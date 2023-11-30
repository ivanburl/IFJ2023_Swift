//
// Created by burluiva on 11/30/2023.
//

#include "symtable.h"

int cmp_symtable_entry(SymtableEntry* entryA, SymtableEntry* entryB) {
  return 0;
}



Error symtable_init(SymTabel *symTable) {
  hashmap_vector_init(symTable);
  Error err = symtable_push_frame(symTable);//push global frame
  if (err.errorType != NONE) return err;
  return error_create(NONE, NULL);
}

Error symtable_push_frame(SymTabel *symTabel) {
  HashMap* frame = malloc(sizeof (HashMap));
  if (frame == NULL) return error_create(FATAL, "Out of memory!");
  hashmap_init(frame, (hashmap_cmp_fn)cmp_symtable_entry);//add cmp and hash function
  hashmap_vector_push_back(symTabel,frame);
  return error_create(NONE, NULL);
}
