// Node.h
#ifndef NODE_H
#define NODE_H

#include <QVector>//this library is used to create vectors


struct Node {//a node class to create a graph
    int x, y; //co-ordinates as well as size of a node
    bool isObstacle;//to check if a node is an obstacle or not
    QVector<Node*> neighbors;//to store neighbours of a node
};

struct Edge {//used to find in the funtion to find the shortest path
    Node* source;//stores the first node
    Node* destination;//stores the second node
    int weight;//used to store th number of nodes trespassed to compare weight(no.of nodes trapessad) of different paths to find shortest path
};

#endif // NODE_H
