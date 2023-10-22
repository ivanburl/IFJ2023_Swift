#include "../scanner.h"
#include"ifj23_swift_configurator.h"

void configure_let(Scanner* scanner){
  automata_set_edge(&(scanner->automata),0,'l',43);
  automata_set_edge(&(scanner->automata),43,'e',44);
  automata_set_edge(&(scanner->automata),44,'t',45);
  automata_set_stateReturnValue(&(scanner->automata),45,LET);
}
void configure_var(Scanner* scanner){
  automata_set_edge(&(scanner->automata),0,'l',46);
  automata_set_edge(&(scanner->automata),46,'e',47);
  automata_set_edge(&(scanner->automata),47,'t',48);
  automata_set_stateReturnValue(&(scanner->automata),48,VAR);
}
