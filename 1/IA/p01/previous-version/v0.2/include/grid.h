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
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#ifndef GRID_H
#define GRID_H

class Grid {
 public:
  Grid(int rows, int columns)
      : rows_{rows}, columns_{columns},
        grid_(rows, std::vector<int>(columns)) {}

  void BuildEnvironment(const std::string& input_file_name);

  int GetRows() const { return rows_; }
  int GetColumns() const { return columns_; }

  int GetCell(int matrix_row, int matrix_column) const {
    return grid_.at(matrix_row).at(matrix_column);
  }
  std::pair<int, int> GetOriginCoords() const { return origin_; }
  std::pair<int, int> GetDestinationCoords() const { return destination_; }
  double GetEntryCost(int r, int c) const;

  bool IsValid(int r, int c) const {
    return r >= 1 && r <= rows_ && c >= 1 && c <= columns_;
  }
  bool IsObstacle(int r, int c) const;
  void WritePath(const std::vector<std::pair<int, int>>& path,
                 const std::string& output_file_name) const;

 private:
  int rows_;
  int columns_;
  std::vector<std::vector<int>> grid_;
  std::pair<int, int> origin_{0, 0};
  std::pair<int, int> destination_{0, 0};
};

#endif