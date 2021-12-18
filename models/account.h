/* TAD: Account */
/* Tipo exportado */

#ifndef ACCOUNT_H_
#define ACCOUNT_H_

typedef struct
{
  int id;
  double balance;
  char withdrawPassword[256];
  char password[256];
  char cpf[256];
  char name[256];
  char aka[256];
} Account;

Account *constructor(int id, double balance, char *withdrawPassword, char *password, char *cpf, char *name, char *aka);

void destroy(Account *account);

#endif /* ACCOUNT_H_ */