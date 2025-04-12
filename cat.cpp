#include "cat.h"

Cat::Cat(QLabel *parent)
    : QLabel{parent}
{
    open_cat = new QPixmap(":/cat/opencat.png");
    close_cat = new QPixmap(":/cat/closecat.png");
    this->setPixmap(*close_cat);

    anim = new QPropertyAnimation(this, "pos");
}

void Cat::set_start_pos(int x, int y)
{
    this->setPixmap(*close_cat);

    if(anim->state() == QAbstractAnimation::Running)
        anim->stop();

    this->setGeometry(x, y, close_cat->height(), close_cat->width());
}

void Cat::start_animation()
{
    anim->setDuration(3000);
    anim->setStartValue(QPoint(0, close_cat->height()));
    anim->setEndValue(QPoint(0, close_cat->height() - (close_cat->height() * 0.8)));
    anim->start();
}

void Cat::back_animation()
{
    anim->setDuration(500);
    anim->setStartValue(QPoint(0, close_cat->height() - (close_cat->height() * 0.8)));
    anim->setEndValue(QPoint(0, close_cat->height()));
    anim->start();
}

void Cat::win()
{
    this->setPixmap(*open_cat);
}


//хлопает ртом при победе
//быстро убегает после неудачного ролла
