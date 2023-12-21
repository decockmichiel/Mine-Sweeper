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
    Controller();
    ~Controller();

    int rows() const;
    int columns() const;

private:
    struct Pimpl;
    std::unique_ptr<Pimpl> m_p;
};

} // namespace core
