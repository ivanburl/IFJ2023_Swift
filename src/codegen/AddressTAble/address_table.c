//
// Created by thekr on 11/21/2023.
//

#include "address_table.h"

void address_table_init(AddressTable *addressTable) {
  addressTable->resRegisters = 0;
  addressTable->resArgs = 0;
  hashmap_init(addressTable->hashMap, (hashmap_cmp_fn)cmp_fn);
}

int cmp_fn(const VarAddress *entryA, const VarAddress *entryB) {
  return entryA->key == entryB->key ? 0 : 1;
}


int get_reg_fromTA(AddressTable *addressTable, String *var) {
  VarAddress *varAddress = hashmap_get(addressTable->hashMap, var);
  if (varAddress != NULL) {
    return varAddress->value;
  }
  return -1;
}

//Theoretically pizdec
int create_with_reg_fromTA(AddressTable *addressTable, String *var, int reg) {
  //Create and put new value
  VarAddress *newEntry = malloc(sizeof(VarAddress));
  hashmap_entry_init(newEntry, memhash(var->data, var->length));
  newEntry->key = var;
  newEntry->value = reg;

  newEntry = hashmap_put(addressTable->hashMap, newEntry);

  return newEntry != NULL ? newEntry->value : -1;
}

int get_reg_new(AddressTable *addressTable) {
  return addressTable->resRegisters++;
}
