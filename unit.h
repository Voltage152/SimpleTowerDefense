#ifndef UNIT_H
#define UNIT_H

#include <QObject>
#include <QPainter>
#include <QMouseEvent>
#include <QPoint>
#include <QString>
#include <QDebug>
#include <QList>

#include "enemy.h"
#include "ui_widget.h"
#include "position.h"

class Widget;
class Enemy;

class Unit : public QObject
{
    Q_OBJECT
public:
    virtual void draw(QPainter * painter)const;//画出单位
    virtual void attack();
    virtual void findEnemy();

    void clearEnemy(Enemy* enemy);//敌人死亡后将敌人从攻击对象中移除
    void removeEnemy(Enemy* enemy);//敌人死亡后将敌人从被攻击对象中移除
    void getDemaged(int damage);
    void remove();
    void setPosition(Position* position);
    void getAttacked(Enemy* enemy);
    void getLostSight(Enemy* enemy);
    QPoint getPos();
    int getCost();
    void resetFindCd();
    void setSelected(bool condition = true);
    bool isSelected();
    int getId();
    void resetAttackCd();
    void setDizzy(int dizzy = 3000);
    bool feelDizzy();

protected:
    int type;//0为近战，1为远程
    int cost;//消耗的资源
    int attackRange;//攻击范围
    int ATK;//攻击力
    int attackRate;//攻击频率(毫秒)
    int attackCd;
    int health;
    int currentHealth;
    int maxTarget;
    int blockNum;
    int id;
    bool deleted;
    bool selected;
    int dizzyCd;

    int findCd;
    int nowFindCd;

    QPoint pos;//单位的位置
    QPoint lpos;
    Widget* game;
    QTimer* clock;
    Position* position;
    QList<Enemy *> attackerEnemyList;//正在攻击该单位的所有敌人
    QList<Enemy*> targetList;//正在攻击的所有敌人

signals:

public slots:
};

class Warrior : public Unit
{
public:
    Warrior(QPoint pos, Widget* game);
    ~Warrior();
    void draw(QPainter * painter)const;
    void attack();
    void findEnemy();
private:
};

class Archer : public Unit
{
public:
    Archer(QPoint pos, Widget* game);
    ~Archer();
    void draw(QPainter * painter)const;
    void attack();
    void findEnemy();
};

class Miner : public Unit
{
public:
    Miner(QPoint pos,Widget* game);
    ~Miner();
    void draw(QPainter *painter) const;
    void attack();
    void findEnemy();
};

class Shield : public Unit
{
public:
    Shield(QPoint pos,Widget* game);
    ~Shield();
    void draw(QPainter *painter) const;
    void attack();
    void findEnemy();
};

class FlyWarrior :public Unit
{
public:
    FlyWarrior(QPoint pos, Widget* game);
    ~FlyWarrior();
    void draw(QPainter * painter)const;
    void attack();
    void findEnemy();
};

class Catapult : public Unit
{
public:
    Catapult(QPoint pos, Widget* game);
    ~Catapult();
    void draw(QPainter * painter)const;
    void attack();
    void findEnemy();
};

#endif // UNIT_H
