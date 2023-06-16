cmake_minimum_required(VERSION 3.24)
project(bigHW C)

set(CMAKE_C_STANDARD 23)

add_executable(bigHW main.c menuFile.c menuFile.h calcHash.c calcHash.h parseFreeRewrite.c parseFreeRewrite.h booksProcessing.c booksProcessing.h studentsProcessing.c studentsProcessing.h borrowedProcessing.c borrowedProcessing.h sortAlgorithm.c)
