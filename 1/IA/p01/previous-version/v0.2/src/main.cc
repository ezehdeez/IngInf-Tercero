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
#include <string>

void AStarSearch(const Grid& grid, const std::pair<int, int>& origin_coords,
                 const std::pair<int, int>& destination_coords,
                 const std::string& map_output_file,
                 const std::string& trace_output_file);

int main(int argc, char* argv[]) {
  try {
    if (argc != 2) {
      std::cerr << "Uso: " << argv[0] << " <mapa>\n";
      return 1;
    }
    Grid grid(10, 11);
    grid.BuildEnvironment(argv[1]);
    AStarSearch(grid, grid.GetOriginCoords(), grid.GetDestinationCoords(),
                "mapa_camino.txt", "traza.txt");
  } catch(const std::exception& e) {
    std::cerr << "[ERROR]: " << e.what() << "\n";
    return 1;
  }
}