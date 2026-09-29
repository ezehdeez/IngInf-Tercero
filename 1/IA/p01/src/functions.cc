/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: Inteligencia Artificial - Práctica 1. Búsqueda A*
 * 
 * @file functions.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-09-28
 * @brief Declaration of the main functions used in the main program.
 */

#include "../include/functions.h"

/**
 * @brief Function that returns the Heuristic Function value.
 * 
 * @param current_r 
 * @param current_c 
 * @param dest_r 
 * @param dest_c 
 * @return double 
 */
double CalcHeuristic(int current_r, int current_c, int dest_r, int dest_c) {
  return 2.0 * (std::abs(dest_r - current_r) + std::abs(dest_c - current_c));
}

/**
 * @brief Starting in the destination Node this function will return a vector
 *        with the path from origin to destination node. It makes this by 
 *        jumping from parent to parent (attribute from Class Node).
 * 
 * @param destination_node 
 * @return std::vector<std::pair<int, int>> 
 */
std::vector<std::pair<int, int>> RebuildPath(const std::shared_ptr<Node>& destination_node) {
  std::vector<std::pair<int, int>> path;
  for(auto current = destination_node; current != nullptr;
       current = current->parent_) {
    path.emplace_back(current->r_, current->c_);
  }
  // The obtained path starts in destination so it should inverse it.
  std::reverse(path.begin(), path.end());
  return path;
}

/**
 * @brief Function in charge of the output for each iteration. It can be used
 *        both for console and files, so it let's the program have both outputs.
 * 
 * @param trace 
 * @param iteration 
 * @param open 
 * @param closed 
 */
void WriteTraceLine(std::ostream& trace, int iteration, const OpenNodeList& open, const ClosedNodeList& closed) {
  auto pending = open;
  trace << "Iteración " << iteration << '\n' << "Abiertos = ";
  bool first = true;
  while (!pending.empty()) {
    const auto& node = pending.top();
    if (!first) {
      trace << ", ";
    }
    trace << '(' << node->r_ << ',' << node->c_ << ')';
    first = false;
    pending.pop();
  }
  trace << "\nCerrados = ";
  first = true;
  for (const auto& [r, c] : closed) {
    if (!first) {
      trace << ", ";
    }
    trace << '(' << r << ',' << c << ')';
    first = false;
  }
  trace << "\n\n";
}

/**
 * @brief This function writes the final path with its cost.
 * 
 * @param output 
 * @param path 
 * @param cost 
 */
void WriteResult(std::ostream& output, const std::vector<std::pair<int, int>>& path, double cost) {
  output << "Camino: ";
  for (std::size_t i = 0; i < path.size(); ++i) {
    if (i > 0) {
      output << " -> ";
    }
    output << '(' << path[i].first << ',' << path[i].second << ')';
  }
  output << "\nCoste: " << cost << '\n';
}

void AStarSearch(const Grid& grid, const std::pair<int, int>& origin_coords, const std::pair<int, int>& destination_coords, const std::string& map_output_file, const std::string& trace_output_file) {
  OpenNodeList open;
  ClosedNodeList closed;
  const int offset_r[] = {-1, 1, 0, 0};
  const int offset_c[] = {0, 0, 1, -1};
  std::ofstream trace_file{trace_output_file};
  if (!trace_file.is_open()) {
    throw std::runtime_error("Cannot open output file " + trace_output_file + ".");
  }

  const double h0 = CalcHeuristic(origin_coords.first, origin_coords.second, destination_coords.first, destination_coords.second);
  open.push(std::make_shared<Node>(origin_coords.first, origin_coords.second, 0.0, h0));

  int iteration = 0;
  while(!open.empty()) {
    ++iteration;
    WriteTraceLine(std::cout, iteration, open, closed);
    WriteTraceLine(trace_file, iteration, open, closed);

    const std::shared_ptr<Node> current = open.top();
    open.pop();
    if(closed.count({current->r_, current->c_}) > 0) {
      continue;
    }
    closed.insert({current->r_, current->c_});

    if(current->r_ == destination_coords.first && current->c_ == destination_coords.second) {
      const auto path = RebuildPath(current);
      grid.WritePath(path, map_output_file);
      WriteResult(std::cout, path, current->g_);
      WriteResult(trace_file, path, current->g_);
      return;
    }

    for(int i = 0; i < 4; ++i) {
      const int next_r = current->r_ + offset_r[i];
      const int next_c = current->c_ + offset_c[i];
      if(!grid.IsValid(next_r, next_c) || grid.IsObstacle(next_r, next_c) || closed.count({next_r, next_c}) > 0) {
        continue;
      }
      const double new_g = current->g_ + grid.GetEntryCost(next_r, next_c);
      const double new_h = CalcHeuristic(next_r, next_c, destination_coords.first, destination_coords.second);
      open.push(std::make_shared<Node>(next_r, next_c, new_g, new_h, current));
    }
  }

  std::cout << "No se ha encontrado solución.\n";
  trace_file << "No se ha encontrado solución.\n";
}
