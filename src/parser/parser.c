//
// Created by burluiva on 10/10/2023.
//

#include "parser.h"

void parser_init(Parser *parser) {
  assert(parser);
  parser->llParser = NULL;
  parser->expressionParser = NULL;
}

Error parser_eat(GrammarToken *grammarToken, TokenType tokenType,
                 TokenVector *tokenVector, int *curOffset) {
  if (tokenType == UNDEFINED)
    return error_create(NONE, NULL);

  if (tokenVector->data[*curOffset].type == tokenType) {

    Token *token = malloc(sizeof(Token));
    if (token == NULL)
      return error_create(FATAL, "Out of memory!");
    token_init(token);

    *token = tokenVector->data[*curOffset];
    grammar_token_add(grammarToken, token);

    *curOffset = *curOffset + 1;
    return error_create(NONE, NULL);
  }
  return error_create(
      PARSER_ERROR,
      "Missing token!"); // TODO fix error message plus other fixes
}

TokenType parser_get_current_token(TokenVector *tokenVector,
                                   const int *offset) {
  return *offset >= tokenVector->length ? UNDEFINED
                                        : tokenVector->data[*offset].type;
}

/// Using precedence SA parse (mainly expressions)
/// \param parser parser
/// \param tokenPointer pointer to the token which should be initialized
/// \param tokens the vector of tokens
/// \param offset offset of vector
/// \return NONE in case everything is ok
Error precedence_parser_parse(Parser *parser, Token **tokenPointer,
                              TokenVector *tokens, int *offset);

/// uses ll grammar as main parser
Error parser_parse(Parser *parser, GrammarToken *grammarToken,
                   TokenVector *tokens, int *offset, TokenType finalToken) {
  assert(parser && grammarToken && tokens && offset);

  int ruleId = ll_parser_get_rule(parser->llParser, finalToken,
                                  parser_get_current_token(tokens, offset));

  if (ruleId == -1) {
    return error_create(
        PARSER_ERROR,
        "Could not continue parsing, no rule to continue..."); // TODO
  }

  grammarToken->grammarRuleId = ruleId;
  GrammarRule *grammarRule =
      &(parser->llParser->llGrammar->grammarRules[ruleId]);

  Error err;
  for (int i = 0; i < grammarRule->productionsNumber; i++) {
    TokenType requiredTokenType = grammarRule->productions[i];
    if (requiredTokenType < NON_TERMINAL_UNDEFINED) {
      err = parser_eat(grammarToken, requiredTokenType, tokens, offset);
      if (err.errorType != NONE)
        return err;
    } else {
      if (requiredTokenType != E) {
        Token *token = malloc(sizeof(Token));

        if (token == NULL)
          return error_create(FATAL, "Out of memory!");
        token_init(token);

        token->type = requiredTokenType;
        token->data.grammarToken = malloc(sizeof(GrammarToken));

        if (token->data.grammarToken == NULL)
          return error_create(FATAL, "Out of memory!");
        grammar_token_init(token->data.grammarToken);
        grammar_token_add(grammarToken, token);

        err = parser_parse(parser, token->data.grammarToken, tokens, offset,
                           requiredTokenType);
      } else {
        err = precedence_parser_parse(
            parser,
            &(grammarToken->tokensHolder[grammarToken->tokensHolderSize]),
            tokens, offset);
        grammarToken->tokensHolderSize++;
      }
      if (err.errorType != NONE)
        return err;
    }
  }

  return error_create(NONE, NULL);
}

/// uses precedence
Error precedence_parser_parse(Parser *parser, Token **tokenPointer,
                              TokenVector *tokens, int *offset) {
  assert(parser && tokenPointer && tokens && offset);
  int balance = 0;

  PParserItemVector stack;
  vector_init(&stack);

  Token dollarToken;
  token_init(&dollarToken);
  dollarToken.type = DOLLAR;

  PParserItem initItem;
  pparser_item_init(&initItem);

  initItem.token = &dollarToken;

  vector_push_back(&stack, initItem);

  while (parser_get_current_token(tokens, offset) != UNDEFINED) {
    Token *token = malloc(sizeof(Token));

    if (token == NULL) {
      free(stack.data);
      return error_create(FATAL, "Out of memory!");
    }
    token_init(token);

    token->type = parser->expressionParser->idRepresentative;
    token->data.grammarToken = malloc(sizeof(GrammarToken));
    if (token->data.grammarToken == NULL) {
      free(token);
      free(stack.data);
      return error_create(FATAL, "Out of memory!");
    }
    grammar_token_init(token->data.grammarToken);

    int backupOffset = *offset;
    Error err = parser_parse(parser, token->data.grammarToken, tokens, offset,
                             token->type);

    if (err.errorType != NONE) {
      grammar_token_free(token->data.grammarToken);
      *offset = backupOffset;
      *token = tokens->data[*offset];
      *offset = *offset + 1;
    }

    PParserItem item;
    pparser_item_init(&item);
    item.closingType = 0;
    item.token = token;

    int closeType =
        parser->expressionParser
            ->priorityTable[stack.data[stack.length].token->type][token->type];

    if (closeType == 0) {
      while (stack.length > 2) {
        err = precedence_parser_reduce(parser, stack);
        if (err.errorType != NONE) {
          // TODO clean the memory used + unite errors
          free(stack.data);
          return err;
        }
      }
      if (stack.data[1].token->type != E) {
        // TODO clean the memory + unite errors
        return error_create(PARSER_ERROR, "Parsing of expression failed");
      }
      *tokenPointer = stack.data[1].token;
      free(stack.data);
      return error_create(NONE, NULL);
    } else if (closeType == -1) {

      int foundTerminalPointer = stack.length - 1;
      while (stack.data[foundTerminalPointer].token->type >
             NON_TERMINAL_UNDEFINED)
        foundTerminalPointer--;

      vector_push_back(&stack, item);
      stack.data[foundTerminalPointer + 1].closingType = -1;

      balance -= 1;
    } else if (closeType == 1) {
      item.closingType = 1;
      vector_push_back(&stack, item);
      balance += 1;

      if (balance > 0) {
        // TODO clean memory?
        free(stack.data);
        return error_create(PARSER_ERROR, "Could not parse expression!");
      }

      precedence_parser_reduce(parser->expressionParser, stack);
      *offset = *offset - 1;
    }
  }

  free(stack.data);
  return error_create(NONE, NULL);
}