#include "imageframe.h"

ImageFrame::ImageFrame(QWidget *parent) : QFrame(parent){

}

void ImageFrame::mouseReleaseEvent(QMouseEvent *e)
{
//    qDebug()<<e->x()<<","<<e->y();
    emit PosClick(e->x(),e->y());
}

