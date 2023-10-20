
#include "../scanner.h"
#include"ifj23_swift_configurator.h"

void configure_id(Scanner* scanner) {
  automata_set_edge(&(scanner->automata), 0, '_', 12);
  for (int i = 'a'; i<= 'z'; i++) {
    automata_set_edge(&(scanner->automata),0,i,12);
  }
  for (int i = 'A'; i<='Z'; i++) {
    automata_set_edge(&(scanner->automata), 0, i, 12);
  }
  automata_set_edge(&(scanner->automata), 0, '_', 12);
  for (int i = 'a'; i<= 'z'; i++) {
    automata_set_edge(&(scanner->automata),12,i,12);
  }
  for (int i = 'A'; i<='Z'; i++) {
    automata_set_edge(&(scanner->automata), 12, i, 12);
  }
  for (int i = '0'; i<='9'; i++) {
    automata_set_edge(&(scanner->automata), 12, i, 12);
  }
  automata_set_stateReturnValue(&(scanner->automata), 12, ID);
}

void configure_blank(Scanner* scanner) {
  automata_set_edge(&(scanner->automata),0, ' ', 13);
  automata_set_edge(&(scanner->automata),0, '\t', 13);
  automata_set_edge(&(scanner->automata),13, ' ', 13);
  automata_set_edge(&(scanner->automata),13, '\t', 13);
  automata_set_stateReturnValue(&(scanner->automata), 13, BLANK);
}

void configure_delimiter(Scanner* scanner) {
  automata_set_edge(&(scanner->automata),0, '\n', 13);
  automata_set_edge(&(scanner->automata),0, '\r', 13);
  automata_set_edge(&(scanner->automata),13, '\n', 13);
  automata_set_edge(&(scanner->automata),13, '\r', 13);
  automata_set_stateReturnValue(&(scanner->automata), 13, DELIMITER);
}
