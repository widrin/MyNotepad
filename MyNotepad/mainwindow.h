#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "about.h"

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QString>
#include <QTextStream>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QtPrintSupport/QPageSetupDialog>
#include <QFont>
#include <QFontDialog>
#include <QColor>
#include <QColorDialog>
#include <QDateTime>
#include <QDesktopServices>    //用于访问桌面服务
#include <QUrl>
#include <QPixmap>
#include <QSplashScreen>
#include <QtMultimedia/QSound>
#include <QMediaPlayer>
#include <QCloseEvent>    //当程序需要关闭时，所处理的内容；所有的事件都是protected



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString saveFileName;
    QString title = "----MyNotepad";
private:
    void printPreview(QPrinter *printer);
    void createPdf();
    void setUpPage();
    void closeEvent(QCloseEvent *);
private slots:
    void newFileSlot();    //新建文本
    void openFileSlot();    //打开文件
    void saveFileSlot();    //保存文本
    void saveAsFileSlot();    //另存为文本
    void printFileSlot();    //打印文本
    void printPreviewSlot();    //打印预览
    void setFontSlot();    //设置字体
    void setColorSlot();    //设置颜色
    void setDateTime();    //添加当前时间
    void setBGColorSlot();    //设置背景颜色
    void aboutAuthor();    //关于作者
    void aboutSoftwareSlot();    //关于软件

};

#endif // MAINWINDOW_H
