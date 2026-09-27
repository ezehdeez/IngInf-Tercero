/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: Inteligencia Artificial - Práctica 1. Búsqueda A*
 * 
 * @file node.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-09-23
 * @brief 
 */

#include <memory>
#include <set>
#include <queue>

using OpenNodeList = std::priority_queue<std::shared_ptr<Node>, std::vector<Node>, CompareFNode>;
using ClosedNodeList = std::set<Node>;

struct Node {
  int r_, c_;
  double f_;
  double g_;
  double h_;
  std::shared_ptr<Node> parent_;

  Node(int r, int c, double g, double h, 
  std::shared_ptr<Node> parent = nullptr) : r_{r}, c_{c}, f_{g + h}, g_{g}, h_{h}, 
  parent_{parent} {}
};

struct CompareFNode {
  bool operator()(const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b) {
    return a->f_ > b->f_;
  }
};