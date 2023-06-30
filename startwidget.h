#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include <QWidget>
#include "mainWidget.h"

namespace Ui {
class StartWidget;
}

class StartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StartWidget(QWidget *parent = 0);
    ~StartWidget();

private:
    Ui::StartWidget *ui;
};

#endif // STARTWIDGET_H
