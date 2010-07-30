#include <iostream>
#include <sys/time.h>
#include "Edge.hpp"
#include "Graph.hpp"

/* To subtract time in micro second precision
 * (from http://stackoverflow.com/questions/1468596
 * /c-programming-calculate-elapsed-time-in-milliseconds-unix)
 *
 */

int timeval_subtract(struct timeval *result, struct timeval *t2, struct timeval *t1) {
    long int diff = (t2->tv_usec + 1000000 * t2->tv_sec) - (t1->tv_usec + 1000000 * t1->tv_sec);
    result->tv_sec = diff / 1000000;
    result->tv_usec = diff % 1000000;

    return (diff<0);
}

int main() {
    int width, height;

    std::cin >> width;  //Get the width
    std::cin >> height; //Now the height

    //STL vector holds the type information for a particular room
    std::vector<std::vector< int > > rooms(height, std::vector< int >(width));
    
    int num, num_count=0;
    for(int i=0;i<height;i++) {  //Now the rest
      for(int j=0;j<width;j++) {
        std::cin >> num;
        rooms[i][j] = num;
        ++num_count;
      }
    }

    //Create Graph object
    Graph *g = new Graph(width, height);

    //Add horizontal edges to graph
    for(int i=0;i<height;i++) {
        for(int j=0;j<width-1;j++) {
            if(rooms[i][j] != 1 && rooms[i][j+1] != 1) {
                Vertex v1 = std::make_pair(i,j);
                Vertex v2 = std::make_pair(i, j+1);
                Edge *e = new Edge(v1, v2);
                g->add_edge(*e);
                /*#ifdef DEBUG
                std::cout << "[("  << i << "," << j << "), (" << i << ","
                    << j+1 << ")]" << std::endl;
                #endif*/
            }
        }
    }

    /*#ifdef DEBUG
    std::cout << std::endl;
    #endif*/

    //Add vertical edges to graph
    for(int i=0;i<height-1;i++) {
        for(int j=0;j<width;j++) {
            if(rooms[i][j] != 1 && rooms[i+1][j] != 1) {
            Vertex v1 = std::make_pair(i,j);
            Vertex v2 = std::make_pair(i+1, j);
            Edge *e = new Edge(v1, v2);
            g->add_edge(*e);
            /*#ifdef DEBUG
            std::cout << "[("  << i << "," << j << "), (" << i+1 << "," << j
                << ")]" << std::endl;
            #endif*/
            }
        }
    }
    /*#ifdef DEBUG
    std::cout << std::endl;
    #endif*/

    Vertex v2, v3;

    /* Find and store vertices labelled 2 and 3
     * vertex 2 is the starting point and vertex 3
     * is the destination
     */
    for(int i=0;i<height;i++) {
        for(int j=0;j<width;j++) {
            if(rooms[i][j] == 2) {
                v2 = std::make_pair(i,j);
            }
            if(rooms[i][j] == 3) {
                v3 = std::make_pair(i,j);
            }
        }
    }

    /*Vertex v_abc = std::make_pair(0, 3);

    for(int i=0;i<g->num_out_edges(v_abc);i++) {
        std::cout << g->out_vertex(v_abc,i) << " ";
    }
    std::cout << " " << std::endl;*/
    struct timeval start_point, term_point, time_diff;

    gettimeofday(&start_point, NULL);

    //int no_longest_paths = g->constrained_dfs_longest_paths(v2, v3);
    int no_longest_paths = g->iterative_c_dfs_longest_paths(v2, v3);

    gettimeofday(&term_point, NULL);
    timeval_subtract(&time_diff, &term_point, &start_point);


    std::cout << no_longest_paths;

    #ifdef DEBUG
    std::cout << "\nExecution Time: " << time_diff.tv_sec
            << "." << time_diff.tv_usec << "s" << std::endl;
    #endif

    return(0);
}
