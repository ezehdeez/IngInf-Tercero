#include "../include/grid.h"
#include "../include/node.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

double CalcHeuristic(int current_r, int current_c, int dest_r, int dest_c) {
  return 2.0 * (std::abs(dest_r - current_r) + std::abs(dest_c - current_c));
}

namespace {

std::vector<std::pair<int, int>> RebuildPath(
    const std::shared_ptr<Node>& destination_node) {
  std::vector<std::pair<int, int>> path;
  for (auto current = destination_node; current != nullptr;
       current = current->parent_) {
    path.emplace_back(current->r_, current->c_);
  }
  std::reverse(path.begin(), path.end());
  return path;
}

void WriteTraceLine(std::ostream& trace, int iteration, const OpenNodeList& open,
                    const ClosedNodeList& closed) {
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

void WriteResult(std::ostream& output, const std::vector<std::pair<int, int>>& path,
                 double cost) {
  output << "Camino: ";
  for (std::size_t i = 0; i < path.size(); ++i) {
    if (i > 0) {
      output << " -> ";
    }
    output << '(' << path[i].first << ',' << path[i].second << ')';
  }
  output << "\nCoste: " << cost << '\n';
}

}  // namespace

void AStarSearch(const Grid& grid, const std::pair<int, int>& origin_coords,
                 const std::pair<int, int>& destination_coords,
                 const std::string& map_output_file,
                 const std::string& trace_output_file) {
  OpenNodeList open;
  ClosedNodeList closed;
  const int offset_r[] = {1, -1, 0, 0};
  const int offset_c[] = {0, 0, 1, -1};
  std::ofstream trace_file{trace_output_file};
  if (!trace_file.is_open()) {
    throw std::runtime_error("Cannot open output file " + trace_output_file + ".");
  }

  const double h0 = CalcHeuristic(origin_coords.first, origin_coords.second,
                                  destination_coords.first, destination_coords.second);
  open.push(std::make_shared<Node>(origin_coords.first, origin_coords.second, 0.0,
                                   h0));

  int iteration = 0;
  while (!open.empty()) {
    ++iteration;
    WriteTraceLine(std::cout, iteration, open, closed);
    WriteTraceLine(trace_file, iteration, open, closed);

    const std::shared_ptr<Node> current = open.top();
    open.pop();
    if (closed.count({current->r_, current->c_}) > 0) {
      continue;
    }
    closed.insert({current->r_, current->c_});

    if (current->r_ == destination_coords.first &&
        current->c_ == destination_coords.second) {
      const auto path = RebuildPath(current);
      grid.WritePath(path, map_output_file);
      WriteResult(std::cout, path, current->g_);
      WriteResult(trace_file, path, current->g_);
      return;
    }

    for (int i = 0; i < 4; ++i) {
      const int next_r = current->r_ + offset_r[i];
      const int next_c = current->c_ + offset_c[i];
      if (!grid.IsValid(next_r, next_c) || grid.IsObstacle(next_r, next_c) ||
          closed.count({next_r, next_c}) > 0) {
        continue;
      }
      const double new_g = current->g_ + grid.GetEntryCost(next_r, next_c);
      const double new_h =
          CalcHeuristic(next_r, next_c, destination_coords.first,
                        destination_coords.second);
      open.push(std::make_shared<Node>(next_r, next_c, new_g, new_h, current));
    }
  }

  std::cout << "No se ha encontrado solución.\n";
  trace_file << "No se ha encontrado solución.\n";
}
