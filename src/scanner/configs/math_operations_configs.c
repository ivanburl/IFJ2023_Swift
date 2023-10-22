#include "../scanner.h"
#include"ifj23_swift_configurator.h"

void configure_plus(Scanner* scanner){
  automata_set_edge(&(scanner->automata),0,'+',59);
  automata_set_stateReturnValue(&(scanner->automata),59,PLUS);
}
void configure_minus(Scanner* scanner){
  automata_set_edge(&(scanner->automata),0,'-',60);
  automata_set_stateReturnValue(&(scanner->automata),60,MINUS);
}
void configure_multiply(Scanner* scanner) {
  automata_set_edge(&(scanner->automata), 0, '*', 61);
  automata_set_stateReturnValue(&(scanner->automata), 61, MULTIPLY);
}
void configure_divide(Scanner* scanner){
  automata_set_edge(&(scanner->automata), 0, '/', 62);
  automata_set_stateReturnValue(&(scanner->automata), 62, DIVIDE);
}
