#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>
#include <dirent.h>

#include "jmplib.h"

int *cash_splitter(double amount)
{
  int *splliter = calloc(sizeof(int), 4);
  for (int x = 0; x < 4; x++)
    splliter[x] = 0;
  int rest = amount;
  while (rest >= 20)
  {
    if (rest >= 100)
    {
      splliter[1] += rest / 100;
      rest %= 100;
    }
    else if (rest >= 50 && rest % 20 != 0)
    {
      splliter[2] += rest / 50;
      rest %= 50;
    }
    else if (rest >= 20 && rest % 50 != 0)
    {
      splliter[3] += rest / 20;
      rest %= 20;
    }
  }
  if (rest == 0)
    splliter[0] = 1;
  return splliter;
}

void bank_door_withdraw(int *splt)
{

  if (splt[1] > 0)
  {
    int aux = 0;
    FILE *outfile = fopen("bank-door/100.cash", "r");
    if (outfile != NULL)
      fscanf(outfile, "%d", &aux);
    outfile = fopen("bank-door/100.cash", "w");
    fprintf(outfile, "%d", (splt[1] + aux));
    fclose(outfile);
  }
  if (splt[2] > 0)
  {
    int aux = 0;
    FILE *outfile = fopen("bank-door/50.cash", "r");
    if (outfile != NULL)
      fscanf(outfile, "%d", &aux);
    outfile = fopen("bank-door/50.cash", "w");
    fprintf(outfile, "%d", (splt[2] + aux));
    fclose(outfile);
  }
  if (splt[3] > 0)
  {
    int aux = 0;
    FILE *outfile = fopen("bank-door/20.cash", "r");
    if (outfile != NULL)
      fscanf(outfile, "%d", &aux);
    outfile = fopen("bank-door/20.cash", "w");
    fprintf(outfile, "%d", (splt[3] + aux));
    fclose(outfile);
  }
}

char *trim(char *s)
{
  char *ptr;
  if (!s)
    return NULL; // handle NULL string
  if (!*s)
    return s; // handle empty string
  for (ptr = s + strlen(s) - 1; (ptr >= s) && isspace(*ptr); --ptr)
    ;
  ptr[1] = '\0';
  return s;
}

void get_password(char *password)
{
  static struct termios old_terminal;
  static struct termios new_terminal;

  //get settings of the actual terminal
  tcgetattr(STDIN_FILENO, &old_terminal);

  // do not echo the characters
  new_terminal = old_terminal;
  new_terminal.c_lflag &= ~(ECHO);

  // set this as the new terminal options
  tcsetattr(STDIN_FILENO, TCSANOW, &new_terminal);

  // get the password
  // the user can add chars and delete if he puts it wrong
  // the input process is done when he hits the enter
  // the \n is stored, we replace it with \0
  if (fgets(password, BUFSIZ, stdin) == NULL)
    password[0] = '\0';
  else
    password[strlen(password) - 1] = '\0';

  // go back to the old settings
  tcsetattr(STDIN_FILENO, TCSANOW, &old_terminal);
}

int split(char *str, char c, char ***arr)
{
  int count = 1;
  int token_len = 1;
  int i = 0;
  char *p;
  char *t;

  p = str;
  while (*p != '\0')
  {
    if (*p == c)
      count++;
    p++;
  }

  *arr = (char **)malloc(sizeof(char *) * count);
  if (*arr == NULL)
    exit(1);

  p = str;
  while (*p != '\0')
  {
    if (*p == c)
    {
      (*arr)[i] = (char *)malloc(sizeof(char) * token_len);
      if ((*arr)[i] == NULL)
        exit(1);

      token_len = 0;
      i++;
    }
    p++;
    token_len++;
  }
  (*arr)[i] = (char *)malloc(sizeof(char) * token_len);
  if ((*arr)[i] == NULL)
    exit(1);

  i = 0;
  p = str;
  t = ((*arr)[i]);
  while (*p != '\0')
  {
    if (*p != c && *p != '\0')
    {
      *t = *p;
      t++;
    }
    else
    {
      *t = '\0';
      i++;
      t = ((*arr)[i]);
    }
    p++;
  }

  return count;
}

int digits_only(const char *s)
{
  while (*s)
  {
    if (isdigit(*s++) == 0)
      return 0;
  }

  return 1;
}

/* Simula um progresso de acordo com **time** tempo  */
/* Utiliza do usleep() para fazer esse efeito.  */
void fake_loading(int time)
{
  printf("\nCarregando painel aguarde!");

  char spinner[5] = {"|/-\\"};
  int i = 0;
  for (int x = 0; x < time; x++)
  {
    usleep(3000);
    printf("\r[INTERFACE] Carregando interface %c", spinner[i]);
    i = (i + 1) % strlen(spinner);
  }
  system("clear");
  printf("\r[INTERFACE] Carregada!                 ");
}
char *includeURI(char *folder, char *file_name)
{
  char *s;
  sprintf(s, "%s/%s", folder, file_name);
  return s;
}
int read_cash_file(char *dir)
{
  int aux = 0;
  FILE *file = fopen(dir, "r");
  if (file == NULL)
  {
    fprintf(stderr, "\nError opened file\n");
    exit(1);
  }
  fscanf(file, "%d", &aux);
  fclose(file);
  remove(dir);

  return aux;
}

char *substring(char *s, int start, int end)
{
  char *new_word = calloc(sizeof(char), end - start + 1);
  int offset = 0;
  for (int x = 0; x < strlen(s); x++)
  {
    if (x >= start && x <= end)
    {
      new_word[offset] = s[x];
      offset++;
    }
  }
  return new_word;
}
double read_deposit(char *uri)
{
  double acc = 0;
  int aux = 0;
  DIR *folder;
  struct dirent *entry;
  folder = opendir(uri);
  if (folder == NULL)
  {
    perror("Unable to read directory");
    return 0;
  }
  while ((entry = readdir(folder)))
  {
    if (strcmp(entry->d_name, "..") && strcmp(entry->d_name, "."))
    {
      int value = atoi(substring(entry->d_name, 0, strlen(entry->d_name) - 6));

      if (value == 50 || value == 20 || value == 100)
      {
        char file_name[256];
        strcpy(file_name, entry->d_name);
        char directory[256];
        strcpy(directory, uri);
        strcat(directory, "/");
        strcat(directory, file_name);

        int amount = read_cash_file(directory);
        acc += value * amount;
      }
    }
  }

  return acc;
}