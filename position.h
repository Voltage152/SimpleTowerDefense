#ifndef POSITION_H
#define POSITION_H

#include <QObject>
#include <QPoint>

class Position : public QObject
{
    Q_OBJECT
public:
    explicit Position(QObject *parent = nullptr);
    Position(QPoint pos,int type);
    QPoint getCenterPos();//格子的位置
    int getType();
    bool hasUnit();
    bool containPos(QPoint pos);
    void setHasUnit(bool hasUnit = true);

protected:
    int type;//0是近战,1是远程
    QPoint pos;
    bool m_hasUnit;
signals:

public slots:
};

class SpawnPoint : public Position
{

};

class Base : public Position
{

};

#endif // POSITION_H
