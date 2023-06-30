#ifndef ROAD_H
#define ROAD_H

#include <QObject>
#include "waypoint.h"

class Road : public QObject
{
    Q_OBJECT
public:
    explicit Road(int size,QObject *parent = nullptr);
    wayPoint** getRoad();
    void setRoad(int posIndex,wayPoint* point = nullptr);
    int getSize();
private:
    int size;
    wayPoint** wayPointList;
signals:

public slots:
};

#endif // ROAD_H
