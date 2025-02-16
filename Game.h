#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include "Maze.h"
#include "MyRect.h"

class Game : public QGraphicsView {//QGraphicsView  is publicly include in Game class
    Q_OBJECT

public:
    Game();//constructor definition

    Maze* getMaze() const;//a function to return maze class object
    Node* getEndNode();//used to access the last node
    bool canMoveTo(Node* node);//to check if player can move through a particular node since some nodes are obstacles

    static Node* currentNode;//tracks the position of player(basically a node through which player is represented)
    static Node* startNode; // Tracks the starting node
    static Node* endNode;   // Tracks the ending node

    QGraphicsTextItem* pointsDisplay;//to display the remaining points of player
    static int points;//to assign and keep tracks of points

    void displayHelp();//to display the path from current position of player to upto 3 nodes ahead on shortest path
    void reveal();//to display the path from current position of player to the endNode
    void checkWon();//to display player has won if he has reached the endNode
    void checkLost();//to display player has lost if he has run out of points before reaching the endNode
    void notEnough();//to display Not Enough points if player do not have enough points to use either reveal or help function

private:
    QGraphicsScene* scene;//used to create a scene
    Maze* maze;//an object of class maze is declared
    MyRect* player;//player is declared as object of MyRect class
    QGraphicsTextItem* helpDisplay;//to display help string(word)
    QGraphicsTextItem* revealDisplay;//to display reveal string(word)
    QGraphicsTextItem* restartGameDisplay;//to display restartGameDisplay(word)

    void initializeMaze();//used to initialize the maze
};

#endif

