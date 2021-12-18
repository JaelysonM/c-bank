#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#include "models/account.h"
#include "controllers/accountcontroller.h"
#include "controllers/pagescontroller.h"
#include "utils/jmplib.h"

int main()
{

  accounts = new_array_list(); // Cria a ArrayList para salvar as contas!
  fetch();
  render_page(0);

  return 0;
}
