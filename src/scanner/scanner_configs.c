#include "configs/ifj23_swift_configurator.h"
#include "scanner.h"

void scanner_configure_swift_2023(Scanner *scanner) {
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
  configure_nullable(scanner);
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
  configure_assign(scanner);

  configure_equal(scanner);
  configure_less(scanner);
  configure_lessequal(scanner);
  configure_greater(scanner);
  configure_greaterequal(scanner);
  configure_notequal(scanner);

  //configure_quote(scanner);
  configure_left_curl_bracket(scanner);
  configure_right_bracket(scanner);
  configure_right_curl_bracket(scanner);
  configure_left_bracket(scanner);

  configure_arrow(scanner);
  configure_func(scanner);
  configure_comma(scanner);
  configure_return(scanner);
  configure_underscore(scanner);
  configure_comment(scanner);
  configure_multi_comment(scanner);

  configure_softunwrap(scanner);
  configure_hardunwrap(scanner);

  configure_colon(scanner);
  configure_semicolon(scanner);
}

/*
 * each terminal should have its oven configuration function, and all of them
 * should be collected into configure automata
 */