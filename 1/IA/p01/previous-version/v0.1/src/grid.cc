/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: Inteligencia Artificial - Práctica 1. Búsqueda A*
 * 
 * @file grid.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-09-22
 * @brief 
 */

#include "../include/grid.h"

void Grid::BuildEnviroment(const std::string& input_file_name) {
  std::ifstream input_file{input_file_name};
  if (!input_file.is_open()) {
    throw std::runtime_error("File " + input_file_name + " cannot be open.");
  }
  int x = 0;
  int y = 0;
  std::string str;
  while(input_file >> str) {
    int value = stoi(str);
    grid_[x][y] = value;
    if(value == 0) {
      origin = {x, y};
    } else if(value == 10) {
      destination = {x, y};
    }
    x++;
    if (x >= x_size_) {
      x = 0;
      y++;
    }
  }
}

double Grid::GetEntryCost(int r, int c) const {
    int i = y_size_ - r;
    int j = c - 1;
    int valor_celda = grid_[i][j];
    if (valor_celda == 10) {
        return 2.0;
    }
    return static_cast<double>(valor_celda);
}