

#include "codegen.h"

Error generate_inter_code(GrammarToken *grToken) {
  AddressTable *addressTable = malloc(sizeof(AddressTable));
  address_table_init(addressTable);

  InterCodeInit();
  post_order_process(grToken, addressTable);
  InterCodeEnd();

  return error_create(NONE, "none");
}

Error generate_registers_inter_code(GrammarToken* grammarToken, char* prefix, int* gen) {
    printf("DEFVAR %s%d", prefix, *gen);
    *gen = *gen + 1;
    for (int i = 0;i<=grammarToken->tokensHolderSize;i++) {
        if (grammarToken->tokensHolder[i]->type>NON_TERMINAL_UNDEFINED) {
            //if (grammarToken->gra)
            //generate_registers_inter_code()
        }
    }
}

void post_order_process(GrammarToken *grToken, AddressTable *addressTable) {
  if (grToken == NULL)
    return;

  if (grToken->grammarRule->assemblerFnPreOrd != NULL)
        grToken->grammarRule->assemblerFnPreOrd(grToken, addressTable);

  for (int i = 0; i < grToken->tokensHolderSize; i++) {
    Token *token = grToken->tokensHolder[i];


    //compute all non terminals
    if (token->type > NON_TERMINAL_UNDEFINED) {
      post_order_process(token->data.grammarToken, addressTable);
    }
  }
  if (grToken->grammarRule->assemblerFnPostOrd != NULL)
    grToken->grammarRule->assemblerFnPostOrd(grToken, addressTable);
}