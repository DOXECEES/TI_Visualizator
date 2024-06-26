#include "cryptvisualizer.h"

CryptVisualizer::CryptVisualizer()
    :scene(new QGraphicsScene(this))
{
    setScene(scene);
}


void CryptVisualizer::draw()
{
    scene->addText(QString("davnslkdnvls"));

}
