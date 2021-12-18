#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "../models/account.h"
#include "accountcontroller.h"
#include "../types/arraylist.h"
#include "../utils/jmplib.h"

Account *create(int id, double balance, char *withdrawPassword, char *password, char *cpf, char *name, char *aka)
{
  Account *account = constructor(id, balance, withdrawPassword, password, cpf, name, aka);

  add_array_list(accounts, account);
  return account;
}

void save()
{
  FILE *outfile = fopen("data.txt", "w+");
  if (outfile == NULL)
  {
    fprintf(stderr, "\nError opened file\n");
    exit(1);
  }

  for (int x = 0; x < accounts->size; x++)
  {
    char *s = serializer(list()[x]);
    strcat(s, "\n");
    fputs(s, outfile);
  }
  fclose(outfile);
}

char *serializer(Account *account)
{
  char *s;
  sprintf(s, "%d|%s|%s|%lf|%s|%s|%s", account->id, account->name, account->aka, account->balance, account->cpf, account->withdrawPassword, account->password);
  return s;
}
Account **list()
{
  if (accounts->size <= 0)
    return NULL;
  Account **arrayPointers = calloc(accounts->size, sizeof(Account));
  for (int x = 0; x < accounts->size; x++)
  {
    arrayPointers[x] = iterator_array_list(accounts)[x];
  }
  return arrayPointers;
}

Account *retrieve(int id)
{
  Account *founded = NULL;
  Account **datas = list();
  for (int x = 0; x < accounts->size; x++)
  {
    Account *account = datas[x];
    if (account->id == id)
    {
      founded = account;
      break;
    }
  }
  return founded;
}

void fetch()
{
  clock_t start_time = clock();
  printf("\r[DATABASE] Carregando base de dados...");
  FILE *in_file = fopen("data.txt", "r+");
  if (in_file == NULL)
  {
    in_file = fopen("data.txt", "a+");
  }
  char line[256];

  while (fgets(line, 1000, in_file) != NULL)
  {
    char **s;
    split(line, '|', &s);
    create(atoi(s[0]), atof(s[3]), s[5] == NULL ? "" : trim(s[5]), s[6] == NULL ? "" : trim(s[6]), s[4] == NULL ? "" : trim(s[4]), s[1] == NULL ? "" : trim(s[1]), s[2] == NULL ? "" : trim(s[2]));
  }
  printf("\r[DATABASE] Dados carregados com sucesso!");
  printf("\n[DATABASE] Demorou %lo ms.", (clock() - start_time));
  fclose(in_file);
}
