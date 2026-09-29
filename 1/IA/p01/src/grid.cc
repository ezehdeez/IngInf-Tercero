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
 * @brief Method declarations from the Grid Class. 
 */

#include "../include/grid.h"

#include <sstream>

/**
 * @brief Method to load tha values for any enviroment the a Grid object.
 * 
 * @param input_file_name 
 */
void Grid::BuildEnvironment(const std::string& input_file_name) {
  std::ifstream input_file{input_file_name};
  if(!input_file.is_open()) {
    throw std::runtime_error("File " + input_file_name + " cannot be open.");
  }
  std::vector<std::vector<int>> loaded_grid;
  std::string line;
  while(std::getline(input_file, line)) {
    std::istringstream line_stream{line};
    std::vector<int> loaded_row;
    int value = 0;
    while(line_stream >> value) {
      loaded_row.push_back(value);
    }
    if(loaded_row.empty()) {
      continue;
    }
    if(!loaded_grid.empty() && loaded_row.size() != loaded_grid.front().size()) {
      throw std::runtime_error("All map rows must have the same number of cells.");
    }
    loaded_grid.push_back(std::move(loaded_row));
  }
  
  if(loaded_grid.empty()) {
    throw std::runtime_error("The map cannot be empty.");
  }

  // Fill the first attributes
  grid_ = std::move(loaded_grid);
  rows_ = static_cast<int>(grid_.size());
  columns_ = static_cast<int>(grid_.front().size());
  origin_ = {-1, -1};
  destination_ = {-1, -1};

  // Search for origin and destination
  for (int matrix_row = 0; matrix_row < rows_; ++matrix_row) {
    for (int matrix_column = 0; matrix_column < columns_; ++matrix_column) {
      const int value = grid_[matrix_row][matrix_column];
      if (value == 0) {
        origin_ = {matrix_row, matrix_column};
      } else if (value == 10) {
        destination_ = {matrix_row, matrix_column};
      }
    }
  }
  if (origin_.first < 0 || destination_.first < 0) {
    throw std::runtime_error("The map must contain an origin (0) and destination (10).");
  }
}

/**
 * @brief Just to check if a cell in the enviroment is an obstacle.
 * 
 * @param r 
 * @param c 
 * @return bool 
 */
bool Grid::IsObstacle(int r, int c) const {
  if (!IsValid(r, c)) {
    return true;
  }
  return GetEntryCost(r, c) < 0;
}

/**
 * @brief Function to return the entry cost for a cell value.
 * 
 * @param r 
 * @param c 
 * @return double 
 */
double Grid::GetEntryCost(int r, int c) const {
  if (!IsValid(r, c)) {
    throw std::out_of_range("Coordinates outside the map.");
  }
  const int cell = grid_[r][c];
  return cell == 10 ? 2.0 : static_cast<double>(cell);
}

/**
 * @brief Function to get the output for the grid.
 * 
 * @param path 
 * @param output_file_name 
 */
void Grid::WritePath(const std::vector<std::pair<int, int>>& path, const std::string& output_file_name) const {
  std::vector<std::vector<std::string>> output(
      rows_, std::vector<std::string>(columns_));
  for (int matrix_row = 0; matrix_row < rows_; ++matrix_row) {
    for (int matrix_column = 0; matrix_column < columns_; ++matrix_column) {
      output[matrix_row][matrix_column] = std::to_string(grid_[matrix_row][matrix_column]);
    }
  }
  for(const auto& [r, c] : path) {
    output[r][c] = "*";
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