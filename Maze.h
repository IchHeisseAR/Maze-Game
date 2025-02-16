#ifndef MAZE_H
#define MAZE_H

#include <QVector>
// #include <QHash>
#include <QSet>
#include "Node.h"

class Maze {
public:
    Maze(int width, int height);//constructor definiton
    void generateMaze();//function to generate a maze
    void addObstacles();//function to generate random obstacles
    QVector<Node*> shortestPath(Node* start, Node* end);//function to find and return shortest path between current position of player and the end Node
    Node* getStartNode() const;//returns last Node
    Node* getEndNode() const;//returns first Node
    const QVector<Node*>& getNodes() const;//function to return/access all nodes
    Node* findNode(int x, int y) const; // Added findNode function

private:
    int width;//to give number of nodes in x-axis
    int height;//to give number of nodes in y-axis
    QVector<Node*> nodes;//it is used to store all nodes
    Node* startNode;//tracks starting/first node
    Node* lastNode;//tracks ending/last node
};

#endif // MAZE_H
