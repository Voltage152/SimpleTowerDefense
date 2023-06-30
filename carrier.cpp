#include "carrier.h"
#include "mainWidget.h"

Carrier::Carrier(Widget* game,QWidget *parent) : QLabel(parent)
{
    this->game = game;
}

void Carrier::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QBrush brush = painter.brush();//保存默认填充色
    painter.setPen(QPen(Qt::black,5));

    for(int i = 0;i<game->getMap()->getRow();i++)
    {
        for(int j = 0; j < game->getMap()->getCol();j++)
        {
            if(game->getMap()->getMap()[i][j] == 1)//敌人出生点
            {
                painter.setBrush(Qt::red);
            }
            else if(game->getMap()->getMap()[i][j] == 2)//己方基地
            {
                painter.setBrush(Qt::blue);
            }
            else if(game->getMap()->getMap()[i][j] == 3)//路径
            {
                painter.setBrush(QColor(202,195,195,100));
            }
            else if(game->getMap()->getMap()[i][j] == 4)//远程单位可部署位置
            {
                painter.setBrush(QColor(209,235,140,100));
            }
            painter.drawRect(Size::margin+j*Size::step,Size::margin+i*Size::step,Size::step,Size::step);
            painter.setBrush(brush);
        }
    }

}

EnemyCarrier::EnemyCarrier(Widget* game,QWidget *parent) : QLabel(parent)
{
    this->game = game;
}

void EnemyCarrier::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    for(int i = 0; i < game->getEnemyList().size();i++)
    {
        this->game->getEnemyList()[i]->draw(&painter);
    }
}

void EnemyCarrier::refresh()
{
    update();
}

UnitCarrier::UnitCarrier(Widget* game,QWidget *parent) : QLabel(parent)
{
    this->game = game;
}

void UnitCarrier::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    for(int i = 0; i < game->getUnitList().size();i++)
    {
        this->game->getUnitList()[i]->draw(&painter);
    }
}

void UnitCarrier::refresh()
{
    foreach(Enemy * enemy,game->getEnemyList())
    {
        enemy->move();
    }
    update();
}

