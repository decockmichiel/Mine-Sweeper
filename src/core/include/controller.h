#pragma once
#include <memory>

#include <QAbstractListModel>
#include <QObject>
#include <QQmlEngine>

namespace core
{

struct Position
{
    Position(int row, int column);

    int row = 0;
    int column = 0;
};

bool operator==(const Position& left, const Position& right);

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

    std::vector<Position> bombs() const;

    int getRow(int tileNumber) const;
    int getColumn(int tileNumber) const;

    int getTileNumber(int row, int column) const;

public slots:
    void onTileClicked(int tileNumber);

private:
    struct Pimpl;
    std::unique_ptr<Pimpl> m_p;
};

} // namespace core
