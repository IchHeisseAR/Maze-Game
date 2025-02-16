#include <QApplication>
#include "Game.h"

int main(int argc, char *argv[]) {
    srand(time(NULL));
    QApplication a(argc, argv);

    Game* game = new Game();//initializing an object of class Game
    game->show();//show() is a functiion of QGraphicsView which is used to display everything on GUI and is called through usin an object of Game class

    return a.exec();
}
