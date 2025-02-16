#ifndef MYRECT_H
#define MYRECT_H

#include <QGraphicsRectItem>
#include <QKeyEvent>//this libray is used to act to a specific action like:if user presses left key thsn player moves to left side etc
#include "Node.h"

class MyRect : public QGraphicsRectItem {//we are including QGraphicsRectItem in MyRect class so we can create object using this class
public:
    MyRect( Node* startNode); // Constructor definition
    void keyPressEvent(QKeyEvent* event) override;//this function is used to give mobility to player

private:
    Node* currentNode;//this stores the current position of the player(basically a node through which player is represented)
};

#endif // MYRECT_H
