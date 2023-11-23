//
// Created by thekr on 11/21/2023.
//

#include "address_table.h"

#define FNV32_BASE ((unsigned int)0x811c9dc5)
#define FNV32_PRIME ((unsigned int)0x01000193)

//------------SYSTEM------------
unsigned int strhash(const char *str)
{
  unsigned int c, hash = FNV32_BASE;
  while ((c = (unsigned char) *str++))
    hash = (hash * FNV32_PRIME) ^ c;
  return hash;
}
void address_table_init(AddressTable *addressTable) {
  addressTable->resRegisters = 0;
  addressTable->hashMap = malloc(sizeof(HashMap));
  hashmap_init(addressTable->hashMap, (hashmap_cmp_fn)cmp_fn);
}
int cmp_fn(const VarAddress *entryA, const VarAddress *entryB) {
  return strcmp(entryA->key->data, entryB->key->data) ? 0 : 1;
}

//------------VARIABLES------------
//Temp reg
int get_reg_new(AddressTable *addressTable) {
  return addressTable->resRegisters++;
}

int get_reg_cur(AddressTable *addressTable) {
  return addressTable->resRegisters-1;
}


int AT_create(AddressTable *addressTable, String *var) {
  int reg = get_reg_new(addressTable);
  reg = AT_create_withReg(addressTable, var, reg);
  return reg;
}

int AT_create_withReg(AddressTable *addressTable, String *var, int reg) {
  //Create and put new value
  VarAddress *newEntry = malloc(sizeof(VarAddress));
  hashmap_entry_init(newEntry, strhash(var->data));
  newEntry->key = var;
  newEntry->value = reg;

  newEntry = hashmap_put(addressTable->hashMap, newEntry);

  return newEntry != NULL ? newEntry->value : -1;
}

int AT_get(AddressTable *addressTable, String *var) {
  VarAddress *varAddress = hashmap_get(addressTable->hashMap, var);
  if (varAddress != NULL) {
    return varAddress->value;
  }
  return -1;
}

int AT_put(AddressTable *addressTable, String *var, int reg) {
  VarAddress *varAddress = hashmap_get(addressTable->hashMap, var);
  varAddress = hashmap_put(addressTable->hashMap, varAddress);
  return varAddress != NULL ? 1 : 0;
}


//------------WHILE------------
int init_cycle(AddressTable *addressTable) {
  int cur_while = addressTable->resCycles++;
  vector_push_back(addressTable->curCycle, cur_while);
  return cur_while;
}

int end_cycle(AddressTable *addressTable) {
  int cur_while = get_cur_cycle(addressTable);
  vector_erase_back(addressTable->curCycle);
  return cur_while;
}

int get_cur_cycle(AddressTable *addressTable) {
  return vector_at(addressTable->curCycle, addressTable->curCycle->length-1);
}
