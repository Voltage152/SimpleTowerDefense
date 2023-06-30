#include "position.h"

Position::Position(QObject *parent) : QObject(parent)
{

}

Position::Position(QPoint pos,int type):pos(pos),m_hasUnit(false),type(type)
{
}

QPoint Position::getCenterPos()
{
    return this->pos;
}

bool Position::hasUnit()
{
    return m_hasUnit;
}
int Position::getType()
{
    return this->type;
}

bool Position::containPos(QPoint pos)
{
    bool x_in= pos.x() < this->pos.x() + 60 && pos.x() > this->pos.x() - 60;
    bool y_in= pos.y() < this->pos.y() + 60 && pos.y() > this->pos.y() - 60;
    return x_in && y_in;
}

void Position::setHasUnit(bool hasUnit)
{
    m_hasUnit = hasUnit;
}
