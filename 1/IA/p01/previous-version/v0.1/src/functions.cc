/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: 
 * 
 * @file functions.cc
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-09-23
 * @brief 
 */

#include "../include/grid.h"
#include "../include/node.h"

#include <cmath>
#include <set>

double CalcHeuristic(int current_r, int current_c, int dest_r, int dest_c) {
  int dif_r = std::abs(dest_r - current_r);
  int dif_c = std::abs(dest_c - current_c);
  return 2.0 * (dif_r + dif_c);
}

void AStarSearch(const Grid& grid, std::pair<int, int> origin_coords, std::pair<int, int> destination_coords) {
  OpenNodeList open;
  ClosedNodeList closed;
  // Operations
  const int offset_r[] = {-1, 1, 0, 0};
  const int offset_c[] = {0, 0, 1, -1};

  // Algorithm initialization
  double h0 = CalcHeuristic(origin_coords.first, origin_coords.second, destination_coords.first, destination_coords.second);
  std::shared_ptr<Node> starter_node = std::make_shared<Node>(origin_coords.first, origin_coords.second, 0.0, h0);
  open.push(starter_node);

  int iteration = 0;

  // Ask for trace

  // Ask for output file

  while(!open.empty()) {
    // IMPRIMIR AQUI

    // --

    std::shared_ptr<Node> current = open.top();
    open.pop();

    // 
    if(closed.count(std::make_pair(current->r_, current->c_)) > 0) continue;

    closed.insert(std::make_pair(current->r_, current->c_));

    // Check if we arrive the destination
    if (current->r_ == destination_coords.first && current->c_ == destination_coords.second) {
      RebuildAndSavePath(current, grid);
      return;
    }

    // Generate 4 neighbours
    for (int i = 0; i < 4; ++i) {
      int next_r = current->r_ + offset_r[i];
      int next_c = current->c_ + offset_c[i];

      // Validate limits, get obstacle info and check in closed nodes.
      if(grid.IsValid(next_r, next_c) && !grid.IsObstacle(next_r, next_c)) {
        if(closed.count(std::make_pair(next_r, next_c)) > 0) {
          continue;
        }

        double entry_cost = grid.GetEntryCost(next_r, next_c);
        double new_g = current->g_ + entry_cost;
        double new_h = CalcHeuristic(next_r, next_c, destination_coords.first, destination_coords.second);

        std::shared_ptr<Node> sucesor = std::make_shared<Node>(next_r, next_c, new_g, new_h, current);
        open.push(sucesor);
      }
  }
  }
}

void RebuildAndSavePath(std::shared_ptr<Node> destination_node, const Grid& grid) {
  std::vector<std::pair<int, int>> path;
    std::shared_ptr<Node> current_node = destination_node;

    // Go through all nodes from the destination to the origin
    while(current_node != nullptr) {
        path.push_back(std::make_pair(current_node->r_, current_node->c_));
        current_node = current_node->parent_;
    }

    // Invert to get the sequence from s0 to sn
    std::reverse(path.begin(), path.end());

    // Print final path with the cost
    std::cout << "Camino: ";
    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << "(" << path[i].first << "," << path[i].second << ")";
        if (i + 1 < path.size()) std::cout << " -> ";
    }
    std::cout << "\nCoste: " << destination_node->g_ << std::endl;
}