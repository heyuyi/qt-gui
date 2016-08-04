#include "systembase.h"

SystemBase::SystemBase()
{
}

const QString SystemBase::path = QDir::currentPath() + QString("/../param/");

const QString SystemBase::postfix = "param";

const QString SystemBase::serialPort3 = "/dev/ttySAC1";
