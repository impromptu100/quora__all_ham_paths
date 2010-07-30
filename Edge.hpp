/* 
 * File:   Edge.hpp
 * Author: praveer
 *
 * Created on July 26, 2010, 10:18 AM
 */

#ifndef _EDGE_HPP
#define	_EDGE_HPP

/*
 * An Edge consists of two vertices, in our implementation since the data
 * center is a 2D grid we use 2 coordinates to denote each vertex. Hence, each
 * vertex is represented as E(V1(x1, y1), V2(x2, y2)). Every edge is directional
 * from V1 to V2.
 *
 * TODO: weighted edge implementation
 *
 */
#include <utility>

typedef std::pair<int, int> Vertex;

class Edge
{
public:
    Edge(Vertex, Vertex);
    Edge(Edge &orig);
    int get_startx();
    int get_starty();
    int get_endx();
    int get_endy();
    bool is_bound(int w, int h);
    Vertex get_start();
    Vertex get_end();
private:
    Vertex v1;
    Vertex v2;
};

#endif	/* _EDGE_HPP */

