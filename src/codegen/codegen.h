//
// Created by thekr on 11/20/2023.
//

#ifndef IFJ2023_SWIFT_CODEGEN_H
#define IFJ2023_SWIFT_CODEGEN_H

#include "inter_code/inter_code.h"
#include "../model/grammar/grammar.h"s
#include "AddressTAble/address_table.h"
#include "../model/grammar/rule/grammar_rule.h"
#include "../model/grammar/token/grammar_token.h"

void generate_inter_code(GrammarToken *token);
void post_order_process(GrammarToken *token, AddressTable *addressTable);

void factor_process(GrammarToken *token, AddressTable *addressTable);
void expression_process(GrammarToken *token, AddressTable *addressTable);
void declaration_process(GrammarToken *token, AddressTable *addressTable);

#endif // IFJ2023_SWIFT_CODEGEN_H