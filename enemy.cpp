#include "enemy.h"
#include "mainWidget.h"

//Enemy基类
void Enemy::draw(QPainter *painter) const
{
    painter->save();
}
void Enemy::move()
{
    ;
}
void Enemy::findUnit()
{
    ;
}
QPoint Enemy::getPos()
{
    return this->pos;
}
void Enemy::getAttacked(Unit *unit)
{
    attackerUnitList.push_back(unit);
}
void Enemy::getDamaged(int damage)
{
    currentHealth-=damage;
    if(currentHealth<=0)
    {
        this->game->awardCoin();
        remove();
    }
}
void Enemy::remove()
{
    if(deleted) return;
    this->game->removeEnemy(this);
    this->deleted = true;
}
void Enemy::removeUnit(Unit* unit)
{
    if(unit!=nullptr)
    {
        this->attackerUnitList.removeOne(unit);
    }
}
void Enemy::clearUnit(Unit *unit)
{
    if(unit!=nullptr)
    {
        this->targetList.removeOne(unit);
    }
}
void Enemy::getLostSight(Unit * unit)
{
    if(unit!=nullptr)
    {
        unit->clearEnemy(this);
        unit->resetAttackCd();
        this->attackerUnitList.removeOne(unit);
    }
}
void Enemy::setActive(bool condition)
{
    this->active = condition;
}
int Enemy::getHealth()
{
    return this->health;
}
void Enemy::setBlock(Unit* unit)
{
    this->blockUnit = unit;
}
bool Enemy::getFly()
{
    return this->fly;
}
void Enemy::setFly(bool fly)
{
    this->fly = fly;
}
void Enemy::attack()
{
    if(!active && blockUnit != nullptr)
    {
        if(attackCd > 0)
        {
            attackCd-=30;
            return;
        }
        else resetAttackCd();

        blockUnit->getDemaged(ATK);
    }
}
void Enemy::resetFindCd()
{
    nowFindCd = findCd;
}
void Enemy::resetAttackCd()
{
    attackCd = attackRate;
}

//普通敌人
OrdinaryEnemy::OrdinaryEnemy(wayPoint* startPoint,Widget* game)
{
    this->health = 30;
    this->ATK = 15;
    this->attackRate = 1500;
    this->attackCd = 1500;
    this->blockUnit = nullptr;
    this->currentHealth = health;
    this->speed = 1.2;
    this->active = false;
    this->game = game;
    this->pos = startPoint->getPos();
    this->destination = startPoint->getNextPoint();
    this->fly = false;
    this->deleted = false;
}
OrdinaryEnemy::~OrdinaryEnemy()
{
    foreach (Unit* unit, targetList)
    {
        unit->removeEnemy(this);
    }
    foreach (Unit* unit, attackerUnitList)
    {
        unit->clearEnemy(this);
    }
    this->attackerUnitList.clear();
    this->destination = nullptr;
    this->game = nullptr;
}
void OrdinaryEnemy::draw(QPainter *painter) const
{
    //血槽
    static const int healthBarWidth=80;
    QPoint healthBarPoint=pos+QPoint(-40,-60);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect healthBarBackRect(healthBarPoint,QSize(healthBarWidth,4));
    painter->drawRect(healthBarBackRect);

    //血条
    painter->setBrush(Qt::green);
    QRect healthBarRect(healthBarPoint,QSize((double)currentHealth/health*healthBarWidth,4));
    painter->drawRect(healthBarRect);//画出当前血量血条

    //把敌人画出来
    painter->drawPixmap(pos.x()- Size::step/2,pos.y()- Size::step/2,120,120,QPixmap(":/Enemies/ordinaryenemy.png"));

    //当自己被选中且单位处于被选中状态，画出aim
    for(int i = 0; i < attackerUnitList.size();i++)
    {
        if(attackerUnitList[i]->isSelected())
        {
            int l_x = pos.x() - 60;
            int l_y = pos.y() - 60;
            painter->drawPixmap(l_x,l_y,120,120,QPixmap(":/Units/aim.png"));
        }
    }
}
void OrdinaryEnemy::move()
{
    if(!active)
    {
        return ;
    }
    if(collide(pos,destination->getPos()))//到达了目标航点
    {
        if(destination->getNextPoint() != nullptr)
        {
            pos=destination->getPos();
            destination=destination->getNextPoint();
        }
        else
        {
            game->baseHealthRecuce(1);
            game->removeEnemy(this);
            return ;
        }
    }
    else
    {//采用QVectoer2D中的两点移动方法
        QPoint targetPoint=destination->getPos();
        double movementSpeed=this->speed;
        QVector2D normailzed(targetPoint-pos);
        normailzed.normalize();
        pos=pos+normailzed.toPoint()*movementSpeed;
    }
}
void OrdinaryEnemy::attack()
{
    Enemy::attack();
}
void OrdinaryEnemy::findUnit()
{
    if(blockUnit!= nullptr)
    {
        if(blockUnit->feelDizzy())
        getLostSight(blockUnit);
    }
    setActive();
}
void OrdinaryEnemy::getDamaged(int damage)
{
    Enemy::getDamaged(damage);
}

//火枪手 远程
HackButeer::HackButeer(wayPoint* startPoint, Widget* game)
{
    this->health = 50;
    this->ATK = 15;
    this->attackRate = 2000;
    this->attackCd = 2000;
    this->attackRange = Size::step*1.6;
    this->blockUnit = nullptr;
    this->currentHealth = health;
    this->speed = 0.8;
    this->active = false;
    this->game = game;
    this->pos = startPoint->getPos();
    this->destination = startPoint->getNextPoint();
    this->fly = false;
    this->deleted = false;
    this->findCd = 200;
    this->nowFindCd = 200;
}
HackButeer::~HackButeer()
{
    for(int i = 0; i < targetList.size();i++)
    {
        targetList[i]->removeEnemy(this);
    }
    for(int i = 0;i < attackerUnitList.size();i++)
    {
        attackerUnitList[i]->clearEnemy(this);
    }
    this->destination = nullptr;
    this->game = nullptr;
}
void HackButeer::draw(QPainter * painter)const
{
    //血槽
    static const int healthBarWidth=80;
    QPoint healthBarPoint=pos+QPoint(-40,-60);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect healthBarBackRect(healthBarPoint,QSize(healthBarWidth,4));
    painter->drawRect(healthBarBackRect);

    //血条
    painter->setBrush(Qt::green);
    QRect healthBarRect(healthBarPoint,QSize((double)currentHealth/health*healthBarWidth,4));
    painter->drawRect(healthBarRect);//画出当前血量血条

    //把敌人画出来
    painter->drawPixmap(pos.x()- Size::step/2,pos.y()- Size::step/2,120,120,QPixmap(":/Enemies/hackbuteer.png"));

    for(int i = 0; i < attackerUnitList.size();i++)
    {
        if(attackerUnitList[i]->isSelected())
        {
            int l_x = pos.x() - 60;
            int l_y = pos.y() - 60;
            painter->drawPixmap(l_x,l_y,120,120,QPixmap(":/Units/aim.png"));
            break;
        }
    }

}
void HackButeer::move()//敌人的移动
{
    if(!active)
    {
        return ;
    }
    if(collide(pos,destination->getPos()))//到达了目标航点
    {
        if(destination->getNextPoint() != nullptr)
        {
            pos=destination->getPos();
            destination=destination->getNextPoint();
        }
        else
        {
            game->baseHealthRecuce(1);
            game->removeEnemy(this);
            return ;
        }
    }
    else
    {//采用QVectoer2D中的两点移动方法
        QPoint targetPoint=destination->getPos();
        double movementSpeed=this->speed;
        QVector2D normailzed(targetPoint-pos);
        normailzed.normalize();
        pos=pos+normailzed.toPoint()*movementSpeed;
    }

}
void HackButeer::attack()
{
    if(!targetList.empty())
    {
        if(attackCd > 0)
        {
            attackCd-=30;
            return;
        }
        else resetAttackCd();
        targetList[0]->getDemaged(ATK);
    }
    else if(targetList.empty())
    {
        setActive();
        resetAttackCd();
    }
}
void HackButeer::findUnit()
{
    if(targetList.size() < 1)
    {
        if(nowFindCd >= 0)
        {
            nowFindCd-=30;
            return;
        }
        else resetFindCd();

        for(int i = 0; i < game->getUnitList().size();i++)
        {
            Unit* tmp = game->getUnitList()[i];
            if(collide(tmp->getPos(),pos,attackRange))
            {
                targetList.push_back(tmp);//设置自己打单位
                tmp->getAttacked(this);//设置单位挨打
                setActive(false);//原地不动
                break;
            }
        }
    }
    if(targetList.empty())
    {
        setActive();
    }
}
void HackButeer::getDamaged(int damage)
{
    Enemy::getDamaged(damage);
}

//飞行艇 飞行时远程攻击，落下后不会攻击,落下后的移速大幅降低,同时，飞行时边移动边攻击
FloatPlane::FloatPlane(wayPoint* startPoint, Widget* game)
{
    this->health = 60;
    this->ATK = 10;
    this->attackRate = 1600;
    this->attackCd = 1600;
    this->attackRange = Size::step*1.6;
    this->blockUnit = nullptr;
    this->currentHealth = health;
    this->speed = 1.8;
    this->active = false;
    this->game = game;
    this->pos = startPoint->getPos();
    this->destination = startPoint->getNextPoint();
    this->fly = true;
    this->deleted = false;
}
FloatPlane::~FloatPlane()
{
    for(int i = 0; i < targetList.size();i++)
    {
        targetList[i]->removeEnemy(this);
    }
    for(int i = 0;i < attackerUnitList.size();i++)
    {
        attackerUnitList[i]->clearEnemy(this);
    }
    this->attackerUnitList.clear();
    this->destination = nullptr;
    this->game = nullptr;

}
void FloatPlane::draw(QPainter * painter)const
{
    //血槽
    static const int healthBarWidth=80;
    QPoint healthBarPoint=pos;
    if(fly)
    {
        healthBarPoint+=QPoint(-40,-80);
        painter->drawPixmap(pos.x()- Size::step/2,pos.y()- Size::step/2 - 20,120,120,QPixmap(":/Enemies/floatplane_1.png"));
    }
    else
    {
        healthBarPoint+=QPoint(-40,-60);
        painter->drawPixmap(pos.x()- Size::step/2,pos.y()- Size::step/2,120,120,QPixmap(":/Enemies/floatplane_2.png"));
    }
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect healthBarBackRect(healthBarPoint,QSize(healthBarWidth,4));
    painter->drawRect(healthBarBackRect);

    //血条
    painter->setBrush(Qt::green);
    QRect healthBarRect(healthBarPoint,QSize((double)currentHealth/health*healthBarWidth,4));
    painter->drawRect(healthBarRect);//画出当前血量血条

    for(int i = 0; i < attackerUnitList.size();i++)
    {
        if(attackerUnitList[i]->isSelected())
        {
            int l_x = pos.x() - 60;
            int l_y = pos.y() - 60;
            painter->drawPixmap(l_x,l_y,120,120,QPixmap(":/Units/aim.png"));
            break;
        }
    }

}
void FloatPlane::move()//敌人的移动
{
    if(!active)
    {
        return;
    }
    if(collide(pos,destination->getPos()))
    {
        if(destination->getNextPoint() != nullptr)
        {
            pos=destination->getPos();
            destination=destination->getNextPoint();
        }
        else
        {
            game->baseHealthRecuce(1);
            game->removeEnemy(this);
            return ;
        }
    }
    else
    {//采用QVectoer2D中的两点移动方法
        QPoint targetPoint=destination->getPos();
        double movementSpeed = 0;
        movementSpeed=this->speed;

        QVector2D normailzed(targetPoint-pos);
        normailzed.normalize();
        pos=pos+normailzed.toPoint()*movementSpeed;
    }

}
void FloatPlane::attack()
{

    if(!fly) return;

    else if(!targetList.empty())
    {
        if(attackCd > 0)
        {
            attackCd-=30;
            return;
        }
        else resetAttackCd();

        targetList[0]->getDemaged(ATK);
    }
    else return;
}
void FloatPlane::findUnit()
{

    if(!fly) return;

    if(targetList.size() < 1)
    {
        if(nowFindCd >= 0)
        {
            nowFindCd-=30;
            return;
        }
        else resetFindCd();

        for(int i = 0; i < game->getUnitList().size();i++)
        {
            Unit* tmp = game->getUnitList()[i];
            if(collide(tmp->getPos(),pos,attackRange))
            {
                targetList.push_back(tmp);//设置自己打单位
                tmp->getAttacked(this);//设置单位挨打
                break;
            }
        }
    }
    else if(!targetList.empty() && !collide(this->targetList[0]->getPos(),pos,attackRange))
    {
        targetList[0]->getLostSight(this);
    }
    if(blockUnit!= nullptr)
    {
        if(blockUnit->feelDizzy())
        getLostSight(blockUnit);
    }
    setActive();

}
void FloatPlane::getDamaged(int damage)
{
    currentHealth-=damage;
    if(currentHealth<=0)
    {
        this->game->awardCoin();
        remove();
    }
    else if(fly && currentHealth <= health - 20)
    {
        this->setFly(false);
        speed = 0.6;
        foreach (Unit* unit,targetList) {
            unit->removeEnemy(this);
        }
    }
}

//Boss 盔甲骑士
Knight::Knight(wayPoint* startPoint,Widget* game)
{
    this->health = 400;
    this->ATK = 25;
    this->attackRate = 1800;
    this->attackCd = 1800;
    this->attackRange = Size::step*2;
    this->blockUnit = nullptr;
    this->currentHealth = health;
    this->speed = 1;
    this->active = false;
    this->game = game;
    this->pos = startPoint->getPos();
    this->destination = startPoint->getNextPoint();
    this->fly = false;
    this->deleted = false;
    this->skillCd = 3000;
    this->findCd = 200;
    this->nowFindCd = 200;
}
Knight::~Knight()
{
    foreach (Unit* unit, targetList)
    {
        unit->removeEnemy(this);
    }
    foreach (Unit* unit, attackerUnitList)
    {
        unit->clearEnemy(this);
    }
    this->attackerUnitList.clear();
    this->destination = nullptr;
    this->game = nullptr;
}
void Knight::draw(QPainter *painter) const
{
    //血槽
    static const int healthBarWidth=80;
    QPoint healthBarPoint=pos+QPoint(-40,-60);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect healthBarBackRect(healthBarPoint,QSize(healthBarWidth,4));
    painter->drawRect(healthBarBackRect);

    //血条
    painter->setBrush(Qt::green);
    QRect healthBarRect(healthBarPoint,QSize((double)currentHealth/health*healthBarWidth,4));
    painter->drawRect(healthBarRect);//画出当前血量血条

    //把敌人画出来
    painter->drawPixmap(pos.x()- Size::step/2,pos.y()- Size::step/2,120,120,QPixmap(":/Enemies/knight.png"));

    //当自己被选中且单位处于被选中状态，画出aim
    for(int i = 0; i < attackerUnitList.size();i++)
    {
        if(attackerUnitList[i]->isSelected())
        {
            int l_x = pos.x() - 60;
            int l_y = pos.y() - 60;
            painter->drawPixmap(l_x,l_y,120,120,QPixmap(":/Units/aim.png"));
        }
    }
}
void Knight::move()
{
    if(!active)
    {
        return ;
    }
    if(collide(pos,destination->getPos()))//到达了目标航点
    {
        if(destination->getNextPoint() != nullptr)
        {
            pos=destination->getPos();
            destination=destination->getNextPoint();
        }
        else
        {
            game->baseHealthRecuce(3);
            game->removeEnemy(this);
            return ;
        }
    }
    else
    {//采用QVectoer2D中的两点移动方法
        QPoint targetPoint=destination->getPos();
        double movementSpeed=this->speed;
        QVector2D normailzed(targetPoint-pos);
        normailzed.normalize();
        pos=pos+normailzed.toPoint()*movementSpeed;
    }
}
void Knight::attack()
{
    Enemy::attack();

    if(skillCd > 0)
    {
        skillCd-=30;
        return;
    }
    else skillCd = 4000;

    foreach (Unit* unit, targetList)
    {
        unit->setDizzy();
        clearUnit(unit);
    }
}
void Knight::findUnit()
{
    if(targetList.size() < 2)
    {
        if(nowFindCd >= 0)
        {
            nowFindCd-=30;
            return;
        }
        else resetFindCd();

        for(int i = 0; i < game->getUnitList().size();i++)
        {
            Unit* tmp = game->getUnitList()[i];
            if(collide(tmp->getPos(),pos,attackRange))
            {
                targetList.push_back(tmp);//设置自己打单位
                tmp->getAttacked(this);//设置单位挨打
            }
        }
    }
    if(blockUnit!= nullptr)
    {
        if(blockUnit->feelDizzy())
        getLostSight(blockUnit);
    }
    setActive();

}
void Knight::getDamaged(int damage)
{
    Enemy::getDamaged(damage);
}


