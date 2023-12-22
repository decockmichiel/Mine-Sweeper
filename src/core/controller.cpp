#include <random>

#include "include/controller.h"
#include "include/tile_model.h"

namespace
{

struct Position
{
    Position(size_t row, size_t column)
        : row(row)
        , column(column)
    {
    }

    size_t row = 0;
    size_t column = 0;
};

bool operator==(const Position& left, const Position& right)
{
    return left.row == right.row && left.column == right.column;
}

} // namespace

namespace core
{

struct Controller::Pimpl
{
    Pimpl(Controller* parent);

    void disperseBombs(size_t numberOfBombs);

    bool isBomb(const Position& pos);

    Controller*           m_controller = nullptr;
    std::vector<Position> m_bombs;
    std::unique_ptr<TileModel> m_tileModel;
};

Controller::Controller()
    : m_p(std::make_unique<Pimpl>(this))
{
}

Controller::~Controller() = default;

int Controller::rows() const
{
    return 20;
}

int Controller::columns() const
{
    return 20;
}

int Controller::getRow(int cellNumber) const
{
    return std::floor(cellNumber / columns());
}

int Controller::getColumn(int cellNumber) const
{
    return cellNumber % columns();
}

QAbstractListModel* Controller::tileModel() const
{
    return m_p->m_tileModel.get();
}

void Controller::onCellClicked(int cellNumber)
{
    TileModel& tileModel = *m_p->m_tileModel;

    const Position    pos(getRow(cellNumber), getColumn(cellNumber));
    const QModelIndex index(m_p->m_tileModel->index(cellNumber, 0));

    if (m_p->isBomb(pos))
        tileModel.setState(index, State::State::failure);
    else
        tileModel.setState(index, State::State::success);
}

Controller::Pimpl::Pimpl(Controller* parent)
    : m_controller(parent)
    , m_tileModel(std::make_unique<TileModel>(parent))
{
    disperseBombs(10);
}

void Controller::Pimpl::disperseBombs(size_t numberOfBombs)
{
    std::random_device              device;
    std::mt19937                    engine(device());
    std::uniform_int_distribution<> distRows(0, m_controller->rows() - 1);
    std::uniform_int_distribution<> distColumns(0, m_controller->columns() - 1);

    for (size_t bomb = 0; bomb != numberOfBombs; ++bomb)
        m_bombs.push_back(Position(distRows(device), distColumns(device)));
}

bool Controller::Pimpl::isBomb(const Position& pos)
{
    return std::find(m_bombs.cbegin(), m_bombs.cend(), pos) != m_bombs.cend();
}
}
