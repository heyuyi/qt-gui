#include "systembase.h"

SystemBase::SystemBase()
{
}

const QString SystemBase::path = QDir::currentPath() + QString("/../param/");

const QString SystemBase::postfix = "param";

const QString SystemBase::serialPort1 = "/dev/ttySAC1";
