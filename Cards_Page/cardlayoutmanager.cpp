#include "cardlayoutmanager.h"

CardLayoutManager::CardLayoutManager(QWidget* parent)
    : QWidget(parent)
{
    right_click_menu_set = new Right_Click_Menu_Set(this);
    right_click_menu_set->hide();

    connect(right_click_menu_set, &Right_Click_Menu_Set::Card_Deleted_Signal, this, &CardLayoutManager::Delete_Card);
    connect(right_click_menu_set, &Right_Click_Menu_Set::Card_New_Signal, this, &CardLayoutManager::Create_Menu);
    connect(right_click_menu_set, &Right_Click_Menu_Set::Card_Edit_Signal, this, &CardLayoutManager::Edit_Card);
    connect(RELAY_SIGNALS, &Central_Bundle_Bridge::Send_Y_Axis, this, &CardLayoutManager::Set_Current_Visible_Y_Coordinate);
    connect(RELAY_SIGNALS, &Central_Bundle_Bridge::Forward_Self_Button_Name, this, &CardLayoutManager::filterByYear);
    connect(RELAY_SIGNALS, &Central_Bundle_Bridge::Show_All_Buttons, this, &CardLayoutManager::showAllCards);
}

void CardLayoutManager::addCard(Anime_Card* card)
{
    m_cards.append(card);
    this->Update_Layout_Slot_Function();
}

void CardLayoutManager::setAnimationDuration(int duration)
{
    m_animationDuration = duration;
}

void CardLayoutManager::filterByYear(const QString year)
{
    for (auto& card : m_cards)
    {
        card->setType_Is_Visible(card->cardYear() == year);
    }
    this->Update_Layout_Slot_Function();
}

void CardLayoutManager::showAllCards()
{
    for (auto& card : m_cards)
        card->setType_Is_Visible(true);
    this->Update_Layout_Slot_Function();
}

void CardLayoutManager::Update_Layout_Slot_Function()
{
    this->Basic_Parameters();
    this->updateLayout();
}

void CardLayoutManager::Delete_Card(Anime_Card* anime_card)
{
    for (int i = 0; i < m_cards.size(); i++)
    {
        if (!m_cards[i]->isVisible()) continue;

        if (m_cards[i] == anime_card)
        {
            DATABASE_RELATEDS->deleteComprehensive(m_cards[i]->Card_ID());
            DATABASE_RELATEDS->deleteVideo(m_cards[i]->Card_ID());
            DATABASE_RELATEDS->deleteImage(m_cards[i]->Card_ID());

            delete m_cards[i];
            m_cards.remove(i);
            this->Update_Layout_Slot_Function();
            return;
        }
    }
}

void CardLayoutManager::Create_Menu(int id)
{
    if (Menu != nullptr) return;

    Menu = new New_Menu_Set();
    Menu->setWindowFlags(Qt::Drawer);
    int x = 0;
    for (auto& card : m_cards)
    {
        if (card->Card_ID() > x) x = card->Card_ID();
    }
    x += 1;
    Menu->setId(x);
    Menu->setAnime_card(id);
    Menu->input_box5->setText(QString::number(QDateTime::currentDateTime().date().year()));

    connect(Menu, &New_Menu_Set::New_Window_Creation, this, &CardLayoutManager::Add_Card_To_Layout);
    connect(Menu, &New_Menu_Set::Window_Close_Signal, this, [this] {
        delete Menu;
        Menu = nullptr;
        });

    Menu->show();
}

void CardLayoutManager::Add_Card_To_Layout(int Create_Location_Card, Anime_Card* anime_card)
{
    if (Create_Location_Card == -1)
    {
        anime_card->setParent(this);
        this->addCard(anime_card);

        DATABASE_RELATEDS->insertComprehensive(
            anime_card->Theme_Text(),
            anime_card->cardYear().toInt(),
            anime_card->Card_Link_Address(),
            anime_card->Video_Folder(),
            m_cards.length() + 1,
            anime_card->Card_ID()
        );

        this->Update_Layout_Slot_Function();
        return;
    }

    for (int i = 0; i < m_cards.size(); i++)
    {
        if (!m_cards[i]->isVisible()) continue;
        if (m_cards[i]->Card_ID() == Create_Location_Card)
        {
            m_cards.insert(i, anime_card);
            anime_card->setParent(this);

            DATABASE_RELATEDS->Insert_Comprehensive_At_Specific_Position(
                anime_card->Theme_Text(),
                anime_card->cardYear().toInt(),
                anime_card->Card_Link_Address(),
                anime_card->Video_Folder(),
                m_cards.indexOf(m_cards[i]) + 1,
                anime_card->Card_ID()
            );

            this->Update_Layout_Slot_Function();
            return;
        }
    }
}

void CardLayoutManager::Edit_Card(Anime_Card* anime_card)
{
    if (Menu != nullptr) return;
    right_click_menu_set->hide();

    Menu = new New_Menu_Set();
    Menu->Initial_Modification_Value(anime_card);
    Menu->setWindowFlags(Qt::Drawer);

    connect(Menu, &New_Menu_Set::Window_Close_Signal, this, [this] {
        delete Menu;
        Menu = nullptr;
        });

    Menu->show();
}

void CardLayoutManager::Set_Current_Visible_Y_Coordinate(int y_coordinate)
{
    this->current_visible_y_coordinate = y_coordinate;
    this->Update_Layout_Slot_Function();
}

void CardLayoutManager::resizeEvent(QResizeEvent* event)
{
    this->Basic_Parameters();
    this->updateLayout();
    QWidget::resizeEvent(event);
}

void CardLayoutManager::Basic_Parameters()
{
    windowWidth = this->width();
    windowHeight = this->height();
    Max_Card_Value = std::max(windowWidth / cardWidth, 2) - 1;
    Center_Value_Per_Row = windowWidth / (Max_Card_Value * 2);

    normalArea = QRect(0, current_visible_y_coordinate, windowWidth, this->parentWidget()->height());
    extendedArea = normalArea.adjusted(
        0,
        -this->parentWidget()->height(),
        0,
        this->parentWidget()->height()
    );

    int visibleIndex = 0;
    for (auto& card : m_cards)
    {
        if (card->Type_Is_Visible()) visibleIndex++;
    }
    visibleIndex -= 1;
    int row = visibleIndex / Max_Card_Value;
    Total_Height = row * (cardHeight + m_verticalSpacing);

    if (Total_Height + cardHeight + m_verticalSpacing < windowHeight)
    {
        this->setFixedHeight(this->parentWidget()->height());
    }
    else
    {
        this->setFixedHeight(Total_Height + cardHeight + m_verticalSpacing);
    }
}

void CardLayoutManager::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        right_click_menu_set->hide();
    }
    else if (event->button() == Qt::RightButton)
    {
        QPoint pos = event->pos();

        if (Menu != nullptr)
        {
            right_click_menu_set->move(pos);
            right_click_menu_set->Not_On_Card(nullptr);
            return;
        }

        for (auto& card : m_cards)
        {
            if (!card->isVisible()) continue;

            if (card->geometry().contains(pos))
            {
                right_click_menu_set->move(pos);
                right_click_menu_set->When_On_Card(card);
                return;
            }
        }

        for (auto& card : m_cards)
        {
            if (!card->isVisible()) continue;
            if (card->pos().ry() + card->height() > pos.y() && card->pos().rx() + card->width() > pos.x())
            {
                right_click_menu_set->move(pos);
                right_click_menu_set->Not_On_Card(card);
                return;
            }
        }

        right_click_menu_set->move(pos);
        right_click_menu_set->Not_On_Card(nullptr);
    }

    QWidget::mousePressEvent(event);
}

void CardLayoutManager::updateLayout()
{
    if (m_cards.isEmpty()) return;

    int visibleIndex = 0;

    for (auto& card : m_cards)
    {
        if (!card->Type_Is_Visible())
        {
            card->hide();
            continue;
        }
        QPoint targetPos = calculateCardPosition(visibleIndex);
        visibleIndex++;

        if (isInExtendedVisibleArea(targetPos))
        {
            card->show();
            QPropertyAnimation* animation = new QPropertyAnimation(card, "pos");
            animation->setDuration(m_animationDuration);
            animation->setStartValue(card->pos());
            animation->setEndValue(targetPos);
            animation->setEasingCurve(QEasingCurve::BezierSpline);
            animation->start(QAbstractAnimation::DeleteWhenStopped);
        }
        else
        {
            card->hide();
            card->move(targetPos);
        }
    }
}

QPoint CardLayoutManager::calculateCardPosition(int visibleIndex)
{
    if (windowWidth < cardWidth)
    {
        return QPoint(windowWidth / 2 - cardWidth / 2, visibleIndex * cardHeight + m_verticalSpacing);
    }

    const int row = visibleIndex / Max_Card_Value;
    const int col = visibleIndex % Max_Card_Value + 1;

    const int x = (col + col - 1) * Center_Value_Per_Row - cardWidth / 2;
    const int y = row * (cardHeight + m_verticalSpacing);

    return QPoint(x, y);
}

bool CardLayoutManager::isInExtendedVisibleArea(const QPoint& pos)
{
    const QRect cardRect(pos, QSize(cardWidth, cardHeight));
    return extendedArea.intersects(cardRect);
}
