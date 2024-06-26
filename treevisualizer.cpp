#include "treevisualizer.h"
#include <QWheelEvent>

TreeVisualizer::TreeVisualizer(BinaryTree* tree, QWidget* parent)
    :QGraphicsView()
    ,scene(new QGraphicsScene())
    ,tree(tree)
{
    setRenderHint(QPainter::Antialiasing);
    setScene(scene);
    setDragMode(QGraphicsView::NoDrag);

}

void TreeVisualizer::wheelEvent(QWheelEvent* event)
{
    if (event->angleDelta().y() > 0)
    {
        scale(1.2, 1.2);
    }
    else
    {
        scale(1 / 1.2, 1 / 1.2);
    }
}

void TreeVisualizer::drawTree()
{
    scene->clear();
    if (tree->getRoot() != nullptr)
    {
        widthPerLevel = tree->getWidthPerLevel();
        int treeHeight = tree->getHeight();
        int vStep = height() / (treeHeight + 1);

        int maxWidth = *std::max_element(widthPerLevel.begin(), widthPerLevel.end());

        drawNode(tree->getRoot(), width() / 2, 50, width() / (maxWidth + 1), vStep, 0);
    }
}


void TreeVisualizer::drawNode(BinaryTree::TreeNode* node, int x, int y, int hStep, int vStep, int level)
{
    if (node == nullptr)
    {
        return;
    }

    int nodeRadius = 15;
    QPen pen(Qt::black, 2);
    QBrush brush(Qt::white);
    QFont font("Arial", 12);


    QGraphicsEllipseItem* ellipse = scene->addEllipse(x - nodeRadius, y - nodeRadius, 2 * nodeRadius, 2 * nodeRadius, pen, brush);
    QGraphicsTextItem* text = scene->addText(node->value, font);

    text->setDefaultTextColor(Qt::black);
    text->setPos(x - text->boundingRect().width() / 2, y - nodeRadius - text->boundingRect().height() - 5);

    if (level + 1 < widthPerLevel.size())
    {
        int nextHStep = width() / pow(2, (level + 1));

        if (node->left != nullptr)
        {
            QGraphicsLineItem* line = scene->addLine(x, y + nodeRadius, x - nextHStep, y + vStep - nodeRadius, pen);
            QGraphicsTextItem* leftText = scene->addText("0", font);

            leftText->setDefaultTextColor(Qt::black);
            leftText->setPos((x + (x - nextHStep)) / 2 - leftText->boundingRect().width() / 2, (y + (y + vStep - nodeRadius)) / 2);

            drawNode(node->left, x - nextHStep, y + vStep, nextHStep, vStep, level + 1);
        }

        if (node->right != nullptr)
        {
            QGraphicsLineItem* line = scene->addLine(x, y + nodeRadius, x + nextHStep, y + vStep - nodeRadius, pen);
            QGraphicsTextItem* rightText = scene->addText("1", font);

            rightText->setDefaultTextColor(Qt::black);
            rightText->setPos((x + (x + nextHStep)) / 2 - rightText->boundingRect().width() / 2, (y + (y + vStep - nodeRadius)) / 2);

            drawNode(node->right, x + nextHStep, y + vStep, nextHStep, vStep, level + 1);
        }
    }
}

void TreeVisualizer::resizeEvent(QResizeEvent* event)
{
    QGraphicsView::resizeEvent(event);
    drawTree();
}

void TreeVisualizer::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        isPanning = true;

        lastPanPoint = event->pos();

        setCursor(Qt::ClosedHandCursor);
        setDragMode(QGraphicsView::ScrollHandDrag);
    }
    QGraphicsView::mousePressEvent(event);
}

void TreeVisualizer::mouseMoveEvent(QMouseEvent* event)
{
    if (isPanning)
    {
        QPoint delta = event->pos() - lastPanPoint;

        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
        verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());
        lastPanPoint = event->pos();
    }
    QGraphicsView::mouseMoveEvent(event);
}

void TreeVisualizer::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        isPanning = false;

        setCursor(Qt::ArrowCursor);
        setDragMode(QGraphicsView::NoDrag);
    }
    QGraphicsView::mouseReleaseEvent(event);
}

