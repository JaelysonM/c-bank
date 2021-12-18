#include "../types/arraylist.h"
#include "../models/account.h"

ArrayList *accounts;

const Account *cached;

/* Função padrão CRUD (Create, Read, Update, Delete) */
/* Funçăo create - Cria o 'objeto' Account */
Account *create(int id, double balance, char *withdrawPassword, char *password, char *cpf, char *name, char *aka);

/* Função padrão CRUD (Create, Read, Update, Delete) */
/* Funçăo read - Lê todos os valores do banco salvo  */
Account **list();

/* Função padrão CRUD (Create, Read, Update, Delete) */
/* Funçăo retrive - Aloca e retorna um ponto com coordenadas (x,y) */
Account *retrieve(int id);

/* Função padrão CRUD (Create, Read, Update, Delete) */
/* Funçăo update - Atualiza os dados de uma estrutura a partir de uma instância */
void update(Account *account, Account *newAccount);

/* Função padrão CRUD (Create, Read, Update, Delete) */
/* Funçăo update - Deleta os dados a partir de uma instância */
void delete (Account *account);

void save();

char *serializer(Account *account);

void fetch();
