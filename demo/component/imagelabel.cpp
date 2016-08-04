#include "imagelabel.h"

ImageLabel::ImageLabel(QWidget *parent) :
    QLabel(parent)
{
}

void ImageLabel::mousePressEvent(QMouseEvent *e)
{
    emit pressed();
}

void ImageLabel::mouseReleaseEvent(QMouseEvent *e)
{
    emit released();
}
