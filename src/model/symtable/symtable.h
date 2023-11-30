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

void init_symtable_key(SymtableKey* key);

typedef struct sym_value_t {
  TokenType returnType;
  bool isConstant;
  bool isInitialised;
} SymtableValue;

void init_symtable_value(SymtableValue* value);

typedef struct symtable_entry_t {
  HashMapEntry entry;
  SymtableKey key;
  SymtableValue value;
} SymtableEntry;


typedef HashMapPointerVector SymTabel;

Error symtable_init(SymTabel* symTable);

SymtableEntry* symtable_declare(SymTabel* symTable, Token* token);
SymtableEntry* symtable_find(SymTabel * symTable, Token* token);

Error symtable_push_frame(SymTabel* symTabel);
void symtable_pop_frame(SymTabel* symTabel);

Error symtable_free(SymTabel* free);

#endif // IFJ2023_SWIFT_SYMTABLE_H
