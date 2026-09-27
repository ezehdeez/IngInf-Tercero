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
#include <queue>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

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
  bool operator()(const std::shared_ptr<Node>& a,
                  const std::shared_ptr<Node>& b) const {
    if (a->f_ != b->f_) {
      return a->f_ > b->f_;
    }
    if (a->h_ != b->h_) {
      return a->h_ > b->h_;
    }
    return std::tie(a->r_, a->c_) > std::tie(b->r_, b->c_);
  }
};

using OpenNodeList =
    std::priority_queue<std::shared_ptr<Node>,
                        std::vector<std::shared_ptr<Node>>, CompareFNode>;
using ClosedNodeList = std::set<std::pair<int, int>>;