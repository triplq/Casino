#ifndef REEL_H
#define REEL_H

#include <QWidget>
#include <QTimer>
#include <QTimeLine>
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
    qreal m_scrollOffset = 0.0;
    QParallelAnimationGroup *anim_group;

    void setScrollOffset(qreal offset);
    void snapToPosition();

public:
    explicit Reel(QWidget *parent = nullptr);

    void setSlots(const QVector<QPixmap>& n_images);
    void spin(int durationMs);
    qreal currentOffsetIndex() const;
    qreal getScrollOffset() const;

signals:
    void spinningStoped();
    void scrollOffsetChanged();

private slots:
    void onAnimationFinished();

protected:
    void paintEvent(QPaintEvent *event) override;

};

#endif // REEL_H
