#include "../scanner.h"
#include"ifj23_swift_configurator.h"

void configure_string_type(Scanner* scanner) {
//14 //15 //16 //17 //18 //19
automata_set_edge(&(scanner->automata),0,'S',14);
automata_set_edge(&(scanner->automata),14,'t',15);
automata_set_edge(&(scanner->automata),15,'r',16);
automata_set_edge(&(scanner->automata),16,'i',17);
automata_set_edge(&(scanner->automata),17,'n',18);
automata_set_edge(&(scanner->automata),18,'g',19);
automata_set_stateReturnValue(&(scanner->automata),19,STRING_TYPE);

}

void configure_int_type(Scanner* scanner) {
  //20 //21 //22
automata_set_edge(&(scanner->automata), 0, 'I', 20);
automata_set_edge(&(scanner->automata), 20, 'n', 21);
automata_set_edge(&(scanner->automata), 21, 't', 22);
automata_set_stateReturnValue(&(scanner->automata), 22, INT_TYPE);
}

void configure_double_type(Scanner* scanner) {
automata_set_edge(&(scanner->automata),0,'D',23);
automata_set_edge(&(scanner->automata),23,'o',24);
automata_set_edge(&(scanner->automata),24,'u',25);
automata_set_edge(&(scanner->automata),25,'b',26);
automata_set_edge(&(scanner->automata),26,'l',27);
automata_set_edge(&(scanner->automata),27,'e',28);
automata_set_stateReturnValue(&(scanner->automata),28,DOUBLE_TYPE);
}

void configure_boolean(Scanner* scanner){
automata_set_edge(&(scanner->automata),0,'B',29);
automata_set_edge(&(scanner->automata),29,'o',30);
automata_set_edge(&(scanner->automata),30,'o',31);
automata_set_edge(&(scanner->automata),31,'l',32);
automata_set_stateReturnValue(&(scanner->automata),32,BOOLEAN_TYPE);
}

void configure_nullabe(Scanner* scanner){
automata_set_edge(&(scanner->automata), 19, '?', 33);
automata_set_edge(&(scanner->automata), 22, '?', 34);
automata_set_edge(&(scanner->automata), 28, '?', 35);
automata_set_edge(&(scanner->automata), 32, '?', 36);
automata_set_stateReturnValue(&(scanner->automata),33,STRING_NULLABLE_TYPE);
automata_set_stateReturnValue(&(scanner->automata),34, INT_NULLABLE_TYPE);
automata_set_stateReturnValue(&(scanner->automata),35,DOUBLE_NULLABLE_TYPE);
automata_set_stateReturnValue(&(scanner->automata), 36, BOOLEAN_NULLABLE_TYPE);
}