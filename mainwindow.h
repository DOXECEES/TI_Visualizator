#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRegularExpression>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QWheelEvent>

#include <QGraphicsScene>


#include "lzfactory.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    enum class Options : uint8_t
    {
        NO              = 0b00000000,
        NO_REGISTER     = 0b00000001,
        CHANGE_SPACE    = 0b00000010
    };



    inline void addFlag(Options opt) { option = option | opt; };
    inline void deleteFlag(Options opt) { option = static_cast<Options>(static_cast<uint8_t>(option)
                                        & (~static_cast<uint8_t>(opt))); };

    friend MainWindow::Options operator|(MainWindow::Options a, MainWindow::Options b);
    friend bool operator &(MainWindow::Options a, MainWindow::Options b);


private:

    const double mouseDelta = 0.01;
    double scaleFactor = 1.0;

    void preprocessString(QString& str, MainWindow::Options params, bool isCoding);


    Options option = Options::NO;
    LZFactory::LZAlgorithm currentAlgorithm = LZFactory::LZAlgorithm::LZ77;
    QChar replaceSymbol = '_';
    QString sourceFile = "";
    QString destinationFile = "";

    QGraphicsScene *scene = nullptr;

    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
