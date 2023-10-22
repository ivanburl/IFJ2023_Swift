#include "../scanner.h"
#include"ifj23_swift_configurator.h"

void configure_while(Scanner* scanner){
  automata_set_edge(&(scanner->automata),0,'w',49);
  automata_set_edge(&(scanner->automata),49,'h',50);
  automata_set_edge(&(scanner->automata),50,'i',51);
  automata_set_edge(&(scanner->automata),51,'l',52);
  automata_set_edge(&(scanner->automata),52,'e',53);
  automata_set_stateReturnValue(&(scanner->automata),53,WHILE);
}