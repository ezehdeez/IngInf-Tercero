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

void Grid::BuildEnvironment(const std::string& input_file_name) {
  std::ifstream input_file{input_file_name};
  if (!input_file.is_open()) {
    throw std::runtime_error("File " + input_file_name + " cannot be open.");
  }
  for (int matrix_row = 0; matrix_row < rows_; ++matrix_row) {
    for (int matrix_column = 0; matrix_column < columns_; ++matrix_column) {
      int value = 0;
      if (!(input_file >> value)) {
        throw std::runtime_error("The map does not contain enough cells.");
      }
      grid_[matrix_row][matrix_column] = value;
      const int r = rows_ - matrix_row;
      const int c = matrix_column + 1;
      if (value == 0) {
        origin_ = {r, c};
      } else if (value == 10) {
        destination_ = {r, c};
      }
    }
  }
  int extra_value = 0;
  if (input_file >> extra_value) {
    throw std::runtime_error("The map contains more cells than expected.");
  }
  if (origin_.first == 0 || destination_.first == 0) {
    throw std::runtime_error("The map must contain an origin (0) and destination (10).");
  }
}

bool Grid::IsObstacle(int r, int c) const {
  if (!IsValid(r, c)) {
    return true;
  }
  return GetEntryCost(r, c) < 0;
}

double Grid::GetEntryCost(int r, int c) const {
  if (!IsValid(r, c)) {
    throw std::out_of_range("Coordinates outside the map.");
  }
  const int matrix_row = rows_ - r;
  const int matrix_column = c - 1;
  const int cell = grid_[matrix_row][matrix_column];
  return cell == 10 ? 2.0 : static_cast<double>(cell);
}

void Grid::WritePath(const std::vector<std::pair<int, int>>& path,
                     const std::string& output_file_name) const {
  std::vector<std::vector<std::string>> output(
      rows_, std::vector<std::string>(columns_));
  for (int matrix_row = 0; matrix_row < rows_; ++matrix_row) {
    for (int matrix_column = 0; matrix_column < columns_; ++matrix_column) {
      output[matrix_row][matrix_column] =
          std::to_string(grid_[matrix_row][matrix_column]);
    }
  }
  for (const auto& [r, c] : path) {
    output[rows_ - r][c - 1] = "*";
  }
  std::ofstream output_file{output_file_name};
  if (!output_file.is_open()) {
    throw std::runtime_error("Cannot open output file " + output_file_name + ".");
  }
  for (const auto& row : output) {
    for (int column = 0; column < columns_; ++column) {
      if (column > 0) {
        output_file << ' ';
      }
      output_file << row[column];
    }
    output_file << '\n';
  }
}