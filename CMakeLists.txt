cmake_minimum_required(VERSION 3.0)
project(IFJ2023_Swift C)

set(CMAKE_C_STANDARD 17)

add_executable(IFJ2023_Swift src/main.c

        src/structures/vector/vector_t.h

        src/utils/util.c
        src/utils/util.h

        src/structures/hashmap/hashtable.c
        src/structures/hashmap/hashtable.h

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

        src/structures/automata/automata.c
        src/structures/automata/automata.h
        src/utils/logger.h
        src/scanner/configs/ifj23_swift_configurator.h
        src/scanner/configs/value_configs.c
        src/scanner/configs/id_configs.c
        src/scanner/configs/type_configs.c
        src/scanner/configs/conditions_configs.c
        src/scanner/configs/conditions_configs.c
        src/scanner/configs/general_type_configs.c
        src/scanner/configs/cycle_configs.c
        src/scanner/configs/special_symbols_configs.c
)
