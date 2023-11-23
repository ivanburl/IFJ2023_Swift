#include "vector.h"
#include "../../model/token/token.h"
#include "../../parser/precedence_parser/precedence_parser.h"

vector_impl(Token, Token, token_);
vector_impl(PParserItem, PParserItem, pparser_item_);
vector_impl(int, Int, int_);
vector_impl(double, Double, double_);