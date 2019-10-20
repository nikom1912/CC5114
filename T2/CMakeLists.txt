cmake_minimum_required(VERSION 3.14)
project(T2)

set(CMAKE_CXX_STANDARD 14)
find_package(PythonLibs 3.6)

set(MAIN_BITS_SET
        GA_T.h
        utils.cpp utils.h)

set(MAIN_WORD_SET
        GA_T.h
        utils.h)

set(MAIN_UNBOUND_KNAP_SET
        GA_T.h
        utils.h)

add_executable(Bits_Main main_bits.cpp ${MAIN_BITS_SET})

add_executable(Word_main main_words.cpp ${MAIN_WORD_SET})

add_executable(T2_main main_0-1_knapsack.cpp ${MAIN_UNBOUND_KNAP_SET})

#target_link_libraries(Word_main "C:\\Users\nikom\\AppData\\Local\\Programs\\Python\\Python37-32\\lib")