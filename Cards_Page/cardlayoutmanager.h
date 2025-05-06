#ifndef CARDLAYOUTMANAGER_H
#define CARDLAYOUTMANAGER_H

#include <QWidget>
#include <QList>
#include <QPropertyAnimation>
#include <QResizeEvent>
#include "anime_card.h"
#include "Menu_Set/right_click_menu_set.h"
#include "Menu_Set/new_menu_set.h"
#include "../Singleton_Set/Database_Related.h"
#include "../Singleton_Set/File_Related.h"
#include "../Singleton_Set/central_bundle_bridge.h"
#include "ratio_slider.h"

class CardLayoutManager : public QWidget
{
    Q_OBJECT

public:
    explicit CardLayoutManager(QWidget* parent = nullptr);
    void addCard(Anime_Card* card);
    void setAnimationDuration(int duration);

    Right_Click_Menu_Set* right_click_menu_set;

public slots:
    void filterByYear(const QString year);
    void showAllCards();
    void Update_Layout_Slot_Function();
    void Delete_Card(Anime_Card* anime_card);
    void Create_Menu(int id);
    void Add_Card_To_Layout(int Create_Location_Card, Anime_Card* anime_card);
    void Edit_Card(Anime_Card* anime_card);
    void Set_Current_Visible_Y_Coordinate(int y_coordinate);

protected:
    void resizeEvent(QResizeEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

private:
    int cardWidth = 190;
    int cardHeight = 320;
    int windowWidth = 0;
    int windowHeight = 0;
    int m_verticalSpacing = 15;
    int Max_Card_Value = 0;
    int Center_Value_Per_Row = 0;
    void Basic_Parameters();

    QRect normalArea;
    QRect extendedArea;
    int Total_Height;
    int max_total_height = 0;

    void updateLayout();
    QPoint calculateCardPosition(int visibleIndex);
    bool isInExtendedVisibleArea(const QPoint& pos);

    QList<Anime_Card*> m_cards;
    int m_animationDuration = 280;
    int current_visible_y_coordinate = 0;

private:
    New_Menu_Set* Menu = nullptr;
};

#endif // CARDLAYOUTMANAGER_H
