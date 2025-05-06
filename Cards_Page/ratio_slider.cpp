#include "Ratio_Slider.h"

Ratio_Slider::Ratio_Slider(QWidget* parent)
    : QScrollArea(parent)
{
    QPalette palette;
    palette.setColor(QPalette::Base, Qt::transparent);
    setPalette(palette);

    customScrollBar = new CustomScrollBar(this);
    setVerticalScrollBar(customScrollBar);
}
