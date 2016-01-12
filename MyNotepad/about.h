#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QMovie>

namespace Ui {
class about;
}

class about : public QDialog
{
    Q_OBJECT

public:
    explicit about(QWidget *parent = 0);
    ~about();

private:
    Ui::about *ui;
    QMovie *movie;
private slots:
    void stopMovieSlot();
    void startMovieSlot();
};

#endif // ABOUT_H
