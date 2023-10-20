//
// Created by burluiva on 10/20/2023.
//

#include"ifj23_swift_configurator.h"

void configure_string(Scanner* scanner) {
  automata_set_edge(&(scanner->automata), 0, '"', 1);
  for (int i=0; i < MAX_AUTOMATA_EDGE_TYPES; i++) {
    automata_set_edge(&(scanner->automata), 1, i, 1);
  }
  automata_set_edge(&(scanner->automata), 1, '\\', 3);
  automata_set_edge(&(scanner->automata), 1, '\"', 4);
  for (int i =0;i < MAX_AUTOMATA_EDGE_TYPES; i++) {
    automata_set_edge(&(scanner->automata), 3, i, 1);
  }
  automata_set_stateReturnValue(&(scanner->automata), 4, STRING);
  double d = 1e1;
}

void configure_integer(Scanner* scanner){
  for (int i = '0'; i <= '9'; i++) {
    automata_set_edge(&(scanner->automata),0,i,5);
  }
  for (int i = '0'; i <= '9'; i++) {
    automata_set_edge(&(scanner->automata),5,i,5);
  }
  automata_set_stateReturnValue(&(scanner->automata),5,INTEGER);
}
void configure_double(Scanner* scanner){
  for (int i = '0'; i <= '9'; i++) {
    automata_set_edge(&(scanner->automata),0,i,5);
  }
  for (int i = '0'; i <= '9'; i++) {
    automata_set_edge(&(scanner->automata),5,i,5);
  }
  automata_set_edge(&(scanner->automata), 5, 'E', 7);
  automata_set_edge(&(scanner->automata), 5, 'e', 7);
  automata_set_edge(&(scanner->automata), 5, '.', 6);
  automata_set_edge(&(scanner->automata), 6, 'E', 7);
  automata_set_edge(&(scanner->automata), 6, 'e', 7);
  for (int i = '0'; i <= '9'; i++) {
    automata_set_edge(&(scanner->automata),6,i,8);
  }
  for (int i = '0'; i <= '9'; i++) {
    automata_set_edge(&(scanner->automata),7,i,8);
  }
  for (int i = '0'; i <= '9'; i++) {
    automata_set_edge(&(scanner->automata),8,i,8);
  }
  automata_set_stateReturnValue(&(scanner->automata),8,DOUBLE);
}

void configure_nil(Scanner* scanner){
  automata_set_edge(&(scanner->automata),0,'n',9);
  automata_set_edge(&(scanner->automata),9,'i',10);
  automata_set_edge(&(scanner->automata),10,'l',11);
  automata_set_stateReturnValue(&(scanner->automata),11,NIL);
}