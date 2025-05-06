#ifndef HORIZONTAL_NAVIGATION_PAGE_H
#define HORIZONTAL_NAVIGATION_PAGE_H

#include <QWidget>
#include <QResizeEvent>
#include <QGraphicsDropShadowEffect>
#include "button_slider_component.h"

class Horizontal_Navigation_Page : public QWidget
{
    Q_OBJECT

public:
    explicit Horizontal_Navigation_Page(QWidget* parent = nullptr);
    Button_Slider_Component* Slider_Component;

protected:
    void resizeEvent(QResizeEvent* event) override;
 

};

#endif // HORIZONTAL_NAVIGATION_PAGE_H
