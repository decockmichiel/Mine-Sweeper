#pragma once
#include <memory>

#include <QAbstractListModel>
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
    Q_PROPERTY(QAbstractListModel* tileModel READ tileModel CONSTANT)

public:
    Controller();
    ~Controller();

    int rows() const;
    int columns() const;

    QAbstractListModel* tileModel() const;

    int getRow(int cellNumber) const;
    int getColumn(int cellNumber) const;

public slots:
    void onCellClicked(int cellNumber);

private:
    struct Pimpl;
    std::unique_ptr<Pimpl> m_p;
};

} // namespace core
