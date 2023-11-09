#include "configs/ifj23_swift_configurator.h"
#include "scanner.h"

void scanner_configure_swift_2023(Scanner* scanner) {
   configure_double(scanner);
   configure_string(scanner);
   configure_integer(scanner);
   configure_nil(scanner);

   configure_id(scanner);
   configure_blank(scanner);
   configure_delimiter(scanner);

   configure_string_type(scanner);
   configure_int_type(scanner);
   configure_double_type(scanner);
   configure_nullabe(scanner);
   configure_boolean(scanner);

   configure_if(scanner);
   configure_else(scanner);

   configure_let(scanner);
   configure_var(scanner);

   configure_while(scanner);

   configure_plus(scanner);
   configure_minus(scanner);
   configure_multiply(scanner);
   configure_divide(scanner);

   configure_quote(scanner);
   configure_left_curl_bracket(scanner);
   configure_right_bracket(scanner);
   configure_right_curl_bracket(scanner);
   configure_left_bracket(scanner);
}



/*
 * each terminal should have its oven configuration function, and all of them should be collected into configure automata
 */