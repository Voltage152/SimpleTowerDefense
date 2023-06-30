#ifndef WAYPOINT_H
#define WAYPOINT_H

#include <QObject>
#include <QPoint>
#include <QPainter>

class wayPoint : public QObject
{
    Q_OBJECT
public:
    explicit wayPoint(QObject *parent = nullptr);
    wayPoint(QPoint pos);
    void setNextPoint(wayPoint* next);
    wayPoint* getNextPoint();
    QPoint getPos();
    void draw(QPainter* painter);
private:
    QPoint pos;
    wayPoint* next;
signals:

public slots:
};

#endif // WAYPOINT_H
