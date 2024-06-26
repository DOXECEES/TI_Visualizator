#ifndef CRYPTVISUALIZER_H
#define CRYPTVISUALIZER_H

#include <QGraphicsView>
#include <QGraphicsScene>

class CryptVisualizer : public QGraphicsView
{
    Q_OBJECT

public:

    CryptVisualizer();

    void draw();

private:

    QGraphicsScene *scene = nullptr;

};

#endif // CRYPTVISUALIZER_H
