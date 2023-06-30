#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include <QString>
#include <QPainter>
#include <QSize>
#include <QVector2D>
#include <vector>
#include <QPixMap>
#include <QList>
#include <QTimer>
using std::vector;

#include "waypoint.h"
#include "unit.h"
#include "collide.h"
class Widget;
class Unit;

class Enemy : public QObject
{
    Q_OBJECT
public:
    virtual void draw(QPainter * painter)const;
    virtual void move();//敌人的移动
    virtual void attack();
    virtual void findUnit();
    virtual void getDamaged(int damage);//敌人被攻击受到伤害

    void removeUnit(Unit* unit);//单位死亡后需要从敌人的被攻击列表中移除
    void clearUnit(Unit* unit);//单位死亡后需要从敌人的攻击列表中移除
    QPoint getPos();//得到敌人的当前位置

    void getAttacked(Unit * unit);//将攻击敌人的单位添加进list
    void remove();//敌人死亡后需要被移除
    void getLostSight(Unit * unit);//敌人脱离的攻击范围
    void setActive(bool condition = true);//设置敌人是否可以移动
    void setBlock(Unit* unit);//设置阻挡敌方单位的对象
    void setFly(bool fly = true);
    bool getFly();
    int getHealth();
    void resetFindCd();
    void resetAttackCd();

protected:
    int health;//最大血量
    int ATK;
    int attackRange;
    int attackRate;
    int attackCd;
    int currentHealth;//当前血量
    double speed;//移动速度
    bool active;//是否可以移动
    bool fly;//是否为飞行单位
    bool deleted;

    int findCd;
    int nowFindCd;

    wayPoint * destination;//指向下一个航点
    QPoint pos;//当前位置
    QList<Unit *> attackerUnitList;//正在攻击该敌人的所有单位
    QList<Unit*> targetList;
    Widget* game;
    Unit* blockUnit;
    QTimer* clock;

signals:
};

class OrdinaryEnemy : public Enemy
{
public:
    OrdinaryEnemy(wayPoint* startPoint, Widget* game);
    ~OrdinaryEnemy();
    void draw(QPainter * painter)const;
    void move();//敌人的移动
    void attack();
    void findUnit();
    void getDamaged(int damage);
};

class HackButeer : public Enemy
{
public:
    HackButeer(wayPoint* startPoint, Widget* game);
    ~HackButeer();
    void draw(QPainter * painter)const;
    void move();//敌人的移动
    void attack();
    void findUnit();
    void getDamaged(int damage);
};

class FloatPlane : public Enemy
{
public:
    FloatPlane(wayPoint* startPoint, Widget* game);
    ~FloatPlane();
    void draw(QPainter * painter)const;
    void move();//敌人的移动
    void attack();
    void findUnit();
    void getDamaged(int damage);
};

class Knight : public Enemy
{
public:
    Knight(wayPoint* startPoint, Widget* game);
    ~Knight();
    void draw(QPainter * painter)const;
    void move();//敌人的移动
    void attack();
    void findUnit();
    void getDamaged(int damage);
private:
    int skillCd;
};

#endif // ENEMY_H
