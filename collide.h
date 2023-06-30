#ifndef COLLIDE_H
#define COLLIDE_H

inline bool collide(QPoint p1,QPoint p2, int r = 0)
{
    int x=p1.x()-p2.x();
    int y=p1.y()-p2.y();
    int dis=sqrt(x*x+y*y);
    if(dis <= r)
    {
        return true;
    }
    return false;
}

#endif // COLLIDE_H
