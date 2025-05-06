#include "left_window_tip.h"

Left_Window_Tip::Left_Window_Tip(QWidget* parent)
    : QWidget{ parent }
{
    this->setFixedWidth(60);

    quit_button = new Function_Button(QPixmap("://img/关闭.png"), this);
    quit_button->setFixedSize(30, 30);

    min_button = new Function_Button(QPixmap("://img/最小化.png"), this);
    min_button->setFixedSize(30, 30);

    max_button = new Function_Button(QPixmap("://img/最大化.png"), this);
    max_button->setFixedSize(30, 30);
}

void Left_Window_Tip::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    QPainterPath path;
    path.addRoundedRect(rect(), 20, 20);
    painter.setClipPath(path);

    painter.setBrush(QColor(1, 1, 255, 50));
    painter.drawRoundedRect(rect(), 20, 20);
}

void Left_Window_Tip::resizeEvent(QResizeEvent* event)
{
    max_button->move(15, this->height() / 2 - 130);
    quit_button->move(15, this->height() / 2 - 20);
    min_button->move(15, this->height() / 2 + 100);
}
