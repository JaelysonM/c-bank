/* Função de transação */
/* Funçăo withdrawMoney - Remove uma certa quantia de dinheiro.*/
int withdrawMoney(Account *account, double value);

/* Função de transação */
/* Funçăo getBalance - Verifica o dinheiro de uma conta.*/
double getBalance(Account *account);

/* Função de transação */
/* Funçăo getBalance - Verifica o dinheiro de uma conta.*/
double bankDeposit(Account *account, double value);

/* Função de transação */
/* Funçăo transfer_between_accounts - Faz a transação entre contas.*/
int transfer_between_accounts(Account *sender, Account *recipient, double value);
