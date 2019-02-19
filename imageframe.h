#ifndef IMAGEFRAME_H
#define IMAGEFRAME_H

#include <QFrame>
#include <QMouseEvent>
#include <QDebug>

class ImageFrame : public QFrame
{
    Q_OBJECT
public:
    explicit ImageFrame(QWidget *parent = nullptr);
protected:
    virtual void mouseReleaseEvent(QMouseEvent* e);

signals:
    void PosClick(int x, int y);

public slots:
};

#endif // IMAGEFRAME_H
