#ifndef REEL_H
#define REEL_H

#include <QWidget>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QPainter>
#include <QRandomGenerator>

class Reel : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal scrollOffset READ getScrollOffset WRITE setScrollOffset NOTIFY scrollOffsetChanged)
private:
    QVector<QPixmap> images;
    qreal m_scrollOffset = 0.5;
    QParallelAnimationGroup *anim_group;

    void setScrollOffset(qreal offset);
    void snapToPosition();

public:
    explicit Reel(QWidget *parent = nullptr);

    void setSlots(const QVector<QPixmap>& n_images);
    void spin(int durationMs);
    void stop_spinning();
    int currentOffsetIndex() const;
    qreal getScrollOffset() const;

signals:
    void spinningFinished();
    void spinningStopped();
    void scrollOffsetChanged();

protected:
    void paintEvent(QPaintEvent *event) override;

};

#endif // REEL_H
