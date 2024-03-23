#include "clock.h"
#include<QPainter>
#include<QDebug>
#include<QTime>
#include<QTimer>
Clock::Clock(QWidget *parent)
    : QWidget(parent)
{

    setWindowFlags(Qt::FramelessWindowHint);//设置无窗口框架边界
//    setAttribute(Qt::WA_TranslucentBackground);//设置窗口背景透明

    QTimer *t=new QTimer(this);
    connect(t , SIGNAL(timeout()),this,SLOT(update()));
    t->start(1000);
}

Clock::~Clock()
{
}

void Clock::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen(QColor(0,255,0));
    painter.setPen(pen);
    int side=std::min(width(),height());
    painter.setRenderHint(QPainter::Antialiasing);
    QImage *img=new QImage(":/imgs/img/beijing2.jpg");
    painter.drawImage(this->rect(),*img);
    painter.setViewport((width()-side)/2,(height()-side)/2,side,side);

    painter.setWindow(0,0,200,200);
    painter.translate(100,100);
    painter.drawEllipse(-98,-98,196,196);
    painter.drawPoint(0,0);
    drawClock(&painter);

}

void Clock::drawClock(QPainter *painter)
{
    QTime time=QTime::currentTime();
    int h=time.hour(),m=time.minute(),s=time.second();
    QVector<QPoint> hs,ms,ss;
    hs={QPoint(0,-50),QPoint(5,10),QPoint(0,15),QPoint(-5,10)};
    ms={QPoint(0,-60),QPoint(5,10),QPoint(0,15),QPoint(-5,10)};
    ss={QPoint(0,-70),QPoint(5,10),QPoint(0,15),QPoint(-5,10)};
    for(int i=1;i<=60;i++){

        painter->rotate(6);
        if(i%5==0){
            painter->drawLine(0,-98,0,-80);
            if(i/5%3==0)painter->drawText(-20,-80,40,40,Qt::AlignHCenter|Qt::AlignTop,QString::number(i/5));
        }else{
            painter->drawLine(0,-98,0,-88);
        }
    }
    painter->save();
    painter->rotate(h*30+m/2);
    painter->drawPolygon(hs);
    painter->restore();
    painter->rotate(m*6+s/10);
    painter->drawPolygon(ms);
    painter->restore();
    painter->rotate(+s*6);
    painter->drawPolygon(ss);
}
void Clock::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        this->move(event->globalPos() - p);
    }
}

void Clock::mousePressEvent(QMouseEvent *event)
{
    // 如果是鼠标左键, 瞬间状态
    if(event->button() == Qt::LeftButton)
    {
        // 相对位置 = 当前鼠标位置 - 左上角的位置;
        p = event->globalPos() - this->geometry().topLeft();
    }
}
