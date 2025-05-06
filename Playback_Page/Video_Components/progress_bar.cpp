#include "progress_bar.h"

Progress_Bar::Progress_Bar(QWidget* parent)
    : QSlider(parent)
{
    setContextMenuPolicy(Qt::NoContextMenu);
    setOrientation(Qt::Horizontal);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

void Progress_Bar::paintEvent(QPaintEvent* ev)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    QStyleOptionSlider opt;
    initStyleOption(&opt);

    QRect grooveRect = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderGroove, this);
    QRect handleRect = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);

    painter.setBrush(Slot_Color);
    painter.drawRect(grooveRect);

    QRect activeRect = grooveRect;
    activeRect.setRight(handleRect.center().x());
    painter.setBrush(Path_Color);
    painter.drawRect(activeRect);

    painter.setPen(Qt::NoPen);
    painter.setBrush(Slider_Color);
    painter.drawRect(handleRect.adjusted(0, 0, -8, 0));
}
