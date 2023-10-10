cmake_minimum_required(VERSION 3.0)
project(IFJ2023_Swift C)

set(CMAKE_C_STANDARD 17)

add_executable(IFJ2023_Swift src/main.c

        src/structures/vector/vector_t.h

        src/utils/util.c
        src/utils/util.h



        src/structures/hashmap/hashmap.c
        src/structures/hashmap/hashmap.h
        src/structures/hashmap/hashmap_void.c
        src/structures/hashmap/hashmap_void.h

        src/model/token/token.c
        src/model/token/token.h

        src/structures/string/string.h
        src/structures/string/string.c
        src/parser/parser.c
        src/parser/parser.h
        src/scanner/scanner.c
        src/scanner/scanner.h
        src/scanner/scanner.h
        src/structures/vector/vector.h
        src/structures/vector/vector.h

)
