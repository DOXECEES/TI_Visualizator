#ifndef TREEVISUALIZER_H
#define TREEVISUALIZER_H

#include <QPoint>
#include <QVector>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QScrollBar>

#include "binarytree.h"

class TreeVisualizer : public QGraphicsView
{
    Q_OBJECT
public:

    TreeVisualizer(BinaryTree* tree, QWidget* parent = nullptr);

    void drawTree();


    void wheelEvent(QWheelEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;


    inline QGraphicsScene * getScene() const { return scene;};


private:
    void drawNode(BinaryTree::TreeNode* node, int x, int y, int hStep, int vStep, int level);

    BinaryTree *tree = nullptr;

    QGraphicsScene *scene = nullptr;

    std::vector<int> widthPerLevel;
    std::vector<int> currentPos;

    bool isPanning;
    QPoint lastPanPoint;

};

#endif // TREEVISUALIZER_H
