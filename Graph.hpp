/* 
 * File:   Graph.hpp
 * Author: praveer
 *
 * Created on July 26, 2010, 11:07 AM
 */

#include "Edge.hpp"
#include <utility>
#include <vector>
#include <tr1/unordered_map>

//use unordered_map (hash table) to store vertices
typedef std::pair<int, int> Vertex;
typedef std::tr1::unordered_map<int, int> VertexList;
typedef std::vector<std::vector <int> > AdjacencyList;

#ifndef _GRAPH_HPP
#define	_GRAPH_HPP

class Graph {
public:
    Graph(int width, int height);
    Graph(Graph& orig);
    virtual ~Graph();
    int get_w();
    int get_h();
    void add_vertex(Vertex& v);
    bool add_edge(Edge& e);
    int num_out_edges(Vertex& v);
    int out_vertex(Vertex& v, int index);
    bool is_vertex_present(Vertex& v);
    int num_edges();
    int num_vertices();
    void print_vertices();

    int constrained_dfs_longest_paths(Vertex& src, Vertex& dst);
    int iterative_c_dfs_longest_paths(Vertex& src, Vertex& dst);
private:
    int w;
    int h;
    VertexList vertices;
    int vertex_count;
    AdjacencyList adj_list;
    int edge_count;
};

#endif	/* _GRAPH_HPP */

