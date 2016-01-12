#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap startPixmap(":/new/icon/icon/flower.gif");
    startPixmap.size();
    QSplashScreen splash(startPixmap);
    splash.show();
    for(long i=0; i<100000000;i++);
    MainWindow w;
    w.show();
    splash.finish(&w);
    QMediaPlayer *player = new QMediaPlayer;
    player->setMedia(QUrl::fromUserInput("qrc:/new/sound/1.wav"));
    player->setVolume(50);
    player->play();
    return a.exec();
}
