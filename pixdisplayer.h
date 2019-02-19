#ifndef PIXDISPLAYER_H
#define PIXDISPLAYER_H

#include <QFrame>
#include <QLabel>
#include <QString>
#include <array>
#include <QResizeEvent>
#include "common.h"


class PixDisplayer : public QFrame
{
    Q_OBJECT
public:
    explicit PixDisplayer(QFrame *parent = nullptr);
    void SetPixText(const cv::Vec3b& colors);
protected:
    virtual void resizeEvent(QResizeEvent* e);

signals:

public slots:

protected:
    std::array <QLabel*,3> labels;
};

#endif // PIXDISPLAYER_H
