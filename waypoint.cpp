#include "waypoint.h"

wayPoint::wayPoint(QObject *parent) : QObject(parent)
{
    this->next = nullptr;
}

wayPoint::wayPoint(QPoint pos):pos(pos)
{
    this->next = nullptr;
}

void wayPoint::setNextPoint(wayPoint* next)
{
    this->next = next;
}

wayPoint* wayPoint::getNextPoint()
{
    return this->next;
}

QPoint wayPoint::getPos()
{
    return this->pos;
}

void wayPoint::draw(QPainter *painter)
{
    painter->save();
    painter->setPen(QPen(Qt::red,5));
    painter->drawEllipse(this->pos,4,4);
    painter->drawEllipse(this->pos,1,1);
    if(this->next!=nullptr)
    {
        painter->drawLine(this->pos,this->next->getPos());
    }
    painter->restore();
}
