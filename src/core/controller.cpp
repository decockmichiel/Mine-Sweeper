#include <random>

#include "include/controller.h"

namespace
{

struct Position
{
    Position(size_t x, size_t y)
        : x(x)
        , y(y)
    {
    }

    size_t x = 0;
    size_t y = 0;
};
} // namespace

namespace core
{

struct Controller::Pimpl
{
    Pimpl(Controller* parent);

    void disperseBombs(size_t numberOfBombs);

    Controller*           m_controller = nullptr;
    std::vector<Position> m_bombs;
};

Controller::Controller()
    : m_p(std::make_unique<Pimpl>(this))
{
    m_p->disperseBombs(10);
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

Controller::Pimpl::Pimpl(Controller* parent)
    : m_controller(parent)
{
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
}
