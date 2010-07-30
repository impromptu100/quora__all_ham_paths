/* 
 * File:   Graph.cpp
 * Author: praveer
 * 
 * Created on July 26, 2010, 11:07 AM
 */

#include "Graph.hpp"
#include <iostream>
#include <iomanip>
#include <stack>

#define VERTEX_TO_INT(v) ((v.first*w) + v.second)
#define INT_TO_VERTEX(i) (std::make_pair(i/w, i%w))

/**************** Direction Macros ************************/
#define RIGHT 0
#define LEFT 1
#define UP 2
#define DOWN 3

/*
 * Graph is assumed to be undirected for purpose of problem
 * and the 2d position is retained natively, except when storing vertex and
 * edge information in tr1::unordered_map and vector respectively
 *
 */
Graph::Graph(int width, int height) {
    w = width;
    h = height;
    edge_count = 0;
    vertex_count = 0;
    adj_list.resize(w*h);
}

Graph::Graph(Graph& orig) {
    w = orig.get_w();
    h = orig.get_h();
    //TODO: import vertices and edges
}

int Graph::get_w() {
    return w;
}

int Graph::get_h() {
    return h;
}

bool Graph::is_vertex_present(Vertex& v) {
    Vertex vert = v;
    int vertex_i = VERTEX_TO_INT(vert);
    VertexList::iterator iter;
    iter = vertices.find(vertex_i);
    if(iter != vertices.end()) {
        return true;
    }
    else {
        return false;
    }
}

void Graph::print_vertices() {
    VertexList::iterator iter = vertices.begin();
    for(;iter != vertices.end(); ++iter) {
        //std::cout << *iter << " ";
    }
    std::cout << std::endl;
}

void Graph::add_vertex(Vertex& v) {
    Vertex vert = v;
    int i = VERTEX_TO_INT(v);
    vertices.insert(std::make_pair(i, i));
    /* Increment vertex_count */
    ++vertex_count;
}

/* Adds the vertices if required and then adds the edge
 * Assumes graph is undirected/(bidirectional for every edge)
 */

bool Graph::add_edge(Edge& e) {
    if(e.is_bound(get_w(), get_h())) { //Check if the vertex is within bound
        Vertex v_start = e.get_start(), v_end = e.get_end();
        /* Add vertices to vertices Hash table */
        if(!is_vertex_present(v_start)) add_vertex(v_start);
        if(!is_vertex_present(v_end)) add_vertex(v_end);
        /* Now add edges to Adjacency List */
        adj_list[VERTEX_TO_INT(v_start)].push_back(VERTEX_TO_INT(v_end));
        adj_list[VERTEX_TO_INT(v_end)].push_back(VERTEX_TO_INT(v_start));
        /* Increment edge_count */
        ++edge_count;
        return true;
    }
    else {
        return false;
    }
}

int Graph::num_out_edges(Vertex& v) {
    return(adj_list[VERTEX_TO_INT(v)].size());
}

int Graph::out_vertex(Vertex& v, int index) {
    return(adj_list[VERTEX_TO_INT(v)][index]);
}

int Graph::num_edges() {
    return(edge_count);
}

int Graph::num_vertices() {
    return(vertex_count);
}

Graph::~Graph() {
}

int Graph::iterative_c_dfs_longest_paths(Vertex& src, Vertex& dst) {
    VertexList visited_hm;  //unordered hash table for storing the
                                     //list of visited vertices
    int visited[num_vertices()], iteration[num_vertices()], next_vertex,
            max_out_edges[num_vertices()], max_path = num_vertices()-1;
    int visit_length=0, 
            barrier_length = (w+1/2) + (h+1/2), vertex1, vertex2;
    int src_int = VERTEX_TO_INT(src), dst_int = VERTEX_TO_INT(dst),
            no_maxpaths=0;

    for(int i=0;i<num_vertices();i++) { //set all iterations to 0
        iteration[i] = 0;
    }
    for(int i=0, j=0;i < w*h;i++) {
        if(vertices.find(i) != vertices.end()) {
            max_out_edges[j] = adj_list[i].size();
            ++j;
        }
    }

    visited[visit_length] = src_int;
    visited_hm.insert(std::make_pair(src_int, src_int));
    ++visit_length;
    while(iteration[0] != max_out_edges[0]) {

        //if no path out exists backtrace and find next feasible path
        if(iteration[visit_length-1] == max_out_edges[visited[visit_length-1]]) {
            visited_hm.erase(visited[visit_length-1]);
            iteration[visit_length-1] = 0;
            ++iteration[visit_length-2];
            --visit_length;
            continue;
        }
        
        next_vertex = adj_list[visited[visit_length-1]]
                [iteration[visit_length-1]];
        //Assign direction
        if(visit_length > barrier_length &&
                ((max_out_edges[visited[visit_length-1]] == 4 &&
                max_out_edges[next_vertex] == 3) ||
                visited_hm.find(next_vertex) != visited_hm.end())) {
            //
            // If there is a barrier ahead after travelling atleast 
            // (w+1)/2 + (h+1)/2
            // then try to avoid the following no-gain paths through that
            // vertex by back-tracking to previous vertex in the visited path
            //
            if(next_vertex > visited[visit_length-1]) {
                //In this case direction can be either right or down
                if(next_vertex == visited[visit_length-1]+1) {
                    //Now the direction has to be right
                    vertex1 = next_vertex -w;
                    vertex2 = next_vertex +w;
                    if((vertices.find(vertex1) != vertices.end() &&
                        vertices.find(vertex2) != vertices.end() &&
                        visited_hm.find(vertex1) == visited_hm.end() &&
                        visited_hm.find(vertex2) == visited_hm.end())) {
                            //Now we can safely backtrack one vertex
                            ++iteration[visit_length-1];
                            continue;
                    }
                }
                else {
                    //Now the direction is down
                    vertex1 = next_vertex -1;
                    vertex2 = next_vertex +1;
                    if(vertices.find(vertex1) != vertices.end() &&
                        vertices.find(vertex2) != vertices.end() &&
                        visited_hm.find(vertex1) == visited_hm.end() &&
                        visited_hm.find(vertex2) == visited_hm.end()) {
                            //Now we can safely backtrack one vertex
                            ++iteration[visit_length-1];
                            continue;
                    }
                }
            }
            else {
                //In this case direction can be either left or up
                if(next_vertex == visited[visit_length-1] -1) {
                    //Direction is left
                    vertex1 = next_vertex -w;
                    vertex2 = next_vertex +w;
                    if(vertices.find(vertex1) != vertices.end() &&
                        vertices.find(vertex2) != vertices.end() &&
                        visited_hm.find(vertex1) == visited_hm.end() &&
                        visited_hm.find(vertex2) == visited_hm.end()) {
                            //Now we can safely backtrack one vertex
                        ++iteration[visit_length-1];
                        continue;
                    }
                }
                else {
                    vertex1 = next_vertex -1;
                    vertex2 = next_vertex +1;
                    if(vertices.find(vertex1) != vertices.end() &&
                        vertices.find(vertex2) != vertices.end() &&
                        visited_hm.find(vertex1) == visited_hm.end() &&
                        visited_hm.find(vertex2) == visited_hm.end()) {
                            //Now we can safely backtrack one vertex
                        ++iteration[visit_length-1];
                        continue;
                    }
                }
            }
        }
        
        if(next_vertex == dst_int) {  //if destination is found

            if(visit_length == max_path) {
                //found a path to dst after covering all vertices
                ++no_maxpaths;

                //break; //to find time it takes to find first ham path
            }
            
            if(iteration[visit_length-1] == max_out_edges[visited[visit_length-1]]) {
                visited_hm.erase(visited[visit_length-1]);
                iteration[visit_length-1] = 0;
                ++iteration[visit_length-2];
                --visit_length;
            }
            else {
                ++iteration[visit_length-1];
            }
        }
        //if next vertex is not yet visited visit it
        else if(visited_hm.find(next_vertex) == visited_hm.end()) {
            
            //Now mark the vertex as visited
            visited[visit_length] = next_vertex;
            visited_hm.insert(std::make_pair(next_vertex,
                next_vertex));
            ++visit_length;
        }
        else {
            ++iteration[visit_length-1];
        }
    }
    return(no_maxpaths);
}
