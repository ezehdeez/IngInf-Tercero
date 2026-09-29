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
 * @brief Main class for containing the grid with the cells values.
 */


#include <fstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#ifndef GRID_H
#define GRID_H

class Grid {
 public:
  Grid() = default;

  // Load file into a grid object
  void BuildEnvironment(const std::string& input_file_name);

  // Getters
  int GetRows() const { return rows_; }
  int GetColumns() const { return columns_; }
  int GetCell(int matrix_row, int matrix_column) const {
    return grid_.at(matrix_row).at(matrix_column);
  }
  std::pair<int, int> GetOriginCoords() const { return origin_; }
  std::pair<int, int> GetDestinationCoords() const { return destination_; }
  double GetEntryCost(int r, int c) const;

  // Utility methods
  bool IsValid(int r, int c) const {
    return r >= 0 && r < rows_ && c >= 0 && c < columns_;
  }
  bool IsObstacle(int r, int c) const;
  void WritePath(const std::vector<std::pair<int, int>>& path,
                 const std::string& output_file_name) const;

 private:
  int rows_{0};
  int columns_{0};
  std::vector<std::vector<int>> grid_;
  std::pair<int, int> origin_{-1, -1};
  std::pair<int, int> destination_{-1, -1};
};

#endif