#include "horizontal_navigation_page.h"

Horizontal_Navigation_Page::Horizontal_Navigation_Page(QWidget* parent)
    : QWidget{ parent }
{
    Slider_Component = new Button_Slider_Component(this);
    this->resize(0, Slider_Component->height());
}

void Horizontal_Navigation_Page::resizeEvent(QResizeEvent* event)
{
    Slider_Component->m_Bar_Moving_Point = this->parentWidget()->width() / 3;

    if (this->width() - Slider_Component->width() > Slider_Component->pos().x())
    {
        int x = event->size().width() - event->oldSize().width();
        Slider_Component->move(Slider_Component->pos().x() - x, Slider_Component->pos().y());
    }

    QWidget::resizeEvent(event);
}
