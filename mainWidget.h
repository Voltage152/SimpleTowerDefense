#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "map.h"
#include "waypoint.h"
#include "position.h"
#include "unit.h"
#include "enemy.h"
#include "collide.h"
#include "road.h"
#include "carrier.h"

#include <QWidget>
#include <vector>
#include <QMouseEvent>
#include <QPen>
#include <QPainter>
#include <QPoint>
#include <QPaintEvent>
#include <QBrush>
#include <fstream>
#include <string>
#include <QDebug>
#include <QFont>
#include <QTimer>
#include <QString>
#include <QToolBar>
#include <QPushButton>
#include <QDebug>
#include <random>
#include <QLabel>
#include <QMessageBox>

using std::string;
using std::endl;

namespace Size
{
const int step = 120;
const int margin = 100;
}

class Unit;
class Enemy;

namespace Ui {
class Widget;
}
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void paintEvent(QPaintEvent*);
    void addWayPoint();
    void loadMap();
    Map* getMap();
    void addPosition();
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void awardCoin();
    void removeEnemy(Enemy * enemy);
    void removeUnit(Unit* unit);
    void baseHealthRecuce(int damage);
    void setChooseCondition(int choose = 0);
    void resourceGain(int gain);
    QList<Enemy *> getEnemyList();
    QList<Unit*> getUnitList();
    QTextBrowser* getInfoBrowser();

private:
    QTimer * timer;
    QTimer * updateTimer;
    QTimer * waveTimer;
    QTimer * gainTimer;

    EnemyCarrier* enemyCarrier;
    UnitCarrier* unitCarrier;
    Carrier* mapCarrier;

    Ui::Widget *ui;

    QTextBrowser* infoBrowser;
    QList<Road*> roads;//debug
    QList<Position*> positionList;
    QList<Unit*> unitList;
    QList<Enemy*> enemyList;
    Map* map;
    Unit* selectedUnit;
    int resource;
    int baseHealth;
    int wave;
    int nowWave;
    bool win;
    bool lose;
    int gainPerSecond;
    int roadNumber;

    int chooseCondition;//0无法操作，1战士，2弓箭手
    QLabel* virtualLabel;
    bool occupied;
public slots:
    void updateGame();
    void loadWave();


};

#endif // MAINWIDGET_H
