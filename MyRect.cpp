#include "MyRect.h"
#include "Game.h"
#include "Maze.h"
#include <QDebug>
#include <QBrush>
#include <qprocess.h>


MyRect::MyRect(Node* startNode) : QGraphicsRectItem() {
    currentNode = startNode;//setting current node to firstNode
    setRect(0, 0, 20, 20);//setting size of currentNode
    setPos(startNode->x + 5, startNode->y + 5);//setting position of currentNode
}

void MyRect::keyPressEvent(QKeyEvent* event) {
    Game* game = dynamic_cast<Game*>(scene()->views().first());
    if (!game) return;

    Maze* maze = game->getMaze();

    int dx = 0, dy = 0;//variables used to change co-ordinates of player

    //if user chooses to restart after he screwed up, he can...
    if (event->key() == Qt::Key_Y) {
        qApp->quit();
        QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
    }

    // Determine direction of movement
    if (event->key() == Qt::Key_Left) {//if player presses left key then assign -30 to dx(which is also width and height of nodes)
        dx = -30;
    } else if (event->key() == Qt::Key_Right) {//if player presses right key then assign +30 to dx
        dx = 30;
    } else if (event->key() == Qt::Key_Up) {//if player presses up key then assign -30 to dy
        dy = -30;
    } else if (event->key() == Qt::Key_Down) {//if player presses down key then assign +30 to dy
        dy = 30;
    } else if (event->key() == Qt::Key_H) {//if player presses "H" key then initiate displayHelp function

        if(Game::points>=20){//check if player has atleast 20 points
            game->displayHelp();
            return;
        }
        else{
            game->notEnough();
        }
    }

    else if(event->key() == Qt::Key_R){//if player presses "R" key then initiate reveal function

        if(Game::points == 100){//check if player has 100 points
            game->reveal();
        }
        else{
            game->notEnough();
        }
    }

    Node* targetNode = maze->findNode(currentNode->x + dx, currentNode->y + dy);//finding target node mode which is found by adding current co-ordinates of player and values of dy and dx

    // Check if target node is valid
    if (targetNode) {
        if (game->canMoveTo(targetNode)) {//to check if targetNode is not an obstacle
            // Move player to new position
            setPos(targetNode->x, targetNode->y);
            currentNode = targetNode;
            Game::currentNode = currentNode;
        } else if (targetNode->isObstacle) {
            // Handle obstacle collision
            Game::points -= 10;
            game->pointsDisplay->setPlainText("Points: " + QString::number(Game::points));

            // Change obstacle color to black
            QGraphicsRectItem* obstacleItem = new QGraphicsRectItem(targetNode->x, targetNode->y, 30, 30);
            obstacleItem->setBrush(QBrush(Qt::black));
            scene()->addItem(obstacleItem);
        }
    }

    //check if player has runout of points
    if(Game::points < 0){
        game->checkLost();
    }

    // Check if the player has reached the end node
    if (targetNode == Game::endNode) {
        game->checkWon();
    }
}
