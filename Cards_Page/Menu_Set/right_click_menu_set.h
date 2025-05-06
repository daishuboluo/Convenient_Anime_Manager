#ifndef RIGHT_CLICK_MENU_SET_H
#define RIGHT_CLICK_MENU_SET_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include "right_click_menu_button.h"
#include "../anime_card.h"

class Right_Click_Menu_Set : public QWidget
{
    Q_OBJECT
public:
    explicit Right_Click_Menu_Set(QWidget* parent = nullptr);
    void When_On_Card(Anime_Card* anime_card);
    void Not_On_Card(Anime_Card* anime_card);
    void Reset_Position();

public slots:

signals:
    void Card_Deleted_Signal(Anime_Card* anime_card);
    void Card_New_Signal(int id);
    void Card_Edit_Signal(Anime_Card* anime_card);

private:
    QList<Right_Click_Menu_Button*> When_On_Card_list;
    QList<Right_Click_Menu_Button*> Not_On_Card_list;
    Anime_Card* anime_card;

    Right_Click_Menu_Button* button;
    Right_Click_Menu_Button* button2;
    Right_Click_Menu_Button* button3;
    Right_Click_Menu_Button* button4;
    Right_Click_Menu_Button* button5;
    Right_Click_Menu_Button* button6;
    Right_Click_Menu_Button* button7;
};

#endif // RIGHT_CLICK_MENU_SET_H
