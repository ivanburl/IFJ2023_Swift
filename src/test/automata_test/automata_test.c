#include "automata_test.h"
#include"../../utils/logger.h"
#include "../../structures/automata/automata.h"



int test_regex_dot() {
  Automata automata;
  automata_init(&automata, 0, 0);
  automata_set_edge_by_regex(&automata, 0, ".", 1);//all except of .

  int res = 0;
  for (int i=0;i<MAX_AUTOMATA_EDGE_TYPES; i++) {
    res += (automata.automata[0][i] == 1);
  }
  return res == MAX_AUTOMATA_EDGE_TYPES-1 ? 0 : 1;
}

int test_regex_all() {
  Automata automata;
  automata_init(&automata, 0, 0);
  automata_set_edge_by_regex(&automata, 0, ".|$", 1);

  int res = 0;
  for (int i=0;i<MAX_AUTOMATA_EDGE_TYPES; i++) {
    if (automata.automata[0][i] == 1)
      LOG_INFO_WHITE("Found symbol %c", (char)i);
    res += (automata.automata[0][i] == 1);
  }
  LOG_INFO_WHITE("Count %d", res);
  return res == MAX_AUTOMATA_EDGE_TYPES ? 0 : 1;
}

int test_regex_small() {
  Automata automata;
  automata_init(&automata, 0, 0);
  automata_set_edge_by_regex(&automata, 0, "[abc]", 1);//all except of .

  int res = 0;
  for (int i=0;i<MAX_AUTOMATA_EDGE_TYPES; i++) {
    res += (automata.automata[0][i] == 1);
  }
  return res == 3 ? 0 : 1;
}

int test_automata() {

  if (!test_regex_all()) {
    LOG_INFO("AUTOMATA REGEX TEST PASSED");
  } else {
    LOG_ERROR("AUTOMATA REGEX TEST FAILED");
  }

  if (!test_regex_small()) {
    LOG_INFO("AUTOMATA REGEX TEST PASSED");
  } else {
    LOG_ERROR("AUTOMATA REGEX TEST FAILED");
  }

  if (!test_regex_dot()) {
    LOG_INFO("AUTOMATA REGEX TEST PASSED");
  } else {
    LOG_ERROR("AUTOMATA REGEX TEST FAILED");
  }
  return 0;
}