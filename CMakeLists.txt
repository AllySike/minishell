cmake_minimum_required(VERSION 3.19)
project(minishell)

set(CMAKE_CXX_STANDARD 14)

add_executable(minishell main.c line_parse.c)
TARGET_LINK_LIBRARIES(minishell /Users/kgale/CLionProjects/minishell/libft/libft.a)
TARGET_LINK_LIBRARIES(minishell "-lreadline" "-ltermcap")