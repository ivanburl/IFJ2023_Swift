

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
    //compute all non terminals
    if (token->type > NON_TERMINAL_UNDEFINED) {
      post_order_process(token->data.grammarToken, addressTable);
    } else {
      token_preprocess(token, addressTable);
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
  case S:
    statement_process(grToken, addressTable);
    break;
  case INIT:
    if (grToken->tokensHolderSize == 0) {
      return;
    }
    grToken->reg = grToken->tokensHolder[1]->data.grammarToken->reg;
    break;
  default:
    //something happened da i hui s nim
    break;
  }
}

void token_preprocess(Token *token, AddressTable *addressTable) {
  AddressCode ad;
  switch (token->type) {
  case WHILE:
    ad.result = init_cycle(addressTable);
    WhileInitInterCode(&ad);
    break;
  default:
    break;
  }
}

void factor_process(GrammarToken *token, AddressTable *addressTable) {
  Token *tok = token->tokensHolder[0];
  if (tok->type == ID) {
    token->reg = get_reg_fromTA(addressTable, &tok->data.string);
    return;
  }

  //maybe remake switch to RuleID
  switch (tok->type) {
  case INTEGER:
    token->reg = get_reg_new(addressTable);
    StoreInt(token->reg, tok->data.integer_value);
    break;
  case STRING:
    token->reg = get_reg_new(addressTable);
    StoreString(token->reg, &tok->data.string);
    break;
  case DOUBLE:
    token->reg = get_reg_new(addressTable);
    StoreDouble(token->reg, tok->data.double_value);
    break;
  case BOOLEAN:
    token->reg = get_reg_new(addressTable);
    StoreBool(token->reg, tok->data.integer_value);
    break;
  case LEFT_BRACKET:
    token->reg = token->tokensHolder[0]->data.grammarToken->reg;
    break;
  case ID:
    //{ID, F_CALL}, TODO: Add function processing
    break;
  default:
    break;
  }
}
void expression_process(GrammarToken *token, AddressTable *addressTable) {
  //E -> E
  //E -> F
  if (token->tokensHolderSize == 1) {
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
    // TODO: Add function declaration process
    break;
  default:
    break;
  }
}
void statement_process(GrammarToken *grToken, AddressTable *addressTable) {
  if (grToken->tokensHolderSize == 0)
    return;

  AddressCode ad;

  switch (grToken->tokensHolder[0]->type) {
  case WHILE:
    ad.result = end_cycle(addressTable);
    grToken->grammarRule->assemblerFn(&ad);
    break;
  case IF:
    //TODO: PROCESS IF
    break;
//  case D: //Should I just ignore this?
//    break;
  case RETURN:
    ad.result = grToken->tokensHolder[1]->data.grammarToken->reg;
    grToken->grammarRule->assemblerFn(&ad);
    break;
  case BREAK:
  case CONTINUE:
    ad.result = get_cur_cycle(addressTable);
    grToken->grammarRule->assemblerFn(&ad);
    break;
  default:
    break;
  }
}
