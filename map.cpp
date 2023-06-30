#include "map.h"

Map::Map(QObject *parent) : QObject(parent)
{

}
Map::Map(int rowsize,int colsize)
{
    this->rowSize = rowsize;
    this->colSize = colsize;
    this->map = new int*[rowSize];
    for(int i = 0;i<rowSize;i++)
    {
        map[i] = new int[colSize];
    }
    for(int i = 0; i < rowSize;i++)
    {
        for(int j = 0; j < colSize;j++)
        {
            map[i][j] = 0;
        }
    }
}
Map::~Map()
{
    delete[] this->map;
}

int** Map::getMap() const
{
    return this->map;
}
int Map::getRow()
{
    return this->rowSize;
}

int Map::getCol()
{
    return this->colSize;
}

void Map::setMap(int** local)
{
    for(int i = 0; i < rowSize;i++)
    {
        for(int j = 0; j < colSize;j++)
        {
            map[i][j] = local[i][j];
        }
    }
}
