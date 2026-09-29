/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * 
 * @subject: Inteligencia Artificial - Práctica 1. Búsqueda A*
 * 
 * @file functions.h
 * @author Ezequiel Hernández Poleo (alu0101735399@ull.edu.es)
 * @date 2026-09-28
 * @brief This file contains the function initialization for the main functions
 *        used by the main program.
 */

#include "../include/grid.h"
#include "../include/node.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

double CalcHeuristic(int current_r, int current_c, int dest_r, int dest_c);
std::vector<std::pair<int, int>> RebuildPath(const std::shared_ptr<Node>& destination_node);
void WriteTraceLine(std::ostream& trace, int iteration, const OpenNodeList& open, const ClosedNodeList& closed);
void WriteResult(std::ostream& output, const std::vector<std::pair<int, int>>& path, double cost);
void AStarSearch(const Grid& grid, const std::pair<int, int>& origin_coords, const std::pair<int, int>& destination_coords, const std::string& map_output_file, const std::string& trace_output_file);