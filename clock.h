#ifndef CLOCK_H
#define CLOCK_H

#include <QWidget>
#include<QPaintEvent>
class Clock : public QWidget
{
    Q_OBJECT

public:
    Clock(QWidget *parent = nullptr);
    ~Clock();
    QPoint p;
    void paintEvent(QPaintEvent *event);
    void drawClock(QPainter *painter);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};
#endif // CLOCK_H
