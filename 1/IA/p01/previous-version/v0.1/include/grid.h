/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: Inteligencia Artificial - Práctica 1. Búsqueda A*
 * 
 * @file grid.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-09-22
 * @brief 
 */


#include <fstream>
#include <iostream>
#include <vector>

#ifndef GRID_H
#define GRID_H

class Grid {
 public:
  Grid(int x_size, int y_size) : x_size_{x_size}, y_size_{y_size}, 
                                 grid_(x_size, std::vector<int>(y_size)) {}

  void BuildEnviroment(const std::string& input_file_name);

  int GetX() {return x_size_;};
  int GetY() {return y_size_;};

  int GetCell(const int x, const int y) const {return grid_[x][y];}
  std::pair<int, int> GetOriginCoords() {return origin;}
  std::pair<int, int> GetDestinationCoords() {return destination;}
  double GetEntryCost(int r, int c) const;

  bool IsValid(int r, int c) const {
    return (r >= 0) && (r < x_size_) && (c >= 0) && (c < y_size_);
  }
  bool IsObstacle(int r, int c) const {return GetCell(r,c) == -1;}
 private:
  int x_size_;
  int y_size_;
  std::vector<std::vector<int>> grid_;
  std::pair<int, int> origin;
  std::pair<int, int> destination;
};

#endif