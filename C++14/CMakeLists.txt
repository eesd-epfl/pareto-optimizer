# Written by Mahmoud S. Shaqfa and Prof. Katrin Beyer - EPFL - EESD Lab
# Subject: Pareto sampling algorithm
cmake_minimum_required(VERSION 2.4)
project(pareto_algorithm)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_CXX_STANDARD 14)

add_executable(pareto_algorithm main.cpp types.h pareto_interface.cpp pareto_interface.h
        objective.cpp objective.h random_generator.h csv_writer.cpp csv_writer.h pareto.cpp pareto.h)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/plotter.py
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})