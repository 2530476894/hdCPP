#ifndef SLIDER_H
#define SLIDER_H
#include <QSlider>
#include <QDebug>

class Slider : public QSlider
{
	Q_OBJECT
public:
    Slider(QWidget *parent = nullptr);
    ~Slider();

signals:
    void onEnter();
    void onLeave();
    void onHover(int pos, int value);

protected:
    virtual void enterEvent(QEvent *e);
    virtual void leaveEvent(QEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);
//#if CODE_FOR_CLICK == 1
    inline int pick(const QPoint &pt) const; //定位坐标
    int pixelPosToRangeValue(int pos) const;//单击到鼠标位置
    void initStyleOption_Qt430(QStyleOptionSlider *option) const;
//#endif
};

#endif //SLIDER_H

