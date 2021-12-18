#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#include "../models/account.h"
#include "../utils/jmplib.h"
#include "accountcontroller.h"

double getBalance(Account *account)
{
  return account->balance;
}

int withdrawMoney(Account *account, double value)
{
  if (getBalance(account) - value < 0)
    return 0;
  account->balance -= value;
  return 1;
}

double bankDeposit(Account *account, double value)
{
  account->balance += value;
  return account->balance;
}

int transfer_between_accounts(Account *sender, Account *recipient, double value)
{
  if (withdrawMoney(sender, value))
  {
    bankDeposit(recipient, value);
    return 1;
  }
  return 0;
}
