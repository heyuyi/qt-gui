#include "inputedit.h"

InputEdit::InputEdit(QWidget *parent) :
    QLineEdit(parent)
{
}

void InputEdit::mouseReleaseEvent(QMouseEvent *e)
{
    emit released();
}
