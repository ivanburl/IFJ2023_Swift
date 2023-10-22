#include "../scanner.h"
#include"ifj23_swift_configurator.h"
//TODO do we need " or ' as a quote

void configure_quote(Scanner* scanner){
  automata_set_edge(&(scanner->automata),0,'\"',54);
  automata_set_stateReturnValue(&(scanner->automata),54,QUOTE);
}
void configure_left_curl_bracket(Scanner* scanner){
  automata_set_edge(&(scanner->automata),0,'{',55);
  automata_set_stateReturnValue(&(scanner->automata),55,LEFT_CURL_BRACKET);
}
void configure_right_curl_bracket(Scanner* scanner){
  automata_set_edge(&(scanner->automata),0,'}',56);
  automata_set_stateReturnValue(&(scanner->automata),56,RIGHT_CURL_BRACKET);
}
void configure_left_bracket(Scanner* scanner){
  automata_set_edge(&(scanner->automata),0,'(',57);
  automata_set_stateReturnValue(&(scanner->automata),57,LEFT_BRACKET);
}
void configure_right_bracket(Scanner* scanner){
  automata_set_edge(&(scanner->automata),0,')',58);
  automata_set_stateReturnValue(&(scanner->automata),58,RIGHT_BRACKET);
}
