#ifndef CAT_H
#define CAT_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QPainter>

class Cat : public QLabel
{
    Q_OBJECT
private:
    QPixmap *open_cat;
    QPixmap *close_cat;

    QPropertyAnimation *anim;

public:
    explicit Cat(QLabel *parent = nullptr);

    void start_animation();
    void back_animation();
    void set_start_pos(int x, int y);
    void win();
};

#endif // CAT_H
