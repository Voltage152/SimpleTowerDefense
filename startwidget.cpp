#include "startwidget.h"
#include "ui_startwidget.h"

StartWidget::StartWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartWidget)
{
    ui->setupUi(this);
    connect(ui->startButton,&QPushButton::clicked,this,[=](){
        Widget* game = new Widget(this);

        this->hide();
        game->setWindowFlags(Qt::Window);
        game->show();
    });
}

StartWidget::~StartWidget()
{
    delete ui;
}
