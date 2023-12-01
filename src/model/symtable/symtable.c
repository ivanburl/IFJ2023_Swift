//
// Created by burluiva on 11/30/2023.
//

#include "symtable.h"
#include "../../utils/logger.h"
#include "limits.h"

//int grammar_token_cmp(GrammarToken *a, GrammarToken *b);
int cmp_symtable_entry(SymtableEntry *entryA, SymtableEntry *entryB) {
  if (entryA == entryB)
    return 0;
  if (entryA == NULL)
    return INT_MIN;
  if (entryB == NULL)
    return INT_MAX;

  int str_cmp = string_cmp(entryA->key.name, entryB->key.name);
  if (str_cmp == 0) {
    return grammar_token_cmp(entryA->key.inputArguments,
                             entryB->key.inputArguments);
  } else {
    return str_cmp;
  }
}

//int grammar_token_cmp(GrammarToken *a, GrammarToken *b) {
//  int tk_size_cmp = a->tokensHolderSize - b->tokensHolderSize;
//  if (tk_size_cmp != 0)
//    return tk_size_cmp;
//
//  for (int i = 0; i < a->tokensHolderSize; i++) {
//    Token *tokenA = a->tokensHolder[i];
//    Token *tokenB = b->tokensHolder[i];
//    int cmp = token_cmp(tokenA, tokenB);
//    if (cmp !=0) return cmp;
//  }
//  return 0;
}

#define FNV32_BASE ((unsigned int)0x811c9dc5)
#define FNV32_PRIME ((unsigned int)0x01000193)
void grammar_token_hash(GrammarToken *grammarToken, unsigned int *hash);
unsigned int symtable_key_hash(SymtableKey *key) {
  unsigned int c, hash = FNV32_BASE;
  if (key->name != NULL && key->name->data != NULL) {
    char *str = key->name->data;
    while ((c = (unsigned char)*str++))
      hash = (hash * FNV32_PRIME) ^ c;
  }
  if (key->inputArguments != NULL) {
    grammar_token_hash(key->inputArguments, &hash);
  }
  return hash;
}

void grammar_token_hash(GrammarToken *grammarToken, unsigned int *hash) {
  assert(grammarToken && hash);
  for (int i = 0; i < grammarToken->tokensHolderSize; i++) {
    Token *token = grammarToken->tokensHolder[i];
    if (token->type > NON_TERMINAL_UNDEFINED) {
      grammar_token_hash(token->data.grammarToken, hash);
    } else {
      *hash = (*hash * FNV32_PRIME) ^ token->type;
    }
  }
}

Error symtable_init(SymTabel *symTable) {
  hashmap_vector_init(symTable);
  Error err = symtable_push_frame(symTable); // push global frame
  if (err.errorType != NONE)
    return err;
  return error_create(NONE, NULL);
}

Error symtable_push_frame(SymTabel *symTabel) {
  HashMap *frame = malloc(sizeof(HashMap));
  if (frame == NULL)
    return error_create(FATAL, "Out of memory!");
  hashmap_init(frame,
               (hashmap_cmp_fn)cmp_symtable_entry); // add cmp and hash function
  hashmap_vector_push_back(symTabel, frame);
  return error_create(NONE, NULL);
}

void symtable_pop_frame(SymTabel *symTabel) {
  if (symTabel->length >= 1) {
    hashmap_free(hashmap_vector_at(symTabel, symTabel->length - 1));
    hashmap_vector_pop(symTabel);
  } else {
    LOG_WARN("SymTable stack was empty could not pop_frame...");
  }
}

SymtableEntry *symtable_declare(SymTabel *symTable, Token *token) {
  return NULL;
}
