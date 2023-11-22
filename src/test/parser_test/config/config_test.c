//
// Created by burluiva on 11/13/2023.
//
#include "config_test.h"
#include "../../../utils/logger.h"
#include "../../../parser/config/config_parser.h"

Token fast_create_token(TokenType type) {
  Token token;
  token.type = type;
  return token;
}


int parser_config_test() {
    Parser parser;
    parser_init(&parser);
    ifj_2023_parser_config(&parser);

    PParser *pParser = parser.expressionParser;
    int operators[6] = {PLUS, MINUS, MULTIPLY, DIVIDE, F, DOLLAR};
    char chOperators[6] = {'+', '-', '*', '/', 'f', '$'};
    printf("  ");
    for (int i=0;i<6;i++)
      printf("%c ", chOperators[i]);
    printf("\n");
    for (int i=0;i<6;i++) {
      printf("%c ", chOperators[i]);
      for (int j = 0; j < 6; j++) {
        char ch = 'x';
        if (pParser->priorityTable[operators[i]][operators[j]] == 1) ch = '<';
        if (pParser->priorityTable[operators[i]][operators[j]] == -1) ch = '>';
        printf("%c ", ch);
      }
      printf("\n");
    }

    TokenVector tokenVector;
    vector_init(&tokenVector);
    vector_push_back(&tokenVector, fast_create_token(LET));
    vector_push_back(&tokenVector, fast_create_token(ID));
    vector_push_back(&tokenVector, fast_create_token(ASSIGN));
    vector_push_back(&tokenVector, fast_create_token(LEFT_BRACKET));
    vector_push_back(&tokenVector, fast_create_token(ID));
    vector_push_back(&tokenVector, fast_create_token(PLUS));
    vector_push_back(&tokenVector, fast_create_token(ID));
    vector_push_back(&tokenVector, fast_create_token(RIGHT_BRACKET));
    vector_push_back(&tokenVector, fast_create_token(MULTIPLY));
    vector_push_back(&tokenVector, fast_create_token(LEFT_BRACKET));
    vector_push_back(&tokenVector, fast_create_token(ID));
    vector_push_back(&tokenVector, fast_create_token(DIVIDE));
    vector_push_back(&tokenVector, fast_create_token(ID));
    vector_push_back(&tokenVector, fast_create_token(MINUS));
    vector_push_back(&tokenVector, fast_create_token(INTEGER));
    vector_push_back(&tokenVector, fast_create_token(MULTIPLY));
    vector_push_back(&tokenVector, fast_create_token(DOUBLE));
    vector_push_back(&tokenVector, fast_create_token(RIGHT_BRACKET));
    vector_push_back(&tokenVector, fast_create_token(DELIMITER));

    GrammarToken grammarToken;
    grammar_token_init(&grammarToken);
    int offset = 0;
    Error err = parser_parse(&parser, &grammarToken, &tokenVector, &offset, STS, LL_PARSER);
    assert(err.errorType == NONE);
    return 0;
}

int main() {
    parser_config_test();
}