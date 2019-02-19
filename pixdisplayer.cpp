#include "pixdisplayer.h"

PixDisplayer::PixDisplayer(QFrame *parent) : QFrame(parent)
{
    for(size_t i=0;i<3;i++){
        labels[i] = new QLabel(this);
        labels[i]->setGeometry(0,this->height()/3*i,this->width(),this->height()/3);
        labels[i]->setAlignment(Qt::AlignCenter);
    }
    this->setFrameStyle(1);
}

void PixDisplayer::SetPixText(const cv::Vec3b &colors)
{
    uint8_t average = (colors[0] + colors[1] + colors[2])/3;
    bool mark = false;
    if(average>125){
        mark = true;
    }
    for(size_t i=0;i<3;i++){
        labels[i]->setText(QString::number(colors[i]));
        if(mark){
            labels[i]->setBackgroundRole(QPalette::Light);
        }else{
            labels[i]->setBackgroundRole(QPalette::Dark);
        }
    }
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(colors[2],colors[1],colors[0]));
    this->setPalette(palette);
}

void PixDisplayer::resizeEvent(QResizeEvent *e)
{
    for(size_t i=0;i<3;i++){
        labels[i]->setGeometry(0,this->height()/3*i,this->width(),this->height()/3);
    }
    QFrame::resizeEvent(e);
}
