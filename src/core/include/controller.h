#pragma once
#include <QObject>
#include <QQmlEngine>

namespace core
{

class Controller : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(int rows READ rows CONSTANT)
    Q_PROPERTY(int columns READ columns CONSTANT)

public:
    int rows() const;
    int columns() const;
};

} // namespace core
