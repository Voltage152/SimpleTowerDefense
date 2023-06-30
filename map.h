#ifndef MAP_H
#define MAP_H

#include <QObject>

class Map : public QObject
{
    Q_OBJECT
public:
    explicit Map(QObject *parent = nullptr);
    Map(int row,int col);
    ~Map();
    int** getMap() const;
    void setMap(int** local);
    int getRow();
    int getCol();
private:
    int rowSize;
    int colSize;
    int* *map;
signals:

public slots:
};

#endif // MAP_H
