#ifndef CARDS_PAGE_H
#define CARDS_PAGE_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QScrollArea>
#include <QResizeEvent>
#include "cardlayoutmanager.h"
#include "anime_card.h"
#include "../Singleton_Set/Database_Related.h"
#include "../Singleton_Set/file_related.h"
#include "Ratio_Slider.h"
#include "qscrollarea.h"

class Cards_Page : public QWidget
{
    Q_OBJECT

public:
    explicit Cards_Page(QWidget* parent = nullptr);

    CardLayoutManager* manager;
    Ratio_Slider* scroll_area;

protected:
    void resizeEvent(QResizeEvent* event) override;

signals:

private:
    int Widget_Activity_Y_Coordinate = 0;
};

#endif // CARDS_PAGE_H
