#include "imagelabel.h"

ImageLabel::ImageLabel(QWidget *parent) :
    QLabel(parent)
{
}

void ImageLabel::mouseReleaseEvent(QMouseEvent *e)
{
    emit released();
}
