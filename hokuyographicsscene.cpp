#include "hokuyographicsscene.h"

HokuyoGraphicsScene::HokuyoGraphicsScene()
{
    for(int i = 0; i < 1080; i++) {
        this->ellipses.append(this->addEllipse(1, 1, 1, 1));
    }
}

void HokuyoGraphicsScene::setScanRanges(int value)
{

}
