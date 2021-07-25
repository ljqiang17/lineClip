#include "lineclip.h"
#include "ui_lineclip.h"
#include <QPainter>


LineClip::LineClip(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LineClip)
{
    ui->setupUi(this);

    //裁剪边界，分别为左边界、上边界、右边界、下边界
    xl = 150;
    yl = 150;
    xr = 450;
    yr = 450;

    //用于区域编码
    l = 1;
    r = 2;
    b = 4;
    t = 8;

    //设置主窗口
    setWindowTitle("Cohen-Sutherland");
    setAutoFillBackground(true);
    setFixedSize(600, 600);
    setFocusPolicy(Qt::StrongFocus);
    Pix = QPixmap(560, 560);
    Pix.fill(Qt::transparent);

    //自定义颜色，红色表示原线段颜色，绿色表示裁剪后的颜色
    lineColor = qRgb(255, 0, 0);
    clipColor = qRgb(0, 255, 0);

    //设置CS Button
    CS = new QPushButton(this);
    CS->setText("Cohen-Sutherland");
    CS->adjustSize();
    CS->move(10, 0);
    connect(CS, &QPushButton::pressed, this, &LineClip::cs); //将button与执行算法的函数连接起来

}

void LineClip::paintEvent(QPaintEvent *event) {//重写painteven函数绘制裁剪区域
    QPainter myPainter(this);
    QPen myPen(Qt::black);
    myPen.setWidth(2);
    myPainter.setPen(myPen);

    //绘制裁剪区域
    myPainter.drawRect(150, 150, 300, 300);
    myPainter.drawPixmap(0, 0, Pix);
}

void LineClip::mousePressEvent(QMouseEvent *event) {//重写mousepressevent函数，用于绘制待裁剪线段
    //设置画笔
    QPainter myPainter(&Pix);
    QPen myPen(lineColor);
    myPen.setWidth(3);
    myPainter.setPen(myPen);
    myPainter.setRenderHint(QPainter::Antialiasing, true);

    //设置起始点和终点，以起始点和终点绘制直线，表示待裁剪的线段
    if(flipflop) {
        startPoint = event->pos();
    } else {
        endPoint = event->pos();
        myPainter.drawLine(startPoint, endPoint);
    }
    update();
    flipflop = !flipflop;
}



void LineClip::cs() { //Cohen-Sutherland算法
    //设置画笔
    QPainter myPainter(&Pix);
    QPen myPen(clipColor);
    myPen.setWidth(3);
    myPainter.setPen(myPen);
    //记录起始点和终点的x和y值
    float x1 = startPoint.x();
    float y1 = startPoint.y();
    float x2 = endPoint.x();
    float y2 = endPoint.y();

    int code1, code2, code;
    float x, y, x0, y0;

    //对起始点和终点进行编码
    code1 = encode(x1, y1);
    code2 = encode(x2, y2);

    //当code1 & code2 == 0时，不需要对线段的左边进行变换，所以只考虑一下情况
    while((code1 != 0) || (code2 != 0)) { //
        if((code1 & code2) != 0) { //显然不可见，直接舍弃，裁剪结束
            return;
        }

        if(code1 != 0) {
            code = code1;
        } else {
            code = code2;
        }

        x0 = x1;
        y0 = y1;
        if((l & code) != 0) { //在裁剪窗口左边
            x = xl;
            y = y0 - (x0 - x) * (y1- y2) /(x1 - x2);
            //y = y1+(y2-y1)*(xr-x1)/(x2-x1);
        } else if((r & code) != 0) { //在裁剪窗口右边
            x = xr;
            y = y0 - (x0 - x) * (y1 - y2) / (x1- x2);
            //y=y1+(y2-y1)*(xr-x1)/(x2-x1);
        } else if((b & code) != 0) { //在裁剪窗口下边
            y=yl;
            x = x0 - (y0 - y) * (x1 - x2) / (y1- y2);
            //x=x1+(x2-x1)*(yl-y1)/(y2-y1);
        } else if((t & code) != 0) { //在裁剪窗口上边
            y = yr;
            x = x0 - (y0 - y) * (x1 - x2) / (y1 - y2);
            //x=x1+(x2-x1)*(yr-y1)/(y2-y1);
        }
        //更新
        if(code == code1) {
            x1 = x;
            y1 = y;
            code1 = encode(x, y);
        } else {
            x2 = x;
            y2 = y;
            code2 = encode(x, y);
        }

    }
    //找到裁剪之后的线段的起始点和终点，绘制直线
    myPainter.drawLine((int)x1, (int)y1, (int)x2, (int)y2);
    update();
    return;


}

int LineClip::encode(float x, float y) {//编码函数
    int code = 0;
    if(x < xl)
        code |= 1;
    if(x > xr)
        code |= 2;
    if(y < yl)
        code |= 4;
    if(y > yr)
        code |= 8;

    return code;
}

LineClip::~LineClip()
{
    delete ui;
}
