#include "about.h"
#include "ui_about.h"

about::about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);
    this->connect(ui->startPushButton,SIGNAL(clicked()),this,SLOT(startMovieSlot()));
    this->connect(ui->stopPushButton,SIGNAL(clicked()),this,SLOT(stopMovieSlot()));
    this->movie = new QMovie(":/new/icon/icon/flower.gif");
    ui->movieLabel->setMovie(this->movie);
    movie->start();
}

about::~about()
{
    delete ui;
}

void about::stopMovieSlot()
{
    this->movie->stop();
}
void about::startMovieSlot()
{
    this->movie->start();
}
