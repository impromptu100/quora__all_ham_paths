/*
 * File:   Edge.cpp
 * Author: praveer
 *
 * Created on July 26, 2010, 10:18 AM
 */

#include "Edge.hpp"
#include <string>

Edge::Edge(std::pair<int,int> vertex_1, std::pair<int,int> vertex_2) {
    v1 = vertex_1;
    v2 = vertex_2;
}

Edge::Edge(Edge& orig) {
    v1 = orig.get_start();
    v2 = orig.get_end();
}

std::pair<int, int> Edge::get_start() {
    return v1;
}

std::pair<int, int> Edge::get_end() {
    return v2;
}

int Edge::get_startx() {
    return v1.first;
}

int Edge::get_starty() {
    return v1.second;
}

int Edge::get_endx() {
    return v2.first;
}

int Edge::get_endy() {
    return v2.second;
}

bool Edge::is_bound(int w, int h) {
    if(get_startx() >=0 && get_startx() < h &&
            get_starty() >=0 && get_starty() < w &&
            get_endx() >=0 && get_endx() < h &&
            get_endx() >=0 && get_endx() < w) {
        return true;
    }
    else {
        return false;
    }
}