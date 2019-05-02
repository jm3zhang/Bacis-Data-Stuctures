/*****************************************
 * UW User ID:  jm3zhang
 * Submitted for ECE 250
 * Semester of Submission:  (Winter) 2017
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 *  the provided code.
 *****************************************/

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>

// include whatever classes you want

class Weighted_graph {
private:
    // your implementation here
    //  you can add both private member variables and private member functions
    int matrix_capacity;
    int total_egdes;
    
    int *degree_array;
    double *adjacency_matrix;
    double *dijkstra_matrix;
    double *vertex_weight;
    
    static const double INF;
    
public:
    Weighted_graph( int = 51 );
    ~Weighted_graph();
    
    int degree( int ) const;
    int edge_count() const;
    double adjacent( int, int ) const;
    double distance( int, int ) const;
    
    void insert( int, int, double );
    
    // Friends
    
    friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

// Your implementation here

// You can modify this function however you want:  it will not be tested

/*Constructor*/
Weighted_graph::Weighted_graph( int n ):
matrix_capacity( 50 ),
total_egdes( 0 ),
degree_array( new int[matrix_capacity]),
adjacency_matrix(  new double[matrix_capacity * matrix_capacity]),
dijkstra_matrix(  new double[matrix_capacity * matrix_capacity]),
vertex_weight( new double[matrix_capacity]){
    
}

/*Destructor*/
Weighted_graph::~Weighted_graph(){
    delete [] degree_array;
    delete [] adjacency_matrix;
    delete [] dijkstra_matrix;
    delete [] vertex_weight;
}

/*Accessors*/
int Weighted_graph::degree( int n ) const {
    return degree_array[n+1];
} //done

int Weighted_graph::edge_count() const {
    return total_egdes;
} //done

double Weighted_graph::adjacent( int m, int n ) const {
    try{
        if(m > matrix_capacity || m < 1 || n > matrix_capacity || n < 1){
            throw illegal_argument();
        }
    }
    catch(int a){
        
    }
    
    if (m == n){
        return 0;
    }
    
    if (adjacency_matrix[m * n]){
        return adjacency_matrix[m * n];
    }
    else{
        return INF;
    }
} //done

double Weighted_graph::distance( int m, int n ) const {
    m += 1;
    n += 1;
    //return adjacency_matrix[4 * 5];
    if (m == n){
        return 0.0;
    }
    
    for (int a = 1; a <= matrix_capacity; a++){
        vertex_weight[a]  = INF;
    }
    vertex_weight[m] = 0;
    
    //double partial_shortest_distance = INF;
    //double partial_shortest_distance_vertex;
    
    /*if (adjacency_matrix[m * n]==0){
        return INF;
    }*/
    
    while (1){
        if (m == n){
            break;
        }
        
        double smallest_partial_Weight = INF;
        double smallest_partial_Weight_vertex;
        
        //int check = 0;
        for (int a = 1; a <= 51; a++ ) {
           // return dijkstra_matrix[m*a]
            if (dijkstra_matrix[m * a]!=0 && m != a){
                //check = 1;
                if (vertex_weight[a] == INF){
                    vertex_weight[a] = dijkstra_matrix[m*a];
                    if (smallest_partial_Weight > dijkstra_matrix[m*a]) {
                        smallest_partial_Weight = dijkstra_matrix[m*a];
                        smallest_partial_Weight_vertex = a;
                    }
                }
                else if (vertex_weight[a] <= (vertex_weight[a] + dijkstra_matrix[m*a])){
                    vertex_weight[a] += dijkstra_matrix[m*a];
                    if (smallest_partial_Weight > dijkstra_matrix[m*a]) {
                        smallest_partial_Weight = dijkstra_matrix[m*a];
                        smallest_partial_Weight_vertex = a;
                    }
                }
                dijkstra_matrix[a*m] = 0;
            }
        }
        return smallest_partial_Weight;
        if (smallest_partial_Weight == INF) {
            return INF;
        }
        m = smallest_partial_Weight_vertex;
    }
    
    for (int b = 1; b <= 51; b++) {
        for (int c = 1; c <= 51; c++) {
            dijkstra_matrix[b*c] = adjacency_matrix[b*c];
        }
    }
    
    /*//return dijkstra_matrix[m*n];
    for (int c = 1; ;c++){
        if (c == 1){
            //int check1 = 0;
            for(int b = 1; b <= matrix_capacity; b++){
                //check1 = 0;
                if (dijkstra_matrix[m * n]!= 0 && dijkstra_matrix[m * b] < vertex_weight[b] && dijkstra_matrix[m * b] != -1) {
                    //check1 = 1;
                    //if ((vertex_weight[b] + dijkstra_matrix[m * b]) < vertex_weight[b]){
                        vertex_weight[b] = dijkstra_matrix[m * b];
                    //}
                    if (vertex_weight[b] < partial_shortest_distance){
                        partial_shortest_distance = dijkstra_matrix[m * b];
                        partial_shortest_distance_vertex = b;
                    }
                    dijkstra_matrix[m * b] = -1;
                    dijkstra_matrix[b * m] = -1;
                }
            }
            //return partial_shortest_distance;
            //return INF;
            if (partial_shortest_distance == 0){
                return INF;
            }
            
            m = partial_shortest_distance_vertex;
            //partial_shortest_distance = INF;
            continue;
        }
        return vertex_weight[2];
        //partial_shortest_distance = INF;
        if(m == n){
            break;
        }
        //int check1 = 0;
        for(int b = 1; b <= matrix_capacity; b++){
           // int check1 = 0;
            if (dijkstra_matrix[m * b] < vertex_weight[b]&&  dijkstra_matrix[m * b] != -1) {
               // check1 = 1;
                if ((vertex_weight[b] + dijkstra_matrix[m * b]) < vertex_weight[b]){
                    vertex_weight[b] += dijkstra_matrix[m * b];
                }
                if (vertex_weight[b] < partial_shortest_distance){
                    partial_shortest_distance = dijkstra_matrix[m * b];
                    partial_shortest_distance_vertex = b;
                }
                dijkstra_matrix[m * b] = -1;
                dijkstra_matrix[b * m] = -1;
            }
        }
        //return partial_shortest_distance_vertex;
        if (partial_shortest_distance == 0){
            return INF;
        }
        m = partial_shortest_distance_vertex;
    }
    
    
    
    
    /*double shortest_distance = 0;
     double partial_distance = 0;
     double partial_shortest_distance = infinity();
     while(0){
     if (m == n){
     break;
     }
     for (int i = 1; i <= matrix_capacity; i++){
     if (dijkstra_matrix[m * i] && dijkstra_matrix[m * i] != -1){
     partial_distance = dijkstra_matrix[m * i];
     dijkstra_matrix[m * i] = -1;
     }
     if(partial_distance > 0 || partial_distance < partial_shortest_distance){
     partial_shortest_distance = partial_distance;
     partial_distance = 0;
     }
     }
     }*/
    
    return vertex_weight[1];
}

/*Mutators*/
void Weighted_graph::insert( int m, int n, double w ){
    m += 1;
    n += 1;
    
    try{
        if(w <= 0 || n == m || m > matrix_capacity || m < 1 || n > matrix_capacity || n < 1){
            throw illegal_argument();
        }
    }
    catch(int a){
        
    }
    
    if(w > 0){
        //if that edge exists
        if(adjacency_matrix[m * n]){
            adjacency_matrix[m * n] = w;
            //adjacency_matrix[n * m] = w;
            dijkstra_matrix[m * n] = w;
            //dijkstra_matrix[n * m] = w;
            return;
        }
        //new edge
        adjacency_matrix[m * n] = w;
        //adjacency_matrix[n * m] = w;
        dijkstra_matrix[m * n] = w;
        //dijkstra_matrix[n * m] = w;
        total_egdes ++;
        if (degree_array[m]||degree_array[n]){
            degree_array[m] ++;
            degree_array[n] ++;
        }
        else {
            degree_array[m] = 1;
            degree_array[n] = 1;
        }
        
    }
    
    return;
}

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();


std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
    return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif