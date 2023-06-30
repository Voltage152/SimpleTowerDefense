#include "mainWidget.h"
#include "ui_widget.h"
#include <QToolBar>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    this->resource = 200;//设置初始资源
    this->gainPerSecond = 10;
    this->baseHealth = 5;
    this->win = false;
    this->lose = false;
    this->wave = 15;
    this->nowWave = wave;
    this->selectedUnit = nullptr;
    this->virtualLabel = nullptr;
    this->occupied = false;

    ui->setupUi(this);
    loadMap();
    this->setFixedSize((map->getCol()+4)*Size::step ,(map->getRow()+2)*Size::step);
    addPosition();

    ui->progressBar->setMaximum(15);
    ui->progressBar->setValue(0);
    ui->infoWidget->setText("提示:点击已经放置的单位可以查看单位的详细信息~");

    mapCarrier = new Carrier(this,this);
    mapCarrier->setFixedSize((map->getCol()+4)*Size::step ,(map->getRow()+2)*Size::step);
    mapCarrier->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    mapCarrier->setStyleSheet("QLabel {background-color: transparent;}");
    mapCarrier->show();
    mapCarrier->update();

    enemyCarrier = new EnemyCarrier(this,this);
    enemyCarrier->setFixedSize((map->getCol()+4)*Size::step ,(map->getRow()+2)*Size::step);
    enemyCarrier->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    enemyCarrier->setStyleSheet("QLabel {background-color: transparent;}");
    enemyCarrier->show();

    unitCarrier = new UnitCarrier(this,this);
    unitCarrier->setFixedSize((map->getCol()+4)*Size::step ,(map->getRow()+2)*Size::step);
    unitCarrier->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    unitCarrier->setStyleSheet("QLabel {background-color: transparent;}");
    unitCarrier->show();

    //计时器初始化
    timer=new QTimer(this);
    connect(timer,&QTimer::timeout,enemyCarrier,&EnemyCarrier::refresh);
    connect(timer,&QTimer::timeout,unitCarrier,&UnitCarrier::refresh);
    timer->start(15);

    updateTimer = new QTimer(this);
    connect(updateTimer,&QTimer::timeout,this,updateGame);
    updateTimer->start(30);

    waveTimer = new QTimer(this);
    connect(waveTimer,&QTimer::timeout,this,loadWave);
    waveTimer->start(8000);

    gainTimer = new QTimer(this);
    connect(gainTimer,&QTimer::timeout,this,[=](){
        resource+=gainPerSecond;
    });
    gainTimer->start(1000);

    //将按钮与对应单位链接
    connect(ui->warriorBtn,&QPushButton::clicked,this,[=](){
        if(occupied) delete virtualLabel;
        setChooseCondition(1);
        setMouseTracking(true);
        virtualLabel = new QLabel(this);
        virtualLabel->setScaledContents(true);
        virtualLabel->setGeometry(ui->warriorBtn->pos().x(),ui->warriorBtn->pos().y(),Size::step,Size::step);
        virtualLabel->setPixmap(QPixmap(":/Units/melee_1.png"));
        virtualLabel->setStyleSheet("background:transparent");
        virtualLabel->show();
        occupied = true;
    });//战士

    connect(ui->archerBtn,&QPushButton::clicked,this,[=](){
        if(occupied) delete virtualLabel;
        setChooseCondition(2);
        setMouseTracking(true);
        virtualLabel = new QLabel(this);
        virtualLabel->setScaledContents(true);
        virtualLabel->setGeometry(ui->warriorBtn->pos().x(),ui->warriorBtn->pos().y(),Size::step,Size::step);
        virtualLabel->setPixmap(QPixmap(":/Units/range_1.png"));
        virtualLabel->setStyleSheet("background:transparent");
        virtualLabel->show();
        occupied = true;
    });//弓箭手

    connect(ui->shieldBtn,&QPushButton::clicked,this,[=](){
        if(occupied) delete virtualLabel;
        setChooseCondition(3);
        setMouseTracking(true);
        virtualLabel = new QLabel(this);
        virtualLabel->setScaledContents(true);
        virtualLabel->setGeometry(ui->warriorBtn->pos().x(),ui->warriorBtn->pos().y(),Size::step,Size::step);
        virtualLabel->setPixmap(QPixmap(":/Units/shield_1.png"));
        virtualLabel->setStyleSheet("background:transparent");
        virtualLabel->show();
        occupied = true;
    });//盾牌

    connect(ui->minerBtn,&QPushButton::clicked,this,[=](){
        if(occupied) delete virtualLabel;
        setChooseCondition(4);
        setMouseTracking(true);
        virtualLabel = new QLabel(this);
        virtualLabel->setScaledContents(true);
        virtualLabel->setGeometry(ui->warriorBtn->pos().x(),ui->warriorBtn->pos().y(),Size::step,Size::step);
        virtualLabel->setPixmap(QPixmap(":/Units/miner_1.png"));
        virtualLabel->setStyleSheet("background:transparent");
        virtualLabel->show();
        occupied = true;
    });//矿工

    connect(ui->flyWarriorBtn,&QPushButton::clicked,this,[=](){
        if(occupied) delete virtualLabel;
        setChooseCondition(5);
        setMouseTracking(true);
        virtualLabel = new QLabel(this);
        virtualLabel->setScaledContents(true);
        virtualLabel->setGeometry(ui->warriorBtn->pos().x(),ui->warriorBtn->pos().y(),Size::step,Size::step);
        virtualLabel->setPixmap(QPixmap(":/Units/flywarrior_1.png"));
        virtualLabel->setStyleSheet("background:transparent");
        virtualLabel->show();
        occupied = true;
    });//飞行战士

    connect(ui->catapultBtn,&QPushButton::clicked,this,[=](){
        if(occupied) delete virtualLabel;
        setChooseCondition(6);
        setMouseTracking(true);
        virtualLabel = new QLabel(this);
        virtualLabel->setScaledContents(true);
        virtualLabel->setGeometry(ui->warriorBtn->pos().x(),ui->warriorBtn->pos().y(),Size::step,Size::step);
        virtualLabel->setPixmap(QPixmap(":/Units/catapult_1.png"));
        virtualLabel->setStyleSheet("background:transparent");
        virtualLabel->show();
        occupied = true;
    });//投石车


    //鼠标悬停时对单位进行说明
    ui->warriorBtn->setToolTip("放置在地面路径\n对近距离内地面敌人单体造成伤害，可以阻挡少量地面敌人");
    ui->archerBtn->setToolTip("放置在路径两侧\n对较远距离内敌人单体造成伤害");
    ui->shieldBtn->setToolTip("放置在地面路径\n血量高，可以阻挡大量地面敌人");
    ui->minerBtn->setToolTip("放置在路径两侧\n无攻击能力，可以提高资源的产出");
    ui->flyWarriorBtn->setToolTip("放置在地面路径\n对近距离内敌人单体造成伤害，可以阻挡少量地面或飞行敌人");
    ui->catapultBtn->setToolTip("放置在路径两侧\n对远距离内敌人造成大量伤害，同时对至多额外两个敌人造成溅射伤害");

    //暂停键设置
    connect(ui->pauseBtn,&QToolButton::clicked,this,[=](){
        gainTimer->stop();
        timer->stop();
        waveTimer->stop();
        QMessageBox::information(this,"暂停","暂停中...");
        gainTimer->start();
        timer->start();
        waveTimer->start();
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::loadMap()
{
    std::ifstream rm("map.txt",std::ios::in);
    if (!rm)
    {
        std::ofstream re("map.txt", std::ios::out);
        return;
    }
    string info;
    std::getline(rm,info);
    string rtmp,ctmp;
    int index = 0;
    int rowsize,colsize = 0;
    for(;info[index] != ',';index++)
    {
        rtmp.push_back(info[index]);
    }
    index++;
    if(rtmp.size() != 0) rowsize = std::stoi(rtmp);//获取地图的行大小
    else return;

    while(info[index] != ',')
    {
        ctmp.push_back(info[index]);
        index++;
    }
    index++;
    if(ctmp.size() != 0) colsize = std::stoi(ctmp);//获取地图的列大小
    else return;

    //导入地图尺寸过大的处理
    if(rowsize > 7 || colsize > 12)
    {
        qDebug() << "地图尺寸过大!" << endl;
        exit(-1);
    }

    string rntmp;
    while((unsigned)index < info.size())
    {
        rntmp.push_back(info[index]);
        index++;
    }
    if(rntmp.size() != 0) roadNumber = std::stoi(rntmp);

    this->map = new Map(rowsize,colsize);//创建map对象
    int** local;
    local = new int*[rowsize];
    for(int i = 0;i<rowsize;i++)
    {
        local[i] = new int[colsize];
    }

    for(int i = 0; i < this->map->getRow();i++)
    {
        string line;
        std::getline(rm,line);
        for(int j = 0;j < this->map->getCol();j++)
        {
            local[i][j] = line[2*j] - '0';//读取地图信息
        }
    }
    map->setMap(local);//设置地图
    delete[] local;

    //设置敌人的运动轨迹
    for(int i = 0;i < roadNumber;i++)
    {
        Road* r = new Road(rowsize*colsize);
        roads.push_back(r);
        string road;
        std::getline(rm,road);
        bool first = true;
        unsigned int new_index = 0;
        wayPoint* helper = nullptr;
        while(new_index < road.size())
        {
            string tmp;
            for(;road[new_index] != ',' && new_index < road.size();new_index++)
            {
                tmp.push_back(road[new_index]);
            }
            new_index++;
            int pos = std::stoi(tmp);
            if(first)
            {
                first = false;
                wayPoint* way = new wayPoint(QPoint( (pos%colsize)*Size::step+Size::margin + Size::step/2, (pos/colsize)*Size::step+Size::margin + Size::step/2));
                roads[i]->setRoad(pos,way);
                helper = way;
            }
            else
            {
                wayPoint* way = new wayPoint(QPoint( (pos%colsize)*Size::step+Size::margin + Size::step/2, (pos/colsize)*Size::step+Size::margin + Size::step/2));
                roads[i]->setRoad(pos,way);
                helper->setNextPoint(way);
                helper = way;
            }
        }
    }

}

void Widget::addPosition()
{
    for(int i = 0; i < map->getRow(); i++)
    {
        for(int j = 0; j < map->getCol(); j++)
        {
            if(map->getMap()[i][j] == 3)
            {
                Position* p = new Position(QPoint(Size::margin + Size::step/2 + j*Size::step,Size::margin + Size::step/2 + i*Size::step), 0);
                positionList.push_back(p);
            }
            else if(map->getMap()[i][j] == 4)
            {
                Position* p = new Position(QPoint(Size::margin + Size::step/2 + j*Size::step,Size::margin + Size::step/2 + i*Size::step), 1);
                positionList.push_back(p);
            }

        }
    }

}

void Widget::paintEvent(QPaintEvent*)
{
    //画出游戏结束的画面
    if(lose || win)
    {
        QString text=lose ? "YOU LOSE":"YOU WIN";
        QPainter painter(this);
        QFont font1;
        font1.setFamily("SimHei");
        font1.setPixelSize(50);
        painter.setFont(font1);
        painter.setPen(Qt::red);
        painter.drawText(rect(),Qt::AlignCenter,text);
        enemyCarrier->hide();
        unitCarrier->hide();
        mapCarrier->hide();
        ui->bigWidget->hide();
        return ;
    }

    QPainter painter(this);
    QBrush brush = painter.brush();//保存默认填充色
    painter.setPen(QPen(Qt::black,5));

    //画出敌人前进路线
//    for(int i = 0;i < roadNumber;i++)
//    {
//        wayPoint* helper = nullptr;
//        for(int j = 0; j < roads[i]->getSize();j++)
//        {
//            if(this->roads[i]->getRoad()[j]!=nullptr)
//            {
//                helper = roads[i]->getRoad()[j];
//                break;
//            }
//        }
//        while(helper->getNextPoint()!= nullptr)
//        {
//            helper->draw(&painter);
//            helper = helper->getNextPoint();
//        }
//    }

    //画出资源
    QFont font1;
    font1.setFamily("SimHei");
    font1.setPixelSize(30);
    painter.setFont(font1);
    QString r1 = QString::number(this->resource);
    painter.drawText(Size::margin,Size::margin - 20,"资源:" + r1);

    //画出资源增益
    QString r2 = QString::number(this->gainPerSecond);
    painter.drawText(Size::margin + Size::step*2,Size::margin - 20,"资源增速/秒:" + r2);

    //画出基地血量
    QString r3 = QString::number(this->baseHealth);
    painter.drawText(Size::margin + Size::step*4,Size::margin - 20,"基地血量:" + r3);
}

void Widget::mousePressEvent(QMouseEvent* event)
{
    QPoint pressPos=event->pos();//得到鼠标点击的位置
    for(int i = 0; i < positionList.size();i++)
    {
        if(Qt::LeftButton == event->button() && chooseCondition != 0)
        {
            if(positionList[i]->containPos(pressPos) && !positionList[i]->hasUnit())
            {
                if(positionList[i]->getType() == 0)
                {
                    switch(chooseCondition)
                    {
                    case 1:
                    {
                        if(resource < 100) break;
                        Unit* unit = new Warrior(positionList[i]->getCenterPos(),this);
                        unit->setParent(nullptr);
                        unit->setPosition(positionList[i]);
                        unitList.push_back(unit);
                        resource-=100;
                        positionList[i]->setHasUnit(true);
                        break;
                    }
                    case 3:
                    {
                        if(resource < 100) break;
                        Unit* unit = new Shield(positionList[i]->getCenterPos(),this);
                        unit->setParent(nullptr);
                        unit->setPosition(positionList[i]);
                        unitList.push_back(unit);
                        resource-=100;
                        positionList[i]->setHasUnit(true);
                        break;
                    }
                    case 5:
                    {
                        if(resource < 125) break;
                        Unit* unit = new FlyWarrior(positionList[i]->getCenterPos(),this);
                        unit->setParent(nullptr);
                        unit->setPosition(positionList[i]);
                        unitList.push_back(unit);
                        resource-=125;
                        positionList[i]->setHasUnit(true);
                        break;
                    }

                    }
                    setChooseCondition();
                    virtualLabel->hide();
                    delete virtualLabel;
                    virtualLabel = nullptr;
                }
                else if(positionList[i]->getType() == 1)
                {
                    switch(chooseCondition)
                    {
                    case 2:
                    {
                        if(resource < 100) break;
                        Unit* unit = new Archer(positionList[i]->getCenterPos(),this);
                        unit->setParent(nullptr);
                        unit->setPosition(positionList[i]);
                        unitList.push_back(unit);
                        resource-=100;
                        positionList[i]->setHasUnit(true);
                        break;
                    }
                    case 4:
                    {
                        if(resource < 125) break;
                        Unit* unit = new Miner(positionList[i]->getCenterPos(),this);
                        unit->setParent(nullptr);
                        unit->setPosition(positionList[i]);
                        unitList.push_back(unit);
                        resource-=125;
                        positionList[i]->setHasUnit(true);
                        break;
                    }
                    case 6:
                    {
                        if(resource < 150) break;
                        Unit* unit = new Catapult(positionList[i]->getCenterPos(),this);
                        unit->setParent(nullptr);
                        unit->setPosition(positionList[i]);
                        unitList.push_back(unit);
                        resource-=150;
                        positionList[i]->setHasUnit(true);
                        break;
                    }

                    }
                    setChooseCondition();
                    virtualLabel->hide();
                    delete virtualLabel;
                    virtualLabel = nullptr;
                }
                update();
                break;
            }
        }
        else if(Qt::LeftButton == event->button() && positionList[i]->hasUnit() && selectedUnit==nullptr && positionList[i]->containPos(pressPos))
        {
            for(int j = 0; j < unitList.size();j++)
            {
                if(collide(unitList[j]->getPos(),positionList[i]->getCenterPos(),5))
                {
                    selectedUnit = unitList[j];
                    selectedUnit->setSelected();
                    break;
                }
            }
            break;
        }
        else if(selectedUnit!= nullptr)
        {
            selectedUnit->setSelected(false);
            selectedUnit = nullptr;

            int tipChooser = rand()%3;
            switch(tipChooser)
            {
            case 1:
            {
                ui->infoWidget->setText("提示:点击已经放置的单位可以查看单位的详细信息~");
                break;
            }
            case 2:
            {
                ui->infoWidget->setText("提示:气球跑得太快?用飞行战士拦住它!");
                break;
            }
            case 3:
            {
            ui->infoWidget->setText("提示:不知道单位的作用时,可以把鼠标放在单位上查看简介哦~");
            break;
            }
            }
            break;
        }

    }
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(chooseCondition)
    {
        virtualLabel->move(event->x()-Size::step/2,event->y()-Size::step/2);
        virtualLabel->raise();
    }
}

void Widget::awardCoin()
{
    this->resource+=25;
}

void Widget::removeEnemy(Enemy * enemy)
{
    if(enemy != nullptr)
    {
        enemyList.removeOne(enemy);
        enemy->deleteLater();
    }
}

void Widget::removeUnit(Unit* unit)
{
    if(unit != nullptr)
    {
        unitList.removeOne(unit);
        unit->deleteLater();
    }
}

QList<Enemy *> Widget::getEnemyList()
{
    return this->enemyList;
}

QList<Unit*> Widget::getUnitList()
{
    return this->unitList;
}

void Widget::baseHealthRecuce(int damage)
{
    this->baseHealth-=damage;
    if(this->baseHealth <= 0)
    {
        this->lose = true;
    }
}

void Widget::loadWave()
{
    int roadChooser = rand()%(roads.size());
    int enemyChooser = rand()%3;
    wayPoint * startWayPoint;

    //enemyChooser = 2;//debug用

    for(int i = 0;i < roads[roadChooser]->getSize();i++)
    {
        if(roads[roadChooser]->getRoad()[i] != nullptr)
        {
            startWayPoint = roads[roadChooser]->getRoad()[i];
            break;
        }
    }
    Enemy * enemy = nullptr;
    if(this->nowWave <= 1)
    {
        enemy = new Knight(startWayPoint,this);
    }
    else
    {
        switch(enemyChooser)
        {
        case 0:
        {
            enemy=new OrdinaryEnemy(startWayPoint,this);
            break;
        }
        case 1:
        {
            enemy=new HackButeer(startWayPoint,this);
            break;
        }
        case 2:
        {
            enemy=new FloatPlane(startWayPoint,this);
            break;
        }
        }
    }
    waveTimer->start(2000);
    enemy->setActive();
    this->enemyList.push_back(enemy);
    this->nowWave--;
    ui->progressBar->setValue(wave-nowWave);
    if(this->nowWave <= 0)
    {
        this->waveTimer->stop();
    }
    enemy = nullptr;
}

void Widget::updateGame()
{
    foreach(Enemy * enemy,enemyList)
    {
        enemy->findUnit();
        enemy->attack();
    }
    foreach (Unit* unit, unitList)
    {
        unit->findEnemy();
        unit->attack();
    }
    if(enemyList.empty() && this->nowWave <= 0)
    {
        this->win = true;
    }
}

void Widget::setChooseCondition(int choose)
{
    chooseCondition = choose;
}

void Widget::resourceGain(int gain)
{
    gainPerSecond += gain;
}

Map* Widget::getMap()
{
    return map;
}

QTextBrowser* Widget::getInfoBrowser()
{
    return ui->infoWidget;
}
