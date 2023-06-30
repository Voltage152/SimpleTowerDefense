#include "unit.h"
#include "mainWidget.h"

//Unit基类
void Unit::draw(QPainter * painter) const
{
    painter->save();
    painter->setPen(Qt::green);
    painter->drawEllipse(pos,attackRange,attackRange);
}
void Unit::attack()
{
    ;
}
void Unit::findEnemy()
{
    if(dizzyCd > 0)
    {
        dizzyCd-=30;
        return;
    }

    if(!targetList.empty())
    {
        if(!collide(this->targetList[0]->getPos(),pos,attackRange))
        {
            targetList[0]->getLostSight(this);
        }
    }
    if(targetList.size() < blockNum)
    {
        if(nowFindCd > 0)
        {
            nowFindCd-=30;
            return;
        }
        else resetFindCd();

        for(int i = 0; i < game->getEnemyList().size();i++)
        {
            Enemy* tmp = game->getEnemyList()[i];
            if(collide(tmp->getPos(),pos,attackRange))
            {
                targetList.push_back(tmp);//设置自己打敌人
                tmp->getAttacked(this);//设置敌人挨打
                break;
            }
        }
    }
}
void Unit::clearEnemy(Enemy* enemy)
{
    if(enemy!=nullptr)
    {
        this->targetList.removeOne(enemy);
    }
}
void Unit::removeEnemy(Enemy* enemy)
{
    if(enemy!=nullptr)
    this->attackerEnemyList.removeOne(enemy);
}
void Unit::getDemaged(int damage)
{
    currentHealth-=damage;
    if(currentHealth <= 0)
    {
        remove();
    }
}
void Unit::getAttacked(Enemy* enemy)
{
    this->attackerEnemyList.push_back(enemy);
}
void Unit::getLostSight(Enemy* enemy)
{
    enemy->clearUnit(this);
    enemy->resetAttackCd();
    this->attackerEnemyList.removeOne(enemy);

}
void Unit::remove()
{
    if(deleted) return;
    this->game->removeUnit(this);
    this->deleted = true;
}
void Unit::setPosition(Position* position)
{
    this->position = position;
}
int Unit::getCost()
{
    return this->cost;
}
QPoint Unit::getPos()
{
    return this->pos;
}
int Unit::getId()
{
    return 0;
}
void Unit::resetFindCd()
{
    nowFindCd = findCd;
}
void Unit::setSelected(bool condition)
{
    selected = condition;
}
bool Unit::isSelected()
{
    return selected;
}
void Unit::resetAttackCd()
{
    attackCd = attackRate;
}
void Unit::setDizzy(int dizzy)
{
    this->dizzyCd = dizzy;
}
bool Unit::feelDizzy()
{
    return (dizzyCd > 0)?true:false;
}

//战士
bool inList(Enemy* enemy,QList<Enemy*> enemyList)
{
    for(int i = 0;i < enemyList.size();i++)
    {
        if(enemy == enemyList[i])
            return true;
    }
    return false;
}
Warrior::Warrior(QPoint pos,Widget* game)
{
    id = 1;
    this->pos = pos;
    this->ATK = 10;
    this->cost = 100;
    this->type = 0;
    this->health = 50;
    this->currentHealth = health;
    this->attackRange = Size::step/2;
    this->attackRate = 1000;
    this->attackCd = 0;
    this->maxTarget = 3;
    this->lpos = QPoint(pos.x()-Size::step/2,pos.y()-Size::step/2);
    this->game = game;
    this->blockNum = 3;
    this->deleted = false;
    this->findCd = 200;
    this->nowFindCd = 0;
    this->selected = false;
    this->dizzyCd = 0;
}
void Warrior::draw(QPainter * painter) const
{
    painter->save();
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
    painter->restore();

    if(selected)
    {
        painter->setPen(QPen(Qt::green,3));
        painter->drawEllipse(pos,attackRange,attackRange);
        QString content = QString("%1%2%3%4").arg("战士\n放置在地面路径\n对近距离内地面敌人单体造成伤害，可以阻挡少量地面敌人\n生命值:",
                                              QString::number(currentHealth)+"/"+QString::number(health)+"\n攻击力:",
                                              QString::number(ATK)+"\n最大阻拦数:",
                                              QString::number(blockNum)+"\n");
        game->getInfoBrowser()->setText(content);
    }
    painter->drawPixmap(lpos.x(),lpos.y(),120,120,QPixmap(":/Units/melee_1.png"));
    painter->restore();

    if(dizzyCd > 0)
    {
        int l_x = pos.x() - 60;
        int l_y = pos.y() - 60;
        painter->drawPixmap(l_x,l_y,120,120,QPixmap(":/Units/dizzy.png"));
    }

}
void Warrior::attack()
{
    if(dizzyCd > 0) return;

    if(attackCd > 0)
    {
        attackCd-=30;
        return;
    }
    else resetAttackCd();

    if(!targetList.empty())
    {
        targetList[0]->getDamaged(ATK);
    }
}
void Warrior::findEnemy()
{
    if(dizzyCd > 0)
    {
        dizzyCd-=30;
        return;
    }

    if(nowFindCd > 0)
    {
        nowFindCd-=30;
        return;
    }
    else resetFindCd();

    if(targetList.size() < blockNum)
    {
        for(int i = 0; i < game->getEnemyList().size();i++)
        {
            Enemy* tmp = game->getEnemyList()[i];
            if(!tmp->getFly() && collide(tmp->getPos(),pos,attackRange) && !inList(tmp,targetList))
            {
                targetList.push_back(this->game->getEnemyList()[i]);//设置自己打敌人
                tmp->setActive(false);//设置敌人不能运动
                tmp->setBlock(this);//设置敌人被阻塞

                tmp->getAttacked(this);//设置敌人挨打
            }
        }
    }
}
Warrior::~Warrior()
{
    foreach (Enemy* enemy, targetList)
    {
        enemy->setActive();
        enemy->setBlock(nullptr);
        enemy->removeUnit(this);
    }
    foreach(Enemy* enemy, attackerEnemyList)
    {
        enemy->clearUnit(this);
    }
    this->game = nullptr;
    position->setHasUnit(false);
}

//弓箭手
Archer::Archer(QPoint pos,Widget* game)
{
    id = 2;
    this->pos = pos;
    this->ATK = 10;
    this->cost = 100;
    this->type = 0;
    this->health = 20;
    this->currentHealth = health;
    this->attackRange = Size::step*2;
    this->attackRate = 800;
    this->attackCd = 0;
    this->maxTarget = 1;
    this->lpos = QPoint(pos.x()-Size::step/2,pos.y()-Size::step/2);
    this->game = game;
    this->blockNum = 1;
    this->deleted = false;
    this->findCd = 200;
    this->nowFindCd = 0;
    this->selected = false;
    this->dizzyCd = 0;

}
void Archer::draw(QPainter * painter) const
{
    painter->save();
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
    painter->restore();

    if(selected)
    {
        painter->setPen(QPen(Qt::green,3));
        painter->drawEllipse(pos,attackRange,attackRange);
        QString content = QString("%1%2%3%4").arg("弓箭手\n放置在路径两侧\n对较远距离内敌人单体造成伤害\n生命值:",
                                              QString::number(currentHealth)+"/"+QString::number(health)+"\n攻击力:",
                                              QString::number(ATK)+"\n最大攻击数量:",
                                              QString::number(maxTarget)+"\n");
        game->getInfoBrowser()->setText(content);
    }
    painter->drawPixmap(lpos.x(),lpos.y(),120,120,QPixmap(":/Units/range_1.png"));
    painter->restore();

    if(dizzyCd > 0)
    {
        int l_x = pos.x() - 60;
        int l_y = pos.y() - 60;
        painter->drawPixmap(l_x,l_y,120,120,QPixmap(":/Units/dizzy.png"));
    }

}
void Archer::attack()
{
    if(dizzyCd > 0) return;

    if(!targetList.empty())
    {
        if(attackCd > 0)
        {
            attackCd-=30;
            return;
        }
        else resetAttackCd();
        targetList[0]->getDamaged(ATK);
    }
}
void Archer::findEnemy()
{
    Unit::findEnemy();
}
Archer::~Archer()
{
    foreach (Enemy* enemy, targetList)
    {
        enemy->removeUnit(this);
    }
    foreach(Enemy* enemy, attackerEnemyList)
    {
        enemy->clearUnit(this);
    }
    this->game = nullptr;
    position->setHasUnit(false);
}

//矿工
Miner::Miner(QPoint pos,Widget* game)
{
    id = 4;
    this->pos = pos;
    this->ATK = 0;
    this->cost = 100;
    this->type = 0;
    this->health = 50;
    this->currentHealth = health;
    this->attackRange = 0;
    this->attackRate = 0;
    this->maxTarget = 0;
    this->lpos = QPoint(pos.x()-Size::step/2,pos.y()-Size::step/2);
    this->game = game;
    this->blockNum = 0;
    this->deleted = false;
    this->game->resourceGain(10);
    this->selected = false;
    this->dizzyCd = 0;

}
void Miner::draw(QPainter *painter) const
{
    painter->save();
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
    painter->restore();

    if(selected)
    {
        painter->setPen(QPen(Qt::green,3));
        painter->drawEllipse(pos,attackRange,attackRange);
        QString content = QString("%1%2%3").arg("矿工\n放置在路径两侧\n无攻击能力，可以提高资源的产出\n生命值:",
                                              QString::number(currentHealth)+"/"+QString::number(health)+"\n资源增量:",
                                              QString::number(10)+"\n");
        game->getInfoBrowser()->setText(content);

    }
    painter->drawPixmap(lpos.x(),lpos.y(),120,120,QPixmap(":/Units/miner_1.png"));
    if(dizzyCd > 0)
    {
        int l_x = pos.x() - 60;
        int l_y = pos.y() - 60;
        painter->drawPixmap(l_x,l_y,120,120,QPixmap(":/Units/dizzy.png"));
    }
}
void Miner::attack()
{
    return;
}
void Miner::findEnemy()
{
    return;
}
Miner::~Miner()
{
    this->game->resourceGain(-10);
    for(int i = 0;i < attackerEnemyList.size();i++)
    {
        attackerEnemyList[i]->clearUnit(this);
    }
    this->game = nullptr;
    position->setHasUnit(false);
}

//盾牌
Shield::Shield(QPoint pos,Widget* game)
{
    id = 3;
    this->pos = pos;
    this->ATK = 0;
    this->cost = 125;
    this->type = 1;
    this->health = 100;
    this->currentHealth = health;
    this->attackRange = Size::step/2;
    this->attackRate = 0;
    this->maxTarget = 0;
    this->lpos = QPoint(pos.x()-Size::step/2,pos.y()-Size::step/2);
    this->game = game;
    this->blockNum = 6;
    this->deleted = false;
    this->findCd = 200;
    this->nowFindCd = 0;
    this->selected = false;
    this->dizzyCd = 0;

}
void Shield::draw(QPainter *painter) const
{
    painter->save();
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
    painter->restore();


    painter->restore();
    if(selected)
    {
        painter->setPen(QPen(Qt::green,3));
        painter->drawEllipse(pos,attackRange,attackRange);
        QString content = QString("%1%2%3%4").arg("盾牌\n放置在地面路径\n血量高，可以阻挡大量地面敌人\n生命值:",
                                              QString::number(currentHealth)+"/"+QString::number(health)+"\n攻击力:",
                                              QString::number(ATK)+"\n最大阻拦数:",
                                              QString::number(blockNum)+"\n");
        game->getInfoBrowser()->setText(content);

    }
    if(currentHealth >= health*0.7)
    {
        painter->drawPixmap(lpos.x(),lpos.y(),120,120,QPixmap(":/Units/shield_1.png"));
    }
    else if(currentHealth >= health*0.4)
    {
        painter->drawPixmap(lpos.x(),lpos.y(),120,120,QPixmap(":/Units/shield_2.png"));
    }
    else
    {
        painter->drawPixmap(lpos.x(),lpos.y(),120,120,QPixmap(":/Units/shield_3.png"));
    }
    painter->restore();
    if(dizzyCd > 0)
    {
        int l_x = pos.x() - 60;
        int l_y = pos.y() - 60;
        painter->drawPixmap(l_x,l_y,120,120,QPixmap(":/Units/dizzy.png"));
    }
}
void Shield::attack()
{
    return;
}
void Shield::findEnemy()
{
    if(dizzyCd > 0)
    {
        dizzyCd-=30;
        return;
    }

    if(nowFindCd > 0)
    {
        nowFindCd-=30;
        return;
    }
    else resetFindCd();

    if(targetList.size() < blockNum)
    {
        for(int i = 0; i < game->getEnemyList().size();i++)
        {
            Enemy* tmp = game->getEnemyList()[i];
            if(!tmp->getFly() && collide(tmp->getPos(),pos,attackRange) && !inList(tmp,targetList))
            {
                targetList.push_back(tmp);//设置自己打人
                tmp->setActive(false);//设置敌人不动
                tmp->setBlock(this);//设置阻拦敌人
                tmp->getAttacked(this);//设置敌人挨打
            }
        }
    }
}
Shield::~Shield()
{
    foreach (Enemy* enemy, targetList)
    {
        enemy->setActive();
        enemy->setBlock(nullptr);
        enemy->removeUnit(this);
    }
    foreach(Enemy* enemy, attackerEnemyList)
    {
        enemy->clearUnit(this);
    }
    this->game = nullptr;
    position->setHasUnit(false);
}

//飞行战士
FlyWarrior::FlyWarrior(QPoint pos, Widget* game)
{
    id = 5;
    this->pos = pos;
    this->ATK = 10;
    this->cost = 125;
    this->type = 0;
    this->health = 50;
    this->currentHealth = health;
    this->attackRange = Size::step/2;
    this->attackRate = 1000;
    this->attackCd = 0;
    this->maxTarget = 3;
    this->lpos = QPoint(pos.x()-Size::step/2,pos.y()-Size::step/2);
    this->game = game;
    this->blockNum = 3;
    this->deleted = false;
    this->findCd = 200;
    this->nowFindCd = 0;
    this->selected = false;
    this->dizzyCd = 0;
}
FlyWarrior::~FlyWarrior()
{
    foreach (Enemy* enemy, targetList)
    {
        enemy->setActive();
        enemy->setBlock(nullptr);
        enemy->removeUnit(this);
    }
    foreach(Enemy* enemy, attackerEnemyList)
    {
        enemy->clearUnit(this);
    }
    this->game = nullptr;
    position->setHasUnit(false);

}
void FlyWarrior::draw(QPainter * painter)const
{
    painter->save();
    static const int healthBarWidth=80;
    QPoint healthBarPoint = pos;
    if(!targetList.empty() && targetList[0]->getFly())
    {
        healthBarPoint=pos+QPoint(-40,-40);
    }
    else
    {
        healthBarPoint=pos+QPoint(-40,-60);
    }
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect healthBarBackRect(healthBarPoint,QSize(healthBarWidth,4));
    painter->drawRect(healthBarBackRect);

    //血条
    painter->setBrush(Qt::green);
    QRect healthBarRect(healthBarPoint,QSize((double)currentHealth/health*healthBarWidth,4));
    painter->drawRect(healthBarRect);//画出当前血量血条

    painter->restore();
    if(selected)
    {
        painter->setPen(QPen(Qt::green,3));
        painter->drawEllipse(pos,attackRange,attackRange);
        QString content = QString("%1%2%3%4").arg("飞行战士\n放置在地面路径\n对近距离内敌人单体造成伤害，可以阻挡少量地面或飞行敌人\n生命值:",
                                              QString::number(currentHealth)+"/"+QString::number(health)+"\n攻击力:",
                                              QString::number(ATK)+"\n最大阻拦数:",
                                              QString::number(blockNum)+"\n");
        game->getInfoBrowser()->setText(content);

    }

    if(!targetList.empty() && targetList[0]->getFly())
    {
        painter->drawPixmap(lpos.x(),lpos.y() - 20,120,120,QPixmap(":/Units/flywarrior_2.png"));
    }
    else
    {
    painter->drawPixmap(lpos.x(),lpos.y(),120,120,QPixmap(":/Units/flywarrior_1.png"));
    }
    painter->restore();
    if(dizzyCd > 0)
    {
        int l_x = pos.x() - 60;
        int l_y = pos.y() - 60;
        painter->drawPixmap(l_x,l_y,120,120,QPixmap(":/Units/dizzy.png"));
    }

}
void FlyWarrior::attack()
{
    if(dizzyCd > 0) return;
    if(!targetList.empty())
    {
        if(attackCd > 0)
        {
            attackCd-=30;
            return;
        }
        else resetAttackCd();

        targetList[0]->getDamaged(ATK);
    }
    else
    {
        resetAttackCd();
    }
}
void FlyWarrior::findEnemy()
{
    if(dizzyCd > 0)
    {
        dizzyCd-=30;
        return;
    }

    if(nowFindCd > 0)
    {
        nowFindCd-=10;
        return;
    }
    else resetFindCd();

    if(targetList.size() < blockNum)
    {
        for(int i = 0; i < game->getEnemyList().size();i++)
        {
            Enemy* tmp = game->getEnemyList()[i];
            if(collide(tmp->getPos(),pos,attackRange) && !inList(tmp,targetList))
            {
                targetList.push_back(this->game->getEnemyList()[i]);//设置自己打敌人
                tmp->setActive(false);//设置敌人不能运动
                tmp->setBlock(this);//设置敌人被阻塞

                tmp->getAttacked(this);//设置敌人挨打
            }
        }
    }
}

//投石车
Catapult::Catapult(QPoint pos, Widget* game)
{
    id = 6;
    this->pos = pos;
    this->ATK = 30;
    this->cost = 100;
    this->type = 0;
    this->health = 20;
    this->currentHealth = health;
    this->attackRange = Size::step*2.4;
    this->attackRate = 1600;
    this->attackCd = 0;
    this->maxTarget = 3;
    this->lpos = QPoint(pos.x()-Size::step/2,pos.y()-Size::step/2);
    this->game = game;
    this->blockNum = 1;
    this->deleted = false;
    this->findCd = 200;
    this->nowFindCd = 0;
    this->selected = false;
    this->dizzyCd = 0;
}
Catapult::~Catapult()
{
    foreach (Enemy* enemy, targetList)
    {
        enemy->removeUnit(this);
    }
    foreach(Enemy* enemy, attackerEnemyList)
    {
        enemy->clearUnit(this);
    }
    this->game = nullptr;
    position->setHasUnit(false);

}
void Catapult::draw(QPainter * painter)const
{
    painter->save();
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
    painter->restore();

    if(selected)
    {
        painter->setPen(QPen(Qt::green,3));
        painter->drawEllipse(pos,attackRange,attackRange);
        QString content = QString("%1%2%3%4%5").arg("投石车\n放置在路径两侧\n对远距离内敌人造成大量伤害，同时对至多额外两个敌人造成溅射伤害\n生命值:",
                                              QString::number(currentHealth)+"/"+QString::number(health)+"\n攻击力:",
                                              QString::number(ATK)+"\n溅射伤害:",
                                              QString::number(ATK/3)+"\n最大攻击数量:",
                                              QString::number(maxTarget)+"\n");
        game->getInfoBrowser()->setText(content);

    }
    painter->drawPixmap(lpos.x(),lpos.y(),120,120,QPixmap(":/Units/catapult_1.png"));
    painter->restore();

    if(dizzyCd > 0)
    {
        int l_x = pos.x() - 60;
        int l_y = pos.y() - 60;
        painter->drawPixmap(l_x,l_y,120,120,QPixmap(":/Units/catapult_1dizzy.png"));
    }
}
void Catapult::attack()
{
    if(dizzyCd > 0) return;
    bool first = true;
    int num = 2;
    foreach (Enemy* enemy, targetList)
    {
        if(attackCd > 0)
        {
            attackCd-=30;
            return;
        }
        else resetAttackCd();

        if(first)
        {
            enemy->getDamaged(ATK);
            first = false;
        }
        else
        {
            if(num <= 0) return;
            enemy->getDamaged(ATK/3);
            num--;
        }
    }

}
void Catapult::findEnemy()
{
    if(dizzyCd > 0)
    {
        dizzyCd-=30;
        return;
    }

    if(nowFindCd > 0)
    {
        nowFindCd-=10;
        return;
    }
    else resetFindCd();

    if(!targetList.empty())
    {
        if(!collide(this->targetList[0]->getPos(),pos,attackRange))
        {
            targetList[0]->getLostSight(this);
        }
    }

    if(targetList.size() < maxTarget)
    {
        for(int i = 0; i < game->getEnemyList().size();i++)
        {
            Enemy* tmp = game->getEnemyList()[i];
            if(!tmp->getFly() && collide(tmp->getPos(),pos,attackRange) && !inList(tmp,targetList))
            {
                targetList.push_back(tmp);//设置自己打敌人
                tmp->getAttacked(this);//设置敌人挨打
                break;
            }
        }
    }

}

