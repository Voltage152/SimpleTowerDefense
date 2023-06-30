#include "road.h"

Road::Road(int size,QObject *parent) : QObject(parent)
{
    this->size= size;
    wayPointList = new wayPoint*[size];
    for(int i = 0;i < size;i++) wayPointList[i] = nullptr;
}

wayPoint** Road::getRoad()
{
    return this->wayPointList;
}
void Road::setRoad(int posIndex,wayPoint* point)
{
    wayPointList[posIndex] = point;
}
int Road::getSize()
{
    return this->size;
}
