#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "../models/account.h"
#include "../controllers/accountcontroller.h"
#include "../controllers/transationcontroller.h"
#include "../controllers/pagescontroller.h"
#include "../utils/jmplib.h"

void register_submit_page(Account *account)
{
  fake_loading(100);
  printf("\n");
  printf("         =-=-=-=-=-=-=-=-=\n");
  printf("            $$ C-BANK $$");
  printf("\n           [Versão 1.0]");
  printf("\n         =-=-=-=-=-=-=-=-=\n");
  printf("\n%s, seja bem-vindo ao C-Bank :D\n", account->aka);
  printf("\n ⎼⎼⎼| Número da sua conta: %d \n", account->id);
  printf("\n ⎼⎼⎼| Seu nome completo: %s \n", account->name);
  printf("\n ⎼⎼⎼| Seu CPF: %s \n", account->cpf);

  printf("\nVolte para logar em sua conta digitando 'S'!\n");

  create(account->id, account->balance, account->withdrawPassword, account->password, account->cpf, account->name, account->aka);
  save();
}
void login_page()
{
  char string[256];
  printf("\n");
  printf("         =-=-=-=-=-=-=-=-=\n");
  printf("            $$ C-BANK $$");
  printf("\n           [Versão 1.0]");
  printf("\n         =-=-=-=-=-=-=-=-=\n");
  printf("\n              Log-in\n");
  printf("\n        Número da conta: ");
  getchar();
  scanf("%[^\n]", string);
  if (retrieve(atoi(string)))
  {
    Account *account = retrieve(atoi(string));
    printf("\n        Digite a senha: ");
    getchar();
    get_password(string);
    if (!strcmp(string, account->password))
    {
      printf("\rLogin autorizado com sucesso!");
      system("clear");
      cached = account;
      render_page(1);
    }
    else
    {
      printf("\r        A senha está incorreta!");
    }
  }
  else
  {
    printf("\r[ERRO] A conta %s não existe, tente novamente!", string);
  }
}
void delete_page_submit(Account *account)
{

  system("clear");
  printf("\rValidando sua transação!");
  fake_loading(500);
  printf("\n");
  printf("         =-=-=-=-=-=-=-=-=\n");
  printf("            $$ C-BANK $$");
  printf("\n           [Versão 1.0]");
  printf("\n         =-=-=-=-=-=-=-=-=\n");
  printf("\nConta deletada com sucesso e todo dinheiro\n");
  printf("da conta sacado automaticamente!\n");
  printf("\n ⎼⎼⎼| Número da conta deletada: %d \n", account->id);
  printf("\n ⎼⎼⎼| Nome do dono da conta: %s \n", account->name);
  printf("\n ⎼⎼⎼| Saldo da conta: $%.2lf \n", account->balance);
  remove_value_array_list(accounts, account);
  bank_door_withdraw(cash_splitter(account->balance));
  free(account);
  save();
}

void delete_page()
{
  char string[256];
  printf("\n");
  printf("         =-=-=-=-=-=-=-=-=\n");
  printf("            $$ C-BANK $$");
  printf("\n           [Versão 1.0]");
  printf("\n         =-=-=-=-=-=-=-=-=\n");
  printf("\n          Deletar conta\n");
  printf("\n        Número da conta: ");
  getchar();
  scanf("%[^\n]", string);
  if (retrieve(atoi(string)))
  {
    Account *account = retrieve(atoi(string));
    delete_page_submit(account);
  }
  else
  {
    printf("\r[ERRO] A conta %s não existe, tente novamente!", string);
  }
}

void register_page_and_logic()
{

  Account *fake_account = constructor(0, 0, "", "", "", "", "");

  char cache[256];
  char string[256];
  printf("\n");
  printf("         =-=-=-=-=-=-=-=-=\n");
  printf("            $$ C-BANK $$");
  printf("\n           [Versão 1.0]");
  printf("\n         =-=-=-=-=-=-=-=-=\n");
  printf("\n              Log-on\n");
  printf("\n       Seu nome completo: ");
  getchar();
  scanf("%[^\n]", string);
  strcpy(fake_account->name, string);
  printf("\r      Como quer ser chamado?: ");
  getchar();
  scanf("%[^\n]", string);
  strcpy(fake_account->aka, string);
  printf("\r    O número que nínguem lembra (CPF): ");
  getchar();
  scanf("%[^\n]", string);
  if (strlen(string) == 11)
  {

    strcpy(fake_account->cpf, string);
    printf("\r    Uma senha de 6 dígitos (Segredo shihh!): ");
    getchar();
    get_password(string);

    if (strlen(string) == 6 && digits_only(string))
    {

      strcpy(cache, string);
      printf("\n    Repita a senha (igualzinha): ");
      get_password(string);
      if (!strcmp(string, cache))
      {
        strcpy(fake_account->password, string);
        srand(time(0));
        int accountId = (rand() % (10000 - 1000 + 1)) + 1000;
        while (retrieve(accountId))
          accountId = (rand() % (10000 - 1000 + 1)) + 1000;
        fake_account->id = accountId;
        register_submit_page(fake_account);
        return;
      }
      else
      {
        printf("\r[ERRO] As senhas não são iguais!");
      }
    }
    else
    {
      printf("\r[ERRO] Devem ser apenas 6 dígitos e so números ok?");
    }
  }
  else
  {
    printf("\r[ERRO] CPF inválido (Devem ser 11 números)!");
  }
  free(fake_account);
}

void change_aka_page()
{
  char string[256];
  printf("\n");
  printf("         =-=-=-=-=-=-=-=-=\n");
  printf("            $$ C-BANK $$");
  printf("\n           [Versão 1.0]");
  printf("\n         =-=-=-=-=-=-=-=-=\n");
  printf("\n              Alterar apelido!\n");
  printf("\r      Coloque seu novo nome: ");
  getchar();
  scanf("%[^\n]", string);
  strcpy(retrieve(cached->id)->aka, string);
  save();
  printf("\rApelido alterado com sucesso!");
  render_page(1);
}

void change_password_page()
{
  Account *accountCache = retrieve(cached->id);
  char string[256];
  char cache[256];
  printf("\n");
  printf("         =-=-=-=-=-=-=-=-=\n");
  printf("            $$ C-BANK $$");
  printf("\n           [Versão 1.0]");
  printf("\n         =-=-=-=-=-=-=-=-=\n");
  printf("\n        Alterar senha da conta!\n");
  printf("\r    Sua senha: ");
  getchar();
  get_password(string);

  if (!strcmp(string, cached->password))
  {
    printf("\r    Sua nova senha: ");
    get_password(string);
    if (strlen(string) == 6 && digits_only(string))
    {
      strcpy(cache, string);
      printf("\r    Repita a senha (igualzinha): ");
      get_password(string);
      if (!strcmp(string, cache))
      {
        strcpy(accountCache->password, string);
        save();
        printf("\rSenha alterada com sucesso!\r");
        render_page(1);
      }
      else
      {
        printf("\r[ERRO] As senhas não são iguais!");
      }
    }
    else
    {
      printf("\r[ERRO] Devem ser apenas 6 dígitos e so números ok?");
    }
  }
  else
  {
    printf("\r[ERRO] Sua senha está incorreta!");
  }
}
void transfer_submit(Account *account, Account *account2, double value)
{
  printf("\rValidando sua transação!\r");
  fake_loading(300);
  printf("\n");
  printf("         =-=-=-=-=-=-=-=-=\n");
  printf("            $$ C-BANK $$");
  printf("\n           [Versão 1.0]");
  printf("\n         =-=-=-=-=-=-=-=-=\n");
  printf("\n%s sua tranferência deu certo :D\n", account->aka);
  printf("\n ⎼⎼⎼| Número da conta: %d \n", account2->id);
  printf("\n ⎼⎼⎼| Nome do destinatário %s \n", account2->name);
  printf("\n ⎼⎼⎼| Valor transferido: $%.2lf \n", value);

  transfer_between_accounts(account, account2, value);
  save();
}

void transfer_page()
{
  char string[256];
  printf("\n");
  printf("         =-=-=-=-=-=-=-=-=\n");
  printf("            $$ C-BANK $$");
  printf("\n           [Versão 1.0]");
  printf("\n         =-=-=-=-=-=-=-=-=\n");
  printf("\nOlá %s!", cached->aka);
  printf("\n+ Seu saldo: $%.2lf", cached->balance);
  printf("\n\n  Área de transferências\n");
  printf("\n ⎼⎼⎼> Número da conta: ");
  getchar();
  scanf("%[^\n]", string);
  if (retrieve(atoi(string)))
  {
    Account *account = retrieve(atoi(string));
    if (account != cached)
    {
      printf("\n ⎼⎼⎼> Valor a ser transferido: ");
      getchar();
      scanf("%[^\n]", string);
      double value = atof(string);
      if (retrieve(cached->id)->balance - value >= 0)
      {
        if (strcmp(cached->withdrawPassword, ""))
        {
          printf("\r   Sua senha de segurança: ");
          getchar();
          get_password(string);
          if (!strcmp(cached->withdrawPassword, string))
            transfer_submit(retrieve(cached->id), account, value);
          else
            printf("\r[ERRO] Senha de segurança inválida!");
        }
        else
        {
          printf("\r\n[ERRO] Você não cadastrou uma senha de segurança.");
          printf("\r\n[!] Crie uma em: Alteração de dados.");
        }
      }
      else
      {
        printf("\r\n[ERRO] Você não tem esse saldo de $%.2lf para transferir para a conta %d!", value, account->id);
      }
    }
    else
    {
      printf("\r\n[ERRO] Você não pode transferir para si mesmo!");
    }
  }
  else
  {
    printf("\r\n[ERRO] A conta %s não existe, tente novamente!", string);
  }
}
void withdraw_page_submit(double amount)
{
  system("clear");
  printf("\rValidando sua transação!\r");
  fake_loading(500);
  printf("\n");
  printf("         =-=-=-=-=-=-=-=-=\n");
  printf("            $$ C-BANK $$");
  printf("\n           [Versão 1.0]");
  printf("\n         =-=-=-=-=-=-=-=-=\n");
  printf("\n%s seu saque deu certo :D\n", cached->aka);
  printf("\n ⎼⎼⎼| Número da conta: %d \n", cached->id);
  printf("\n ⎼⎼⎼| Seu CPF %s \n", cached->cpf);
  printf("\n ⎼⎼⎼| Valor sacado: $%.2lf \n", amount);
  withdrawMoney(retrieve(cached->id), amount);
  save();
}

void withdraw_page()
{
  char string[256];
  printf("\n");
  printf("         =-=-=-=-=-=-=-=-=\n");
  printf("            $$ C-BANK $$");
  printf("\n           [Versão 1.0]");
  printf("\n         =-=-=-=-=-=-=-=-=\n");
  printf("\nOlá %s!", cached->aka);
  printf("\n+ Seu saldo: $%.2lf", cached->balance);
  printf("\n\n  Área de saque\n");
  printf("\n ⎼⎼⎼> Valor a ser sacado: ");
  getchar();
  scanf("%[^\n]", string);
  double value = atof(string);

  if (retrieve(cached->id)->balance - value >= 0)
  {
    if (strcmp(cached->withdrawPassword, ""))
    {
      printf("\r   Sua senha de segurança: ");
      getchar();
      get_password(string);
      if (!strcmp(cached->withdrawPassword, string))
      {
        int *splt = cash_splitter(value);
        if (splt[0] == 1)
        {
          bank_door_withdraw(splt);
          withdraw_page_submit(value);
        }
        else
        {
          printf("\r[ERRO] Você não pode sacar essa quantidade (Apenas comuns de 20, 50 e 100)!");
        }
      }
      else
      {
        printf("\r[ERRO] Senha de segurança inválida!");
      }
    }
    else
    {
      printf("\r\n[ERRO] Você não cadastrou uma senha de segurança.");
      printf("\r\n[!] Crie uma em: Alteração de dados.");
    }
  }
  else
  {
    printf("\r\n[ERRO] Você não tem esse saldo de $%.2lf para sacar!", value);
  }
}
void deposit_page_submit(double amount)
{
  system("clear");
  printf("\rValidando sua transação!\r");
  fake_loading(500);
  printf("\n");
  printf("         =-=-=-=-=-=-=-=-=\n");
  printf("            $$ C-BANK $$");
  printf("\n           [Versão 1.0]");
  printf("\n         =-=-=-=-=-=-=-=-=\n");
  printf("\n%s seu depósito deu certo :D\n", cached->aka);
  printf("\n ⎼⎼⎼| Número da conta: %d \n", cached->id);
  printf("\n ⎼⎼⎼| Seu CPF %s \n", cached->cpf);
  printf("\n ⎼⎼⎼| Valor depositado: $%.2lf \n", amount);
  bankDeposit(retrieve(cached->id), amount);
  save();
}

void deposit_page()
{
  char string[256];
  printf("\n");
  printf("         =-=-=-=-=-=-=-=-=\n");
  printf("            $$ C-BANK $$");
  printf("\n           [Versão 1.0]");
  printf("\n         =-=-=-=-=-=-=-=-=\n");
  printf("\nOlá %s!", cached->aka);
  printf("\n+ Seu saldo: $%.2lf", cached->balance);
  printf("\n\n  Área de deposito\n");
  printf("\n!! Coloque arquivos .cash dentro da pasta");
  printf("\n      bank-door com a quantidade escrita dentro");
  printf("\n      do arquivo!");
  printf("\n!! Apenas [20.cash, 50.cash, 100.cash] serão aceitas");
  printf("\n\n   Pressione ENTER para confirmar o depósito!\n             ");
  getchar();
  scanf("%[^\n]", string);
  double amount = read_deposit("bank-door");
  deposit_page_submit(amount);
}

void change_password_process(Account *accountCache, char *string, char *cache)
{
  printf("\r    Sua nova senha: ");
  get_password(string);
  if (strlen(string) >= 5)
  {
    strcpy(cache, string);
    printf("\r    Repita a senha (igualzinha): ");
    get_password(string);
    if (!strcmp(string, cache))
    {
      strcpy(accountCache->withdrawPassword, string);
      save();
      printf("\rSenha criada com sucesso!            ");
      render_page(2);
    }
    else
    {
      printf("\r[ERRO] As senhas não são iguais!");
    }
  }
  else
  {
    printf("\r[ERRO] Devem ser mais que 5 caracteres!");
  }
}

void change_password_withdraw_page()
{
  Account *accountCache = retrieve(cached->id);
  char string[256];
  char cache[256];
  printf("\n");
  printf("         =-=-=-=-=-=-=-=-=\n");
  printf("            $$ C-BANK $$");
  printf("\n           [Versão 1.0]");
  printf("\n         =-=-=-=-=-=-=-=-=\n");
  printf("\n        Alterar senha de segurança!\n");
  if (strcmp(accountCache->withdrawPassword, ""))
  {
    printf("\r    Sua senha: ");
    getchar();
    get_password(string);
    if (!strcmp(string, cached->withdrawPassword))
    {
      change_password_process(accountCache, string, cache);
    }
    else
    {
      printf("\n[ERRO] Senha de segurança incorreta!");
    }
  }
  else
  {
    getchar();
    change_password_process(accountCache, string, cache);
  }
}
