#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "account.h"

Account *constructor(int id, double balance, char *withdrawPassword, char *password, char *cpf, char *name, char *aka)
{
  Account *account = malloc(sizeof(Account));
  account->id = id;
  account->balance = balance;
  strcpy(account->withdrawPassword, withdrawPassword);
  strcpy(account->password, password);
  strcpy(account->cpf, cpf);
  strcpy(account->name, name);
  strcpy(account->aka, aka);
  return account;
}

void destroy(Account *account)
{
  free(account);
}
