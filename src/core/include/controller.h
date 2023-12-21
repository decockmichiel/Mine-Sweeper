#pragma once
#include <QObject>
#include <QQmlEngine>

namespace core
{

class Controller : public QObject
{
    Q_OBJECT
    QML_ELEMENT
};

} // namespace core
