#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#include "../utils/jmplib.h"
#include "accountcontroller.h"
#include "account.h"
#include "pages.h"
#include "pagescontroller.h"

/* Faz a parte de renderização da interface visual  */

void render_page(int painel)
{
  int option = -1;
  switch (painel)
  {
  case 0: // Main page
    fake_loading(400);
    printf("\n");
    printf("         =-=-=-=-=-=-=-=-=\n");
    printf("            $$ C-BANK $$");
    printf("\n           [Versão 1.0]");
    printf("\n         =-=-=-=-=-=-=-=-=\n");
    printf("\nPainel inicial: (Selecione uma opção)\n");
    printf("\n  ⎼⎼⎼| Logar-se! (1)");
    printf("\n  ⎼⎼⎼| Novo por aqui? Cadastre-se! (2)");
    printf("\n  ⎼⎼⎼| Listar contas (cuidado) (3)");
    printf("\n  ⎼⎼⎼| Quer saber mais sobre nós? (4)");
    printf("\n  ⎼⎼⎼| Apagar conta **NOVO** (5)");
    printf("\n  ⎼⎼⎼| Cansei! Quero sair. (6)");
    printf("\n\n");
    break;
  case 1:
    fake_loading(530);
    printf("\n");
    printf("         =-=-=-=-=-=-=-=-=\n");
    printf("            $$ C-BANK $$");
    printf("\n           [Versão 1.0]");
    printf("\n         =-=-=-=-=-=-=-=-=\n");
    printf("\nOlá %s!", cached->aka);
    printf("\n+ Seu saldo: $%.2lf", cached->balance);
    printf("\n\n  Ações disponiveis para você :D\n");
    printf("\n ⎼⎼⎼| Transferir (1)");
    printf("\n ⎼⎼⎼| Sacar (2)");
    printf("\n ⎼⎼⎼| Depositar (3)");
    printf("\n ⎼⎼⎼| Alteração de dados (4)");
    printf("\n ⎼⎼⎼| Cansei! Quero sair. (5)");
    printf("\n\n");
    break;
  case 2:
    fake_loading(100);
    printf("\n");
    printf("         =-=-=-=-=-=-=-=-=\n");
    printf("            $$ C-BANK $$");
    printf("\n           [Versão 1.0]");
    printf("\n         =-=-=-=-=-=-=-=-=\n");
    printf("\nOlá %s!", cached->aka);
    printf("\n+ Seu saldo: $%.2lf", cached->balance);
    printf("\n\n  Alterações que você pode fazer!\n");
    printf("\n ⎼⎼⎼| Alterar apelido (1)");
    printf("\n ⎼⎼⎼| Alterar senha (2)");
    printf("\n ⎼⎼⎼| Alterar/Criar senha de segurança (3)");
    printf("\n ⎼⎼⎼| Quero voltar. (4)");
    printf("\n\n");
    break;
  }
  printf("Opção: ");
  scanf("%d", &option);
  render_choose(painel, option);
}

/* Processa a escolha feita a partir de um painel e uma opção  */
void render_choose(int painel, int choose)
{
  char repeatable = 'N';
  do
  {
    switch (painel)
    {
    case 0:
      fake_loading(100); // Fake loading padrão para o primeiro painel;
      switch (choose)
      {
      case 1:
        login_page();
        break;
      case 2:
        register_page_and_logic();
        break;
      case 3:
        printf("\n");
        printf("         =-=-=-=-=-=-=-=-=\n");
        printf("            $$ C-BANK $$");
        printf("\n           [Versão 1.0]");
        printf("\n         =-=-=-=-=-=-=-=-=\n");
        printf("         Dados para Nerds :)\n");
        printf("-----------------------------------\n");

        for (int x = 0; x < accounts->size; x++)
        {
          printf("\n ⎼⎼⎼| Conta número: %d | Saldo $%.2lf", list()[x]->id, list()[x]->balance);
        }
        break;
      case 4:
        printf("\n");
        printf("         =-=-=-=-=-=-=-=-=\n");
        printf("            $$ C-BANK $$");
        printf("\n           [Versão 1.0]");
        printf("\n         =-=-=-=-=-=-=-=-=\n");
        printf("           Sobre nós :)\n");
        printf("-----------------------------------\n");
        printf("O C-Bank foi criado sobre demanda através de um\n");
        printf("trabalho solicitado pelo Prof. Dr. Carlos.\n");
        printf("Maurício Jr. tendo como parte da equipe \n");
        printf("so alunos: \n\n");
        printf(" + Jaelyson Martins - CTO (github.com/JaelysonM); \n");
        printf(" + João Gabriel Coelho - CEO e Talker; \n");
        printf(" + Daniel Victor - CEO e Talker; \n");
        break;
      case 5:
        delete_page();
        break;
      case 6:
        printf("\nSistema encerrado!");
        system("clear");
        exit(0);
        break;
      default:
        printf("\nOpção Inválida! Ta errado viu!");
        system("clear");
        render_page(painel);
        return;
      }
      break;
    case 1:
      fake_loading(100); // Fake loading padrão para o segundo painel;
      switch (choose)
      {
      case 1:
        transfer_page();
        break;
      case 2:
        withdraw_page();
        break;
      case 3:
        deposit_page();
        break;
      case 4:
        system("clear");
        render_page(2);
        break;
      case 5:
        system("clear");
        render_page(0);
        break;
      default:
        printf("\nOpção Inválida! Ta errado viu!");
        system("clear");
        render_page(painel);
        return;
      }
      break;
    case 2:
      fake_loading(100); // Fake loading padrão para o segundo painel;
      switch (choose)
      {
      case 1:
        change_aka_page();
        break;
      case 2:
        change_password_page();
        break;
      case 3:
        change_password_withdraw_page();
        break;
      case 4:
        system("clear");
        render_page(1);
        break;
      default:
        printf("\nOpção Inválida! Ta errado viu!");
        system("clear");
        render_page(painel);
        return;
      }
      break;
    }
    printf("\n\nVoltar? (S/N): ");
    getchar();
    scanf("%c", &repeatable);
  } while (repeatable == 'N');
  system("clear");
  render_page(painel);
}