//
// Created by burluiva on 11/30/2023.
//

#include "symtable.h"
#include "../../utils/logger.h"
#include "limits.h"

void symtable_key_init(SymtableKey *key) {
  key->name = NULL;
  key->inputArguments = NULL;
}

void symtable_value_init(SymtableValue* value) {
  value->returnType = UNDEFINED;
  value->isConstant = false;
  value->isInitialised = false;
}

void symtable_entry_init(SymtableEntry *symtableEntry) {
  assert(symtableEntry);
  hashmap_entry_init(&symtableEntry->entry, 0);
  symtable_key_init(&symtableEntry->key);
  symtable_value_init(&symtableEntry->value);
}

Error symtable_entry_create(SymtableEntry **entry, SymtableKey *key,
                            SymtableValue *value) {
  *entry = malloc(sizeof(SymtableEntry));
  if (*entry == NULL) return error_create(FATAL, "Out of memory!");

  symtable_entry_init(*entry);
  hashmap_entry_init(&((*entry)->entry), symtable_key_hash(key));
  (*entry)->key = *key;
  (*entry)->value = *value;

  return error_create(NONE, NULL);
}

int cmp_symtable_entry(SymtableEntry *entryA, SymtableEntry *entryB) {
  if (entryA == entryB)
    return 0;
  if (entryA == NULL)
    return INT_MIN;
  if (entryB == NULL)
    return INT_MAX;

  int str_cmp = string_cmp(entryA->key.name, entryB->key.name);
  if (str_cmp != 0) {
    return str_cmp;
  }
  return grammar_token_cmp(entryA->key.inputArguments,
                           entryB->key.inputArguments);
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

/// add declaration to last stack frame of our symtable
/// \param symTable - symbolic table
/// \param entry - entry must be created using symtable_entry_create function
/// \param override - whether to override previous declaration (symbol)
/// \return
Error symtable_add(SymTabel *symTable, SymtableEntry *entry, bool override) {
  assert(symTable && entry);
  SymtableEntry *previous = hashmap_put(symTable, entry);
  if (previous != NULL && !override)
    return error_create(FATAL, "redefinition or override is not allowed");//TODO add better eeror
  return error_create(NONE, NULL);
}
SymtableEntry *symtable_get(SymTabel *symTable, SymtableKey *key) {
  assert(symTable && key);
  SymtableEntry searchEntry;
  symtable_entry_init(&searchEntry);
  searchEntry.key = *key;
  hashmap_entry_init(&searchEntry.entry, symtable_key_hash(&searchEntry.key));
  return (SymtableEntry*) hashmap_get(symTable, &searchEntry);
}

Error symtable_free(SymTabel *symTabel) {
  hashmap_free(symTabel);
  return error_create(NONE, NULL);
}
