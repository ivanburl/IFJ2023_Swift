

#include "codegen.h"

Error generate_inter_code(GrammarToken *grToken) {
  AddressTable *addressTable = malloc(sizeof(AddressTable));
  address_table_init(addressTable);

  InterCodeInit();
  post_order_process(grToken, addressTable);
  InterCodeEnd();

  return error_create(NONE, "none");
}

//Yes, recursive, and what (nam pizda)
void post_order_process(GrammarToken *grToken, AddressTable *addressTable) {
  if (grToken == NULL)
    return;

  for (int i = 0; i < grToken->tokensHolderSize; i++) {
    Token *token = grToken->tokensHolder[i];

    if (grToken->grammarRule->assemblerFnPreOrd != NULL)
      grToken->grammarRule->assemblerFnPreOrd(grToken, addressTable);

    //compute all non terminals
    if (token->type > NON_TERMINAL_UNDEFINED) {
      post_order_process(token->data.grammarToken, addressTable);
    }
  }
  if (grToken->grammarRule->assemblerFnPostOrd != NULL)
    grToken->grammarRule->assemblerFnPostOrd(grToken, addressTable);
}