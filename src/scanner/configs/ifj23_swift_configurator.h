//
// Created by burluiva on 10/13/2023.
//

#ifndef IFJ2023_SWIFT_IFJ23_SWIFT_CONFIGURATOR_H
#define IFJ2023_SWIFT_IFJ23_SWIFT_CONFIGURATOR_H

#include "../scanner.h"

void configure_string(Scanner* scanner);
void configure_integer(Scanner* scanner);
void configure_double(Scanner* scanner);
void configure_nil(Scanner* scanner);

void configure_id(Scanner* scanner);
void configure_blank(Scanner* scanner);
void configure_delimiter(Scanner* scanner);

void configure_string_type(Scanner* scanner);
void configure_int_type(Scanner* scanner);
void configure_double_type(Scanner* scanner);
void configure_nullabe(Scanner* scanner);
void configure_boolean(Scanner* scanner);

void configure_if(Scanner* scanner);
void configure_else(Scanner* scanner);

void configure_let(Scanner* scanner);
void configure_var(Scanner* scanner);

void configure_while(Scanner* scanner);

void configure_plus(Scanner* scanner);
void configure_minus(Scanner* scanner);
void configure_multiply(Scanner* scanner);
void configure_divide(Scanner* scanner);

void configure_quote(Scanner* scanner);
void configure_left_curl_bracket(Scanner* scanner);
void configure_right_curl_bracket(Scanner* scanner);
void configure_left_bracket(Scanner* scanner);
void configure_right_bracket(Scanner* scanner);




#endif // IFJ2023_SWIFT_IFJ23_SWIFT_CONFIGURATOR_H
