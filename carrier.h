#ifndef CARRIER_H
#define CARRIER_H

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QPaintEvent>

class Widget;

class Carrier : public QLabel
{
    Q_OBJECT
public:
    explicit Carrier(Widget* game,QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
private:
    Widget* game;
signals:
public slots:
};

class EnemyCarrier : public QLabel
{
    Q_OBJECT
public:
    explicit EnemyCarrier(Widget* game,QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    void refresh();
private:
    Widget* game;
signals:
public slots:
};

class UnitCarrier : public QLabel
{
    Q_OBJECT
public:
    explicit UnitCarrier(Widget* game,QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    void refresh();
private:
    Widget* game;
signals:
public slots:
};



#endif // CARRIER_H
