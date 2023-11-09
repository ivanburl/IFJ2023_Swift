#include "../scanner.h"
#include "ifj23_swift_configurator.h"

void configure_softunwrap(Scanner *scanner) {
  automata_set_edge(&(scanner->automata), 0, '?', 72);
  automata_set_edge(&(scanner->automata), 72, '?', 73);
  automata_set_stateReturnValue(&(scanner->automata), 73, SOFT_UNWRAP);
}
void configure_hardunwrap(Scanner *scanner) {
  automata_set_edge(&(scanner->automata), 0, '!', 74);
  automata_set_stateReturnValue(&(scanner->automata), 74, HARD_UNWRAP);
}
