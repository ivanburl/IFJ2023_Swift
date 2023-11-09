cmake_minimum_required(VERSION 3.0)
project(IFJ2023_Swift C)

set(CMAKE_C_STANDARD 17)

add_executable(IFJ2023_Swift src/main.c

        src/structures/vector/vector_t.h

        src/utils/util.c
        src/utils/util.h

        src/structures/hashmap/hashmap.c
        src/structures/hashmap/hashmap.h

        src/model/token/token.c
        src/model/token/token.h

        src/structures/string/string.h
        src/structures/string/string.c

        src/parser/parser.c
        src/parser/parser.h

        src/scanner/scanner_configs.c
        src/scanner/scanner.c
        src/scanner/scanner.h

        src/structures/vector/vector.h
        src/structures/vector/vector.h

        src/model/error/error.c
        src/model/error/error.h

        src/utils/logger.h

        src/structures/automata/automata.c
        src/structures/automata/automata.h

        src/scanner/configs/ifj23_swift_configurator.h
        src/scanner/configs/value_configs.c
        src/scanner/configs/id_configs.c
        src/scanner/configs/type_configs.c
        src/scanner/configs/conditions_configs.c
        src/scanner/configs/conditions_configs.c
        src/scanner/configs/general_type_configs.c
        src/scanner/configs/cycle_configs.c
        src/scanner/configs/special_symbols_configs.c
        src/scanner/configs/math_operations_configs.c

        src/model/grammar/rule/grammar_rule.c
        src/model/grammar/rule/grammar_rule.h

        src/model/grammar/grammar.c
        src/model/grammar/grammar.h

        src/model/grammar/token/grammar_token.c
        src/model/grammar/token/grammar_token.h

        src/parser/config/config_parser.c
        src/parser/config/config_parser.h
        src/scanner/configs/unwraps_configs.c
        src/scanner/configs/utils_configs.c
        src/scanner/configs/utils_configs.c
)
