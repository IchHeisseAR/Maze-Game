 #include "Maze.h"
#include <QRandomGenerator> //Similar to rand() in c++ defined in cstdlib
#include <QStack>
#include <limits>
#include <cstdlib>
#include <QDebug> //Similar working to std::cout


Maze::Maze(int width, int height) : width(width), height(height) {//it creates a total of 15*15=225 nodes
    for (int y = 0; y < height; ++y) {//starts from zero and goes upto 15-1 --outer loop
        for (int x = 0; x < width; ++x) {//starts from zero and goes upto 15-1  --inner loop
            Node* node = new Node();//it creates a new node
            node->x = x * 30;//it used to set x-axis of a node i.e:node1-x=0,node2-x=30,there x-axis is multiple of 30
            node->y = y * 30;//it used to set y-axis of a node i.e:node1-y=0,node2-y=30,there y-axis is multiple of 30

            // Introduce random obstacle placement
            // node->isObstacle = rand() % 60 == 0; // Adjust probability as needed

            nodes.append(node);//store all nodes that have been created so far
        }
    }

    for (int i = 0; i < nodes.size(); ++i) {//loops from 0 to 1 less tha total number nodes(in this case 225)
        Node* node = nodes[i];//accesses a specific node
        // Check bounds before accessing neighbors
        if (i % width != 0 && i > 0) { // Left neighbor
            node->neighbors.append(nodes[i - 1]);
        }
        if (i % width != width - 1 && i < nodes.size() - 1) { // Right neighbor
            node->neighbors.append(nodes[i + 1]);
        }
        if (i >= width) { // Top neighbor
            node->neighbors.append(nodes[i - width]);
        }
        if (i + width < nodes.size()) { // Bottom neighbor
            node->neighbors.append(nodes[i + width]);
        }
    }

    startNode = nodes[0];
    lastNode = nodes.back();
}

void Maze::addObstacles() {
    int obstacleCount = 30; // Desired number of obstacles
    int placedObstacles = 0;

    // qDebug() << "Total nodes in the maze:" << nodes.size();

    while (placedObstacles < obstacleCount) {
        Node* node = nodes[QRandomGenerator::global()->bounded(nodes.size())];

        // Check if node is eligible for an obstacle
        if (node != startNode && node != lastNode && !node->isObstacle) {
            node->isObstacle = true;
            ++placedObstacles;
            // qDebug() << "Placed obstacle at node:"
            //          << "x=" << node->x
            //          << "y=" << node->y;
        }
    }

    qDebug() << "Total obstacles placed:" << placedObstacles;
}



QVector<Node*> Maze::shortestPath(Node* start, Node* end) { //Another DFS algorithm to find the shortest path between starting and ending node for help and reveal function
    QHash<Node*, int> distances;
    QHash<Node*, Node*> previous;
    QSet<Node*> unvisited;

    for (Node* node : nodes) {
        distances[node] = std::numeric_limits<int>::max();
        unvisited.insert(node);
    }
    distances[start] = 0;

    while (!unvisited.isEmpty()) {
        Node* closest = nullptr;
        for (Node* node : unvisited) {
            if (!closest || distances[node] < distances[closest]) {
                closest = node;
            }
        }

        if (closest == end || distances[closest] == std::numeric_limits<int>::max()) break;

        unvisited.remove(closest);

        for (Node* neighbor : closest->neighbors) {
            if (!neighbor->isObstacle && unvisited.contains(neighbor)) {
                int alt = distances[closest] + 1;
                if (alt < distances[neighbor]) {
                    distances[neighbor] = alt;
                    previous[neighbor] = closest;
                }
            }
        }
    }

    QVector<Node*> path;
    for (Node* at = end; at != nullptr; at = previous.value(at, nullptr)) {
        path.prepend(at);
    }
    return path;
}

Node* Maze::getStartNode() const { return startNode; }
Node* Maze::getEndNode() const { return lastNode; }
const QVector<Node*>& Maze::getNodes() const { return nodes; }

Node* Maze::findNode(int x, int y) const {
    for (Node* node : nodes) {
        if (node->x == x && node->y == y) {
            return node;
        }
    }
    return nullptr;
}
