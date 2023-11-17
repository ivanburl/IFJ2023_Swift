//
// Created by burluiva on 10/20/2023.
//

#include "ifj23_swift_configurator.h"
/*
void configure_string(Scanner *scanner) {
  automata_set_edge(&(scanner->automata), 0, '\"', 1);
  automata_set_edge_by_regex(&(scanner->automata), 1, ".|$", 1);
  automata_set_edge(&(scanner->automata), 1, '\\', 3);
  automata_set_edge_by_regex(&(scanner->automata), 3, ".|$", 1);
  automata_set_edge(&(scanner->automata), 1, '\"', 2);  // Added transition to state 2
  //automata_set_edge_by_regex(&(scanner->automata), 2, ".|$", 2);  // Added transition to itself for demonstration
  automata_set_stateReturnValue(&(scanner->automata), 2, STRING);
}
*/
void configure_string(Scanner *scanner) {
  automata_set_edge(&(scanner->automata), 0, '\"', 1);
  automata_set_edge(&(scanner->automata), 1, '\"', 2);
  automata_set_edge(&(scanner->automata), 2, '\"', 75);
  automata_set_edge_by_regex(&(scanner->automata), 1, "[^\"]", 3);
  automata_set_edge_by_regex(&(scanner->automata), 3, "[^\"]", 3);
  automata_set_edge(&(scanner->automata), 3, '\"', 4);
  automata_set_stateReturnValue(&(scanner->automata), 4, STRING);
}
// "[^\"\\\\]|\\\\."
void configure_integer(Scanner *scanner) {
  for (int i = '0'; i <= '9'; i++) {
    automata_set_edge(&(scanner->automata), 0, i, 5);
  }
  for (int i = '0'; i <= '9'; i++) {
    automata_set_edge(&(scanner->automata), 5, i, 5);
  }
  automata_set_stateReturnValue(&(scanner->automata), 5, INTEGER);
}
void configure_double(Scanner *scanner) {
  for (int i = '0'; i <= '9'; i++) {
    automata_set_edge(&(scanner->automata), 0, i, 5);
  }
  for (int i = '0'; i <= '9'; i++) {
    automata_set_edge(&(scanner->automata), 5, i, 5);
  }
  automata_set_edge(&(scanner->automata), 5, 'E', 7);
  automata_set_edge(&(scanner->automata), 5, 'e', 7);
  automata_set_edge(&(scanner->automata), 5, '.', 6);
  automata_set_edge(&(scanner->automata), 6, 'E', 7);
  automata_set_edge(&(scanner->automata), 6, 'e', 7);
  for (int i = '0'; i <= '9'; i++) {
    automata_set_edge(&(scanner->automata), 6, i, 8);
  }
  for (int i = '0'; i <= '9'; i++) {
    automata_set_edge(&(scanner->automata), 7, i, 8);
  }
  for (int i = '0'; i <= '9'; i++) {
    automata_set_edge(&(scanner->automata), 8, i, 8);
  }
  automata_set_stateReturnValue(&(scanner->automata), 8, DOUBLE);
}

void configure_nil(Scanner *scanner) {
  automata_set_edge(&(scanner->automata), 0, 'n', 9);
  automata_set_edge_by_regex(&(scanner->automata), 9, "[a-zA-Z0-9_]+", 12);
  automata_set_edge(&(scanner->automata), 9, 'i', 10);
  automata_set_edge_by_regex(&(scanner->automata), 10, "[a-zA-Z0-9_]+", 12);
  automata_set_edge(&(scanner->automata), 10, 'l', 11);
  automata_set_edge_by_regex(&(scanner->automata), 11, "[a-zA-Z0-9_]+", 12);
  automata_set_stateReturnValue(&(scanner->automata), 11, NIL);
}
void configure_multi_string(Scanner *scanner) {
  automata_set_edge_by_regex(&(scanner->automata), 75, "[^\"]", 75);
  automata_set_edge(&(scanner->automata), 75, '\"', 76);
  automata_set_edge_by_regex(&(scanner->automata), 76, "[^\"]", 75);
  automata_set_edge(&(scanner->automata), 76, '\"', 77);
  automata_set_edge_by_regex(&(scanner->automata), 77, "[^\"]", 75);
  automata_set_edge(&(scanner->automata), 77, '\"', 78);
  automata_set_stateReturnValue(&(scanner->automata), 78 , MULTI_STRING);

//  automata_set_edge(&(scanner->automata), 4, '\"', 75);
//  automata_set_edge_by_regex(&(scanner->automata), 75, ".|$", 75);
//  automata_set_edge(&(scanner->automata), 75, '\\', 76);
//  automata_set_edge_by_regex(&(scanner->automata), 76, ".|$", 75);
//  automata_set_edge(&(scanner->automata), 75, '\"', 77);
//  automata_set_edge(&(scanner->automata), 77, '\"', 78);
//  automata_set_edge(&(scanner->automata), 78, '\"', 79);
//  automata_set_edge_by_regex(&(scanner->automata), 79, ".|$", 79);
//  automata_set_stateReturnValue(&(scanner->automata), 79, MULTI_STRING);
}


