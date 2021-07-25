#ifndef LINECLIP_H
#define LINECLIP_H

#include <QWidget>
#include <QMouseEvent>
#include <QPushButton>

namespace Ui {
class LineClip;
}

class LineClip : public QWidget
{
    Q_OBJECT

public:
    explicit LineClip(QWidget *parent = nullptr);
    ~LineClip();

private:
    QRgb lineColor;
    QRgb clipColor;
    QPushButton *CS;
    QPoint startPoint;
    QPoint endPoint;
    QPixmap Pix;
    int xl, yl, xr, yr;
    int l, r, b, t;
    bool flipflop = true;
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void cs();
    int encode(float x, float y);

private:
    Ui::LineClip *ui;
};

#endif // LINECLIP_H
