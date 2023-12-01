//
// Created by burluiva on 11/30/2023.
//

#ifndef IFJ2023_SWIFT_SYMTABLE_H
#define IFJ2023_SWIFT_SYMTABLE_H

#include "../../structures/hashmap/hashmap.h"
#include "../../structures/string/string.h"
#include "../grammar/token/grammar_token.h"
#include "../token/token.h"

typedef struct sym_key_t {
  String *name;
  GrammarToken *inputArguments;
} SymtableKey;

void symtable_key_init(SymtableKey* key);
unsigned int symtable_key_hash(SymtableKey *key);

typedef struct sym_value_t {
  TokenType returnType;
  bool isConstant;
  bool isInitialised;
} SymtableValue;

void symtable_value_init(SymtableValue* value);

typedef struct symtable_entry_t {
  HashMapEntry entry;
  SymtableKey key;
  SymtableValue value;
} SymtableEntry;

void symtable_entry_init(SymtableEntry* symtableEntry);
Error symtable_entry_create(SymtableEntry **entry, SymtableKey *key, SymtableValue *value);



typedef HashMap SymTabel;

Error symtable_init(SymTabel* symTable);

/// adds entry (throws error on duplicates)
/// \param symTable - the symtable itself
/// \param entry - pointer to the entry (pointer should not on the stuck)
/// \param override - whether override is allowed
/// \return NULL - could not put, problem
Error symtable_add(SymTabel* symTable, SymtableEntry* entry, bool override);
SymtableEntry* symtable_get(SymTabel * symTable, SymtableKey* key);

Error symtable_push_frame(SymTabel* symTabel);
void symtable_pop_frame(SymTabel* symTabel);

Error symtable_free(SymTabel* symTabel);

#endif // IFJ2023_SWIFT_SYMTABLE_H
