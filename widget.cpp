#include "widget.h"
#include <QDebug>

//#define SQUAR 60
Widget::Widget(QWidget *parent)
    : QWidget(parent),curwidth(this->width()),curheight(this->height())
{
    frame = new ImageFrame(this);
    connect(frame,SIGNAL(PosClick(int,int)),this,SLOT(on_posclicked(int,int)));
    frame->setGeometry(0,BTN_HEIGHT,this->width(),qMax(0,this->height()-BTN_HEIGHT));
    frame->setFrameStyle(QFrame::Box);

    pixframe = new QFrame();
    pixframe->setGeometry(this->x()+100,this->y()+100,PIXWIDTH*PIX_COLS,PIXHEIGHT*PIX_ROWS);

    for(size_t irow=0;irow<PIX_ROWS;irow++){
        for(size_t icol=0;icol<PIX_COLS;icol++){
            pixes[irow][icol] = new PixDisplayer(pixframe);
            pixes[irow][icol]->setGeometry(icol*PIXWIDTH,irow*PIXHEIGHT,PIXWIDTH,PIXHEIGHT);
            cv::Vec3b colors = {0,0,0};
            pixes[irow][icol]->SetPixText(colors);
        }
    }
    pixframe->show();

    btn = new QPushButton(this);
    btn->setGeometry(0,0,BTN_WIDTH,BTN_HEIGHT);
    btn->setText("LoadImage");

    connect(btn,SIGNAL(clicked()),this,SLOT(on_clicked()));
}

Widget::~Widget()
{

}

void Widget::on_clicked()
{
    mat = cv::imread("/home/z/Pictures/1.jpg");
    QPalette pal(this->frame->palette());
    pal.setColor(QPalette::Background, Qt::black);
    this->frame->setAutoFillBackground(true);
    cv::Mat cpy;
    mat.copyTo(cpy);
    cv::cvtColor(cpy,cpy,cv::COLOR_BGR2RGB);

    QImage image(cpy.data,cpy.cols,cpy.rows,cpy.step,QImage::Format_RGB888);
    QPixmap pm = QPixmap::fromImage(image);

    pal.setBrush(QPalette::Window,QBrush(pm));

    this->frame->setPalette(pal);
    this->frame->resize(cpy.cols,cpy.rows);
    this->resize(qMax(cpy.cols,BTN_WIDTH),cpy.rows+BTN_HEIGHT);


    for(size_t irow=0;irow<qMin(PIX_ROWS,mat.rows);irow++){
        for(size_t icol=0;icol  <qMin(PIX_COLS,mat.cols);icol++){
//            cv::Vec3b colors =
            pixes[irow][icol]->SetPixText(mat.at<cv::Vec3b>((int)irow,(int)icol));
        }
    }
    cpy.release();
}

void Widget::on_posclicked(int x, int y)
{
    qDebug()<<x<<","<<y;
    qDebug()<<PIX_ROWS<<","<<(int)mat.rows-y;
    qDebug()<<PIX_COLS<<","<<(int)mat.cols-x;

//    int rtheight,rtwidth;
    int left,right,top,bottom;
    if(x<PIX_COLS/2) left = 0;
    else left = x-PIX_COLS/2;
    if(x>mat.cols-PIX_COLS/2) right = mat.cols;
    else right = x+PIX_COLS/2;
    if(y<PIX_ROWS/2) bottom = 0;
    else bottom = y-PIX_ROWS/2;
    if(y>mat.rows-PIX_ROWS/2) top = mat.rows;
    else top = y+PIX_ROWS/2;

//    rtheight = right - left;
//    rtwidth = top - bottom;
//    qDebug()<<"rt len: "<<rtwidth<<","<<rtheight;

    for(size_t irow=bottom;irow<top;irow++){
        for(size_t icol=left;icol<right;icol++){
            pixes[irow-bottom][icol-left]->SetPixText(mat.at<cv::Vec3b>((int)irow,(int)icol));
        }
    }

    qDebug()<<"in cpy:";
    cv::Mat cpy;
    mat.copyTo(cpy);
    cv::cvtColor(cpy,cpy,cv::COLOR_BGR2RGB);

    qDebug()<<"in rect";
    cv::Rect rect(left,bottom,right-left,top-bottom);
    qDebug()<<"rect: "<<rect.x<<","<<rect.y<<","<<rect.width<<","<<rect.height;
    cv::rectangle(cpy,rect,cv::Scalar(255,0,0));

    QPalette pal(this->frame->palette());
    pal.setColor(QPalette::Background, Qt::black);
    this->frame->setAutoFillBackground(true);
    QImage image(cpy.data,cpy.cols,cpy.rows,cpy.step,QImage::Format_RGB888);
    QPixmap pm = QPixmap::fromImage(image);
    pal.setBrush(QPalette::Window,QBrush(pm));
    this->frame->setPalette(pal);
    cpy.release();
}

