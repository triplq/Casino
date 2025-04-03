#include "reel.h"

Reel::Reel(QWidget *parent)
    : QWidget{parent}
{
    anim_group = new QParallelAnimationGroup;
    anim_group->setParent(this);

    QPropertyAnimation *animReel = new QPropertyAnimation(this, "scrollOffset");
    animReel->setEasingCurve(QEasingCurve::OutExpo);
    animReel->setDuration(2500);
    animReel->setStartValue(0.0);
    animReel->setEndValue(10.0);

    anim_group->addAnimation(animReel);

    connect(anim_group, &QParallelAnimationGroup::finished, this, &Reel::onAnimationFinished);
}

void Reel::setScrollOffset(qreal offset)
{
    if(m_scrollOffset != offset)
    {
        m_scrollOffset = offset;
        update();

        emit scrollOffsetChanged();
    }
}

void Reel::snapToPosition()
{
    if(std::fmod(m_scrollOffset, 1.0) != 0.5)
        m_scrollOffset = qRound(m_scrollOffset) + 0.5;

    update();
}

void Reel::setSlots(const QVector<QPixmap>& n_images)
{
    images = n_images;

    update();
}

void Reel::spin(int durationMs)
{
    if(anim_group->state() == QAbstractAnimation::Running)
        anim_group->stop();

    QPropertyAnimation* animReel = qobject_cast<QPropertyAnimation*>(anim_group->animationAt(0));
    animReel->setStartValue(m_scrollOffset);
    animReel->setDuration(durationMs);
    animReel->setEndValue(m_scrollOffset + 10.5 + QRandomGenerator::global()->bounded(3));

    anim_group->start();
}

qreal Reel::currentOffsetIndex() const
{
    //return static_cast<int>(qRound(m_scrollOffset) % images.size());

    return m_scrollOffset; // % images.size();
}

qreal Reel::getScrollOffset() const { return m_scrollOffset; }

void Reel::onAnimationFinished()
{
    snapToPosition();

    update();

    emit spinningStoped();
}

void Reel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.fillRect(rect(), Qt::black);

    const int visibleImages = 2;
    const qreal imageHeight = height() / visibleImages;

    if(images.isEmpty()) return;

    for(int i = -1; i <= visibleImages; i++)
    {
        qreal yPos = (i - std::fmod(m_scrollOffset, 1.0)) * imageHeight;
        int imageIndex = (i + static_cast<int>(m_scrollOffset)) % images.size();

        if(imageIndex < 0) imageIndex += images.size();

        painter.drawPixmap(0, yPos, width(), imageHeight, images.at(imageIndex));
    }

    update();
}
