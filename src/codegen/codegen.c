

#include "codegen.h"

void generate_inter_code(GrammarToken *grToken) {
  AddressTable *addressTable = malloc(sizeof(AddressTable));
  address_table_init(addressTable);

  InterCodeInit();
  post_order_process(grToken, addressTable);
  InterCodeEnd();
}

//Yes, recursive, and what (nam pizda)
void post_order_process(GrammarToken *grToken, AddressTable *addressTable) {
  if (grToken == NULL)
    return;

  for (int i = 0; i < grToken->tokensHolderSize; i++) {
    Token *token = grToken->tokensHolder[i];
    //compute all non terminals
    if (token->type > NON_TERMINAL_UNDEFINED) {
      post_order_process(token->data.grammarToken, addressTable);
    }
  }

  switch (grToken->grammarRule->resultTokenType) {
  case F:
    factor_process(grToken, addressTable);
    break;
  case E:
    expression_process(grToken, addressTable);
    break;
  case D:
    declaration_process(grToken, addressTable);
    break;
  case INIT:
    if (grToken->tokensHolderSize == 0)
      return;
    grToken->reg = grToken->tokensHolder[1]->data.grammarToken->reg;
    break;
  default:
    //something happened da i hui s nim
    break;
  }
}

void factor_process(GrammarToken *token, AddressTable *addressTable) {
  Token *tok = token->tokensHolder[0];
  if (tok->type == ID && token->tokensHolderSize == 1) {
    token->reg = get_reg_fromTA(addressTable, &tok->data.string);
    return;
  }

  //maybe remake switch to RuleID
  switch (tok->type) {
  case INTEGER:
    StoreInt(get_reg_new(addressTable), tok->data.integer_value);
    token->reg = addressTable->resRegisters;
    break;
  case STRING:
    StoreString(get_reg_new(addressTable), &tok->data.string);
    token->reg = addressTable->resRegisters;
    break;
  case DOUBLE:
    StoreDouble(get_reg_new(addressTable), tok->data.double_value);
    token->reg = addressTable->resRegisters;
    break;
  case BOOLEAN:
    //StoreBoolean
    break;
  case LEFT_BRACKET:
    //neebu chto eto
    //LEFT_BRACKET, UNDERSCORE, RIGHT_BRACKET
    break;
  case ID:
    //{ID, F_CALL},
    break;
  default:
    break;
  }
}
void expression_process(GrammarToken *token, AddressTable *addressTable) {
  //if we have factor then just load this register into GramToken
  if (token->tokensHolder[0]->type == F) {
    token->reg = token->tokensHolder[0]->data.grammarToken->reg;
    return;
  }

  //Create 3AK
  AddressCode ad3;
  ad3.op1 = token->tokensHolder[0]->data.grammarToken->reg;
  ad3.op2 = token->tokensHolder[2]->data.grammarToken->reg;
  ad3.result = get_reg_new(addressTable);

  //Set current token reg to our output reg
  token->reg = ad3.result;
  token->grammarRule->assemblerFn(&ad3);
}

void declaration_process(GrammarToken *token, AddressTable *addressTable) {
  switch (token->tokensHolder[0]->type) {
  case VAR:
  case LET:
    token->reg = create_with_reg_fromTA(
        addressTable,
        &token->tokensHolder[1]->data.string,
        token->tokensHolder[3]->data.grammarToken->reg);
    break;
  case FUNC:
    break;
  default:
    break;
  }
}
