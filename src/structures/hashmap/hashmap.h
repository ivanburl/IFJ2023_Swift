//
// Created by burluiva on 10/10/2023.
//

#ifndef IFJ2023_SWIFT_HASHMAP_H
#define IFJ2023_SWIFT_HASHMAP_H

#include <stddef.h>

/// inspiration
/// https://opensource.apple.com/source/Git/Git-98/src/git/hashmap.h.auto.html

/// ############### EXAMPLE OF ENTRY #####################
/// struct CustomEntry {
///     struct hashmap_entry entry; //hash holder
///     long key; //key of entry
///     char value[100]; //value of entry
/// }

/// FNV-1 algorithm
/// http://www.isthe.com/chongo/tech/comp/fnv).
extern unsigned int memhash(const void *buf, size_t len);

typedef struct hashmap_entry {
  struct hashmap_entry *next;
  unsigned int hash;
} HashMapEntry;

/// User-supplied function to test two hashmap entries for equality.
///  \return equals ? 0 : other-number
///  \note entry should contain key and value attributes
typedef int (*hashmap_cmp_fn)(const void *entryA, const void *entryB);

typedef struct hashmap {
  struct hashmap_entry **table;

  hashmap_cmp_fn cmpFn;

  /// total number of entries
  unsigned int size;

  /// the size of the table
  unsigned int tableSize;

  /// when table should grow
  unsigned int growAt;
} HashMap;

void hashmap_init(HashMap *map, hashmap_cmp_fn equals_function);

/// Frees hashmap
/// \warning the elements of hashmap are not freed
void hashmap_free(HashMap *map);

void hashmap_entry_init(void *entry, unsigned int hash) {
  struct hashmap_entry *e = entry;
  e->hash = hash;
  e->next = NULL;
}

/// Find entry by NON-NULL key
/// \return found ? found : NULL
void *hashmap_get(const HashMap *map, const void *key);

/// Replace or Add value into hashmap
/// \param map - hashmap
/// \param entry - entry
/// \note entry must contain \p K key, V value, HashMapEntry ent
void *hashmap_put(HashMap *map, void *entry);

/// Removes entry by key
/// \return found ? found : NULL
void *hashmap_remove(HashMap *map, const void *key);

typedef struct hashmap_iter {
  struct hashmap *map;
  struct hashmap_entry *next;
  unsigned int tablePos;
} HashMapIter;

extern void hashmap_iter_init(HashMap *map, HashMapIter *iter);
extern void *hashmap_iter_next(HashMapIter *iter);

static inline void *hashmap_iter_first(HashMap *map,
                                       HashMapIter *iter) {
  hashmap_iter_init(map, iter);
  return hashmap_iter_next(iter);
}

#endif // IFJ2023_SWIFT_HASHMAP_H
