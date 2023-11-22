//
// Created by thekr on 11/21/2023.
//

#ifndef IFJ2023_SWIFT_ADDRESS_TABLE_H
#define IFJ2023_SWIFT_ADDRESS_TABLE_H

#include "../../model/token/token.h"
#include "../../structures/hashmap/hashmap.h"
#include "../../structures/string/string.h"

typedef struct address_table_t {
  HashMap *hashMap;
  int resRegisters;
  int resArgs;
} AddressTable;

typedef struct var_address_t {
  struct hashmap_entry entry; //hash holder
  String *key; //key of entry
  int value; //value of entry
} VarAddress;

void address_table_init(AddressTable *addressTable);
int cmp_fn(const VarAddress *entryA, const VarAddress *entryB);

int get_reg_new(AddressTable *addressTable);
int get_reg_fromTA(AddressTable *addressTable, String *var);
int create_with_reg_fromTA(AddressTable *addressTable, String *var, int reg);

#endif // IFJ2023_SWIFT_ADDRESS_TABLE_H
