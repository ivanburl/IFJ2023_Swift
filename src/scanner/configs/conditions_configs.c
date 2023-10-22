#include "../scanner.h"
#include"ifj23_swift_configurator.h"

void configure_if(Scanner* scanner){
  automata_set_edge(&(scanner->automata),0,'i',37);
  automata_set_edge(&(scanner->automata),37,'f',38);
  automata_set_stateReturnValue(&(scanner->automata),38,IF);
}
void configure_else(Scanner* scanner){
  automata_set_edge(&(scanner->automata),0,'e',39);
  automata_set_edge(&(scanner->automata),39,'l',40);
  automata_set_edge(&(scanner->automata),40,'s',41);
  automata_set_edge(&(scanner->automata),41,'e',42);
  automata_set_stateReturnValue(&(scanner->automata),42,ELSE);
}