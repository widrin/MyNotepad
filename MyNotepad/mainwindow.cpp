#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(!this->saveFileName.isEmpty())
    {
        this->setWindowTitle(this->title.append(this->saveFileName));
    }
    else
    {
        this->setWindowTitle("Untitled----MyNotepad");
    }
    this->connect(ui->action_N,SIGNAL(triggered()),this,SLOT(newFileSlot()));
    this->connect(ui->action_O,SIGNAL(triggered()),this,SLOT(openFileSlot()));
    this->connect(ui->action_S,SIGNAL(triggered()),this,SLOT(saveFileSlot()));
    this->connect(ui->action_3,SIGNAL(triggered()),this,SLOT(saveAsFileSlot()));
    this->connect(ui->action_P,SIGNAL(triggered()),this,SLOT(printFileSlot()));
    this->connect(ui->action_7,SIGNAL(triggered()),this,SLOT(close()));
    this->connect(ui->action_Z,SIGNAL(triggered()),ui->textEdit,SLOT(undo()));
    this->connect(ui->action_C,SIGNAL(triggered()),ui->textEdit,SLOT(copy()));
    this->connect(ui->action_V,SIGNAL(triggered()),ui->textEdit,SLOT(paste()));
    this->connect(ui->action_A,SIGNAL(triggered()),ui->textEdit,SLOT(selectAll()));
    this->connect(ui->action_X,SIGNAL(triggered()),ui->textEdit,SLOT(cut()));
    this->connect(ui->action_R,SIGNAL(triggered()),ui->textEdit,SLOT(redo()));
    this->connect(ui->action_5,SIGNAL(triggered()),this,SLOT(setBGColorSlot()));
    this->connect(ui->action_13,SIGNAL(triggered()),this,SLOT(setFontSlot()));
    this->connect(ui->action_2,SIGNAL(triggered()),this,SLOT(setColorSlot()));
    this->connect(ui->action_F5,SIGNAL(triggered()),this,SLOT(setDateTime()));
    this->connect(ui->action,SIGNAL(triggered()),this,SLOT(aboutAuthor()));
    this->connect(ui->action_4,SIGNAL(triggered()),this,SLOT(aboutSoftwareSlot()));
    //this->connect(ui->action_L,SIGNAL(triggered()),ui->textEdit,SLOT(deleteLater()));
}

void MainWindow::closeEvent(QCloseEvent * event)
{
    if(ui->textEdit->document()->isModified())
    {
        QMessageBox msgBox;
        msgBox.setText("文件已被修改");
        msgBox.setInformativeText("您是否要保存？");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();

        switch (ret) {
          case QMessageBox::Save:
              // Save was clicked
            this->saveFileSlot();
              break;
          case QMessageBox::Discard:
              event->accept();
              break;
          case QMessageBox::Cancel:
              event->ignore();
              break;
          default:
              // should never be reached
              break;
        }
    }
    else
    {
        event->accept();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFileSlot()
{
    //如果当前文档的内容已经改变
    if(ui->textEdit->document()->isModified())
    {
        this->saveFileSlot();
    }
    else
    {
        ui->textEdit->clear();
        this->setWindowTitle("Untitled.txt----MyNotepad");
    }
}

void MainWindow::openFileSlot()
{
    QString fileName = QFileDialog::getOpenFileName( this,"Open File",QDir::currentPath());
    if(fileName.isEmpty())
    {
        QMessageBox::information(this,"Error Message","Please choose a file");
        return;
    }
    //打开文件
    QFile *file = new QFile;
    file->setFileName(fileName);
    bool ok = file->open(QIODevice::ReadOnly);
    if(ok)
    {
        //创建流关联文件
        QTextStream in(file);
        ui->textEdit->setText(in.readAll());
        this->saveFileName = fileName;
        file->close();
        delete file;
        this->setWindowTitle(this->title.append(this->saveFileName));
    }
    else
    {
        QMessageBox::information(this,"Error Message","File Open Error");
        return;
    }
}

void MainWindow::saveFileSlot()
{
    if(this->saveFileName.isEmpty())
    {
        this->saveAsFileSlot();
    }
    else
    {
        //获取保存的文件名
        QFile *file = new QFile;
        file->setFileName(saveFileName);
        bool ok = file->open(QIODevice::WriteOnly);
        if(ok)
        {
            QTextStream out(file);
            out << ui->textEdit->toPlainText();    //转换为纯文本
            file->close();
            delete file;
            this->setWindowTitle(this->title.append(this->saveFileName));
        }
        else
        {
            QMessageBox::information(this,"Error Message","File Save Failed");
            return;
        }
    }

}

void MainWindow::saveAsFileSlot()
{
    //获取保存的文件名
    QString fileName = QFileDialog::getSaveFileName(this,"Save File",QDir::currentPath());
    if(fileName.isEmpty())
    {
        QMessageBox::information(this,"Error Message","Please choose a file");
        return;
    }
    QFile *file = new QFile;
    file->setFileName(fileName);
    bool ok = file->open(QIODevice::WriteOnly);
    if(ok)
    {
        QTextStream out(file);
        out << ui->textEdit->toPlainText();    //转换为纯文本
        this->saveFileName = fileName;
        file->close();
        delete file;
        this->setWindowTitle(this->title.append(this->saveFileName));
    }
    else
    {
        QMessageBox::information(this,"Error Message","File Save Failed");
        return;
    }
}

void MainWindow::printFileSlot()
{
    // 创建打印机对象
    QPrinter printer;
    // 创建打印对话框
    QString printerName = printer.printerName();
    if( printerName.size() == 0)
        return;
    QPrintDialog dlg(&printer, this);
    //如果编辑器中有选中区域，则打印选中区域
    if (ui->textEdit->textCursor().hasSelection())
        dlg.addEnabledOption(QAbstractPrintDialog::PrintSelection);
    // 如果在对话框中按下了打印按钮，则执行打印操作
    if (dlg.exec() == QDialog::Accepted)
    {
       ui->textEdit->print(&printer);
       // print the existing document by absoult path
      //  printFile("D:/myRSM.doc");
    }
}
// 打印预览
void MainWindow::printPreviewSlot()
{
    QPrinter printer;
    // 创建打印预览对话框
    QPrintPreviewDialog preview(&printer, this);
    // 当要生成预览页面时，发射paintRequested()信号
    connect(&preview, SIGNAL(paintRequested(QPrinter*)),
                  this,SLOT(printPreview(QPrinter*)));
    preview.exec();
}
void MainWindow::printPreview(QPrinter *printer)
{
    ui->textEdit->print(printer);
}
// 生成PDF文件
void MainWindow::createPdf()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("导出PDF文件"), QString(), "*.pdf");
    if (!fileName.isEmpty()) {
        // 如果文件后缀为空，则默认使用.pdf
        if (QFileInfo(fileName).suffix().isEmpty())
            fileName.append(".pdf");
        QPrinter printer;
        // 指定输出格式为pdf
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
        ui->textEdit->print(&printer);
    }
}
// 页面设置
void MainWindow::setUpPage()
{
    QPrinter printer;
    QPageSetupDialog pageSetUpdlg(&printer, this);
    if (pageSetUpdlg.exec() == QDialog::Accepted)
    {
        printer.setOrientation(QPrinter::Landscape);
    }
    else
    {
        printer.setOrientation(QPrinter::Portrait);
    }
}

void MainWindow::setFontSlot()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok,this);
    if(ok)
    {
        ui->textEdit->setFont(font);
    }
    else
    {
        QMessageBox::information(this,"Error Message","Set Font Failed");
    }
}

void MainWindow::setColorSlot()
{
    QColor color = QColorDialog::getColor(Qt::red,this);
    if(color.isValid())
    {
        ui->textEdit->setTextColor(color);
    }
    else
    {
        QMessageBox::information(this,"Error Message","Set Color Failed");
    }
}

void MainWindow::setDateTime()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    ui->textEdit->insertPlainText(dateTime.toString("yyyy-MM-dd,HH:mm:ss"));
}

void MainWindow::setBGColorSlot()
{
    QColor bgColor = QColorDialog::getColor(Qt::green,this);
    if(bgColor.isValid())
    {
        ui->textEdit->setTextBackgroundColor(bgColor);
    }
    else
    {
        QMessageBox::information(this,"Error Message","BackgroundColor set Failed");
    }
}

void MainWindow::aboutAuthor()
{
    QDesktopServices::openUrl(QUrl("http://home.cnblogs.com/u/HuangWj/"));
}

void MainWindow::aboutSoftwareSlot()
{
    about *dialog = new about();
    dialog->show();    //unmodel dialog
    //dialog->exec();    //model dialog
}
