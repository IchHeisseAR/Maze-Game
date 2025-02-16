#include "Game.h"
#include "Maze.h"
#include "MyRect.h"
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>//this library is used to display words
#include <QBrush>//this library is used to give colors to items
#include <QFont>//this library is used to assign font style
#include <QPen>
#include <QDebug>//this library is just used for cout in functions to check if function is properly being called
#include <QTimer>//this library is used for differen function like delay etc

//few things to keep in mind:
//QGraphicsView is used to create a view which is like our environment without an boundary
//QGraphicsScene is used to create a scene which like a romm in a view which can either have boundary or not
//QGraphicsRectIten is used to create objects which are actually displayed in scene like tables and other things in a room


// Define static members
Node* Game::currentNode = nullptr;
Node* Game::startNode = nullptr;
Node* Game::endNode = nullptr;
int Game::points = 100;


Game::Game() {
    points = 100; // Initial points

    scene = new QGraphicsScene(this);//initializing scene object
    setScene(scene);//here we are directly using setScene function of QGraphicsView to create a scene since QGraphicsView class is already included in Game class
    setFixedSize(800, 600);//setting size of scene
    scene->setBackgroundBrush(QBrush(Qt::darkCyan));//setting background color of scene

    maze = new Maze(15, 15); // 15x15 maze grid
    initializeMaze();//initialize function of Game class is called

    pointsDisplay = new QGraphicsTextItem("Points: " + QString::number(points));//to display a string
    pointsDisplay->setPos(10, -50);//setting co-ordinates
    pointsDisplay->setCursor(Qt::PointingHandCursor);//setting cursor
    pointsDisplay->setAcceptHoverEvents(true);
    scene->addItem(pointsDisplay);//adding to scene

    helpDisplay = new QGraphicsTextItem("Help: Press 'H'");
    helpDisplay->setPos(width() - 150, -50);
    helpDisplay->setCursor(Qt::PointingHandCursor);
    helpDisplay->setAcceptHoverEvents(true);
    scene->addItem(helpDisplay);

    restartGameDisplay = new QGraphicsTextItem("Restart Game: 'Y'");
    restartGameDisplay->setPos(200, -50);
    restartGameDisplay->setCursor(Qt::PointingHandCursor);
    restartGameDisplay->setAcceptHoverEvents(true);
    scene->addItem(restartGameDisplay);

    revealDisplay=new QGraphicsTextItem("Reveal path: Press 'R'");
    revealDisplay->setPos(350,-50);
    revealDisplay->setCursor(Qt::PointingHandCursor);
    revealDisplay->setAcceptHoverEvents(true);
    scene->addItem(revealDisplay);

    QGraphicsTextItem *ini=new QGraphicsTextItem("Initializing game....");//to display string
    ini->setPos(width() / 2 - 320, height() / 2 - 120);
    ini->setFont(QFont("Arial", 50));//setting font style
    ini->setDefaultTextColor(Qt::black);//setting font color
    scene->addItem(ini);
    //Lambda function in which () describes the inputs, and [] defines the stuff the function can access from the outside environment
    QTimer::singleShot(3000,this,[this,ini](){//this is a lambda fuction which is used to display an item for a specific amount of time
        scene->removeItem(ini);//remove th item after the desired amount of time
        delete ini;
    });
}

void Game::initializeMaze() {
    qDebug() << "Initializing maze...";

    QVector<Node*> nodes = maze->getNodes();
    maze->addObstacles();

    for (Node* node : nodes) {
        QGraphicsRectItem* rect = new QGraphicsRectItem(node->x, node->y, 30, 30);
        rect->setBrush(QBrush(QColor(205, 133, 63))); // set color to each block

        rect->setPen(QPen(Qt::black));//border
        scene->addItem(rect);
    }

    // Create player
    player = new MyRect(maze->getStartNode());//set player to first node
    player->setBrush(QBrush(Qt::red));//set color to red
    scene->addItem(player);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();//keyEvents are only appliable on these items which are set as focusable which is mostly only one

    // Save references to start and end nodes
    currentNode = maze->getStartNode();
    startNode = maze->getStartNode();
    endNode = maze->getEndNode();

    // Highlight start and end nodes
    QGraphicsEllipseItem* startMarker = new QGraphicsEllipseItem(startNode->x + 5, startNode->y + 5, 20, 20);
    startMarker->setBrush(QBrush(Qt::green));
    scene->addItem(startMarker);

    QGraphicsEllipseItem* endMarker = new QGraphicsEllipseItem(endNode->x + 5, endNode->y + 5, 20, 20);
    endMarker->setBrush(QBrush(Qt::blue));
    scene->addItem(endMarker);
}

void Game::displayHelp() {
    qDebug() << "Help function is called";

    // Reduce points by 20 whenever help function is called
    points -= 20;
    pointsDisplay->setPlainText("Points: " + QString::number(points));//display points

    // Calculate path from the current position to the end node
    QVector<Node*> path = maze->shortestPath(currentNode, endNode);

    // Visualize the path with a distinct color upto 4 nodes
    for (int i = 0; i < 4; ++i) {
        Node* current = path[i];
        Node* next = path[i + 1];

        QLineF line(current->x + 15, current->y + 15, next->x + 15, next->y + 15);
        QPen pen(Qt::blue);
        pen.setWidth(3);
        scene->addLine(line, pen);
    }


}



void Game::reveal(){
    qDebug() << "Reveal function is called";

    // Reduce points to 0
    points = 0;
    pointsDisplay->setPlainText("Points: " + QString::number(points));

    // Calculate path from the current position to the end node
    QVector<Node*> path = maze->shortestPath(currentNode, endNode);

    // Visualize the path with a distinct color
    for (int i = 0; i < path.size() - 1; ++i) {
        Node* current = path[i];
        Node* next = path[i + 1];

        QLineF line(current->x + 15, current->y + 15, next->x + 15, next->y + 15);
        QPen pen(Qt::blue);
        pen.setWidth(3);
        scene->addLine(line, pen);
    }

}

void Game::checkWon() {//displays win message
    QGraphicsTextItem* winMessage = new QGraphicsTextItem("You Won!");
    qDebug() << "You have won";
    winMessage->setPos(width() / 2 - 320, height() / 2 - 120);
    winMessage->setFont(QFont("Arial", 50));
    winMessage->setDefaultTextColor(Qt::black);
    scene->addItem(winMessage);

    // Disable player movement
    player->setEnabled(false);
}

void Game::checkLost(){//displays lose msg
    QGraphicsTextItem* lostMessage = new QGraphicsTextItem("You Lost!");
    qDebug() << "You have Lost";
    lostMessage->setPos(width() / 2 - 320, height() / 2 - 120);
    lostMessage->setFont(QFont("Arial", 50));
    lostMessage->setDefaultTextColor(Qt::black);
    scene->addItem(lostMessage);

    // Disable player movement
    player->setEnabled(false);
}

void Game::notEnough(){//display not enough points message
    QGraphicsTextItem *less=new QGraphicsTextItem("Not Enough points");
    less->setPos(width() / 2 - 320, height() / 2 - 120);
    less->setFont(QFont("Arial", 20));
    less->setDefaultTextColor(Qt::black);
    scene->addItem(less);
    QTimer::singleShot(2000,this,[this,less](){
        scene->removeItem(less);
        delete less;
    });
}

bool Game::canMoveTo(Node* node) {
    return node && !node->isObstacle;
}

Maze* Game::getMaze() const {
    return maze;
}

Node* Game::getEndNode() {
    return endNode;
}
