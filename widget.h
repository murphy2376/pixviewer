#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <QPushButton>
#include "common.h"
#include "pixdisplayer.h"
#include "imageframe.h"


#define BTN_HEIGHT 50
#define BTN_WIDTH 200
#define PIXWIDTH 30
#define PIXHEIGHT 42
#define PIX_ROWS 22
#define PIX_COLS 56

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
protected slots:
    void on_clicked();
    void on_posclicked(int x,int y);
protected:
    ImageFrame *frame;
    QFrame *pixframe;
    QPushButton* btn;
    PixDisplayer* pixes[PIX_ROWS][PIX_COLS];
    size_t curwidth,curheight;
    cv::Mat mat;
};

#endif // WIDGET_H

