#include "../scanner.h"
#include "ifj23_swift_configurator.h"

void configure_let(Scanner *scanner) {
  automata_set_edge(&(scanner->automata), 0, 'l', 43);
  automata_set_edge_by_regex(&(scanner->automata), 43, "[a-zA-Z0-9_]+", 12);
  automata_set_edge(&(scanner->automata), 43, 'e', 44);
  automata_set_edge_by_regex(&(scanner->automata), 44, "[a-zA-Z0-9_]+", 12);
  automata_set_edge(&(scanner->automata), 44, 't', 45);
  automata_set_edge_by_regex(&(scanner->automata), 45, "[a-zA-Z0-9_]+", 12);
  automata_set_stateReturnValue(&(scanner->automata), 45, LET);
}
void configure_var(Scanner *scanner) {
  automata_set_edge(&(scanner->automata), 0, 'v', 46);
  automata_set_edge_by_regex(&(scanner->automata), 46, "[a-zA-Z0-9_]+", 12);
  automata_set_edge(&(scanner->automata), 46, 'a', 47);
  automata_set_edge_by_regex(&(scanner->automata), 47, "[a-zA-Z0-9_]+", 12);
  automata_set_edge(&(scanner->automata), 47, 'r', 48);
  automata_set_edge_by_regex(&(scanner->automata), 48, "[a-zA-Z0-9_]+", 12);
  automata_set_stateReturnValue(&(scanner->automata), 48, VAR);
}
