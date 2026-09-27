/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: Inteligencia Artificial - Práctica 1. Búsqueda A*
 * 
 * @file main.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-09-22
 * @brief 
 */

#include "../include/grid.h"

#include <exception>
#include <iostream>

int main(int argc, char* argv[]) {
  try {
    Grid grid(11,10);
    grid.BuildEnviroment(argv[1]);
    for(int j = 0; j < grid.GetY(); j++) {      // Fila actual (Y)
      for(int i = 0; i < grid.GetX(); i++) {    // Columna actual (X)
        std::cout << grid.GetCell(i, j) << " ";
      }
      std::cout << std::endl;
    }
  } catch(const std::exception& e) {
    std::cerr << "[ERROR]: " << e.what() << "\n";
    return 1;
  }
}