#include "right_click_menu_set.h"

Right_Click_Menu_Set::Right_Click_Menu_Set(QWidget* parent)
    : QWidget{ parent }
{
    button3 = new Right_Click_Menu_Button(QPixmap("://img/新建.png"), QString("新建"), this);
    connect(button3, &Right_Click_Menu_Button::Clicked, this, [this] {
        if (anime_card == nullptr) emit Card_New_Signal(-1);
        else emit Card_New_Signal(anime_card->Card_ID());
        this->hide();
        });

    When_On_Card_list.append(button3);
    Not_On_Card_list.append(button3);

    button = new Right_Click_Menu_Button(QPixmap("://img/编辑.png"), QString("编辑"), this);
    connect(button, &Right_Click_Menu_Button::Clicked, this, [this] {
        emit Card_Edit_Signal(anime_card);
        });
    When_On_Card_list.append(button);

    button2 = new Right_Click_Menu_Button(QPixmap("://img/删除.png"), QString("删除"), this);
    connect(button2, &Right_Click_Menu_Button::Clicked, this, [this] {
        emit Card_Deleted_Signal(anime_card);
        this->hide();
        });
    When_On_Card_list.append(button2);

    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(11, 11);
    shadow->setBlurRadius(55);
    shadow->setColor(QColor(255, 216, 251, 66));
    this->setGraphicsEffect(shadow);
}

void Right_Click_Menu_Set::When_On_Card(Anime_Card* anime_card)
{
    this->Reset_Position();
    this->raise();
    this->show();
    this->anime_card = anime_card;

    int y = 0;
    for (auto& button : When_On_Card_list)
    {
        QPropertyAnimation* animation = new QPropertyAnimation(button, "pos");
        animation->setDuration(300);
        animation->setStartValue(QPoint(0, 0));
        animation->setEndValue(QPoint(0, y));
        animation->start(QAbstractAnimation::DeleteWhenStopped);

        button->show();
        button->lower();

        y += button->height();
        y += 5;
        this->setFixedHeight(y);
    }
}

void Right_Click_Menu_Set::Not_On_Card(Anime_Card* anime_card)
{
    this->Reset_Position();
    this->raise();
    this->show();
    this->anime_card = anime_card;

    int y = 0;
    for (auto& button : Not_On_Card_list)
    {
        QPropertyAnimation* animation = new QPropertyAnimation(button, "pos");
        animation->setDuration(200);
        animation->setStartValue(QPoint(0, 0));
        animation->setEndValue(QPoint(0, y));
        animation->start(QAbstractAnimation::DeleteWhenStopped);

        button->show();
        button->lower();

        y += button->height();
        y += 5;
        this->setFixedHeight(y);
    }
}

void Right_Click_Menu_Set::Reset_Position()
{
    if (When_On_Card_list.isEmpty()) return;
    for (auto& button : When_On_Card_list) button->hide();
    this->resize(When_On_Card_list[0]->width(), 0);

    if (Not_On_Card_list.isEmpty()) return;
    for (auto& button : Not_On_Card_list) button->hide();
}
