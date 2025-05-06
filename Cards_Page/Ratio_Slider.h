#ifndef RATIO_SLIDER_H
#define RATIO_SLIDER_H

#include <QWidget>
#include <QEvent>
#include <QScrollArea>
#include "customscrollbar.h"
#include "../Singleton_Set/central_bundle_bridge.h"

class Ratio_Slider : public QScrollArea
{
    Q_OBJECT

public:
    explicit Ratio_Slider(QWidget* parent = nullptr);

signals:
    void scroll_xy(int x, int y);

private:
    CustomScrollBar* customScrollBar;
};

#endif // RATIO_SLIDER_H
