//
// Created by burluiva on 11/18/2023.
//

#include "precedence_parser.h"

void precedence_parser_build_priority_table(
    int priorityTable[MAX_TOKEN_TYPES_NUMBER][MAX_TOKEN_TYPES_NUMBER],
    int operatorPriority[MAX_TOKEN_TYPES_NUMBER],
    int operatorAssociation[MAX_TOKEN_TYPES_NUMBER],
    TokenType idRepresentative);

TokenType precedence_operator_find_id_representative(Grammar *grammar) {
  assert(grammar);
  TokenType idRepresentative = UNDEFINED;
  for (int i = 0; i < grammar->rulesNumber; i++) {
    GrammarRule *grammarRule = &(grammar->grammarRules[i]);

    if (grammarRule->productionsNumber == 1) {
      assert(idRepresentative == UNDEFINED &&
             "Should be only one representative");
      idRepresentative = grammarRule->productions[0];
    }
  }
  return idRepresentative;
}

void precedence_parser_init(PParser *pParser) {
  assert(pParser);
  for (int i = 0; i < MAX_TOKEN_TYPES_NUMBER; i++) {
    for (int j = 0; j < MAX_TOKEN_TYPES_NUMBER; j++) {
      pParser->priorityTable[i][j] = 0;
    }
    pParser->isOperator[i] = false;
  }
  pParser->pGrammar = NULL;
}

void precedence_parser_configure(
    PParser *parser, Grammar *pGrammar,
    const int operatorPriority[MAX_TOKEN_TYPES_NUMBER],
    const int operatorAssociation[MAX_TOKEN_TYPES_NUMBER]) {

  assert(parser && pGrammar);
  assert(pGrammar->rulesNumber > 0);

  parser->resultTokenType = pGrammar->grammarRules[0].resultTokenType;

  parser->pGrammar = pGrammar;

  TokenType idRepresentative =
      precedence_operator_find_id_representative(pGrammar);

  assert(idRepresentative != UNDEFINED && "Could not find id representative");
  parser->idRepresentative = idRepresentative;

  for (int i = 0; i < pGrammar->rulesNumber; i++) {
    GrammarRule *grammarRule = &(pGrammar->grammarRules[i]);
    assert(parser->resultTokenType == grammarRule->resultTokenType);

    for (int j = 0; j < grammarRule->productionsNumber; j++) {
      if (grammarRule->productions[j] < NON_TERMINAL_UNDEFINED) {
        TokenType operator= grammarRule->productions[j];
        parser->isOperator[operator] = true;
        assert(operatorPriority[operator] == -1 &&
               "Priority of operator is not set...");

        parser->priorityTable[operator][idRepresentative] = (j > 0) ? 1 : 0;
        parser->priorityTable[idRepresentative][i] =
            (j < grammarRule->productionsNumber - 1) ? -1 : 0;

        parser->priorityTable[operator][DOLLAR] = -1;
        parser->priorityTable[DOLLAR][operator] = 1;

        if (j == 0)
          parser->priorityTable[operator][DOLLAR] = 0;
        if (j == pGrammar->rulesNumber - 1)
          parser->priorityTable[DOLLAR][operator] = 0;
      }
    }
  }

  for (int i = 0; i < MAX_TOKEN_TYPES_NUMBER; i++)
    for (int j = 0; j < MAX_TOKEN_TYPES_NUMBER; j++) {
      if (!(parser->isOperator[i]) || !(parser->isOperator[j]))
        continue;
      if (operatorPriority[i] == operatorPriority[j]) {
        if (operatorAssociation[i] == 1 && operatorAssociation[j] == 1) {
          parser->priorityTable[i][j] = 1;
        }
        if (operatorAssociation[i] == -1 && operatorAssociation[j] == -1) {
          parser->priorityTable[i][j] = -1;
        }
      } else {
        parser->priorityTable[i][j] =
            operatorPriority[i] > operatorPriority[j] ? 1 : -1;
      }
    }
}

Error precedence_parser_reduce(PParser *pParser, PParserItemVector* tokenStack) {

  int rightPointer = tokenStack->length - 1;
  int leftPointer = rightPointer;

  while (leftPointer>=0 && tokenStack->data[leftPointer].closingType != -1) leftPointer--;

  if (leftPointer<0)
    return error_create(PARSER_ERROR, "Broken expression...");

  GrammarRule testRule;
  grammar_rule_init(&testRule);
  testRule.resultTokenType = pParser->resultTokenType;
  for (int i=leftPointer;i<=rightPointer;i++) {
    testRule.productions[testRule.productionsNumber++] =
        tokenStack->data[i].token->type;
  }

  int ruleId = findGrammarRule(pParser->pGrammar, &testRule);
  if (ruleId < 0)
    return error_create(PARSER_ERROR, "Could not find rule for parsing...");

  Token* reducedToken = malloc(sizeof(Token));
  if (reducedToken == NULL)
    return error_create(FATAL, "Out of memory!");

  reducedToken->type = pParser->pGrammar->grammarRules[ruleId].resultTokenType;
  reducedToken->data.grammarToken->grammarRuleId = ruleId;

  reducedToken->data.grammarToken = malloc(sizeof(GrammarToken));
  if (reducedToken->data.grammarToken == NULL) {
    free(reducedToken);
    return error_create(FATAL, "Out of memory!");
  }

  grammar_token_init(reducedToken->data.grammarToken);

  for (int i=leftPointer;i<=rightPointer;i++) {
    grammar_token_add(reducedToken->data.grammarToken, tokenStack->data[i].token);
  }
  tokenStack->length = leftPointer;

  PParserItem reducedItem;
  pparser_item_init(&reducedItem);
  reducedItem.token = reducedToken; reducedItem.closingType = 0;

  vector_push_back(tokenStack, reducedItem);
}
