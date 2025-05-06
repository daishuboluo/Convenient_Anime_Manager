#include "video_episode_bar.h"

Video_Episode_Bar::Video_Episode_Bar(QWidget* parent)
    : QWidget{ parent }
{
    this->setFixedWidth(250);
    connect(RELAY_SIGNALS, &Central_Bundle_Bridge::File_URLs, this, &Video_Episode_Bar::Set_Episode);
    connect(RELAY_SIGNALS, &Central_Bundle_Bridge::Button_Collection_Arrangement, this, &Video_Episode_Bar::Set_Episode_Button_Status);
    connect(RELAY_SIGNALS, &Central_Bundle_Bridge::Episode_Jump, this, &Video_Episode_Bar::Set_Play_Position);
}

void Video_Episode_Bar::Set_Button_Position(int button_num)
{
    if (episode_button_height_sum < this->height()) return;
    button_move_step = -button_num;

    int button_height = episode_button_height_ratio * this->width();
    int but_K = this->width() / 10;
    int y = 0;

    for (int i = 0; i < episode_list.size(); i++)
    {
        int m = i % 3 * 2 + 1;
        episode_list[i]->move(episode_list[i]->pos().x(), button_height * y + but_K * (y + 1) + button_move_step);
        qDebug() << "第" << i << "个按钮的位置和宽高为：" << episode_list[i]->geometry();

        if (i % 3 == 2) y += 1;
    }
}

void Video_Episode_Bar::Set_Play_Position(int position)
{
    for (int i = 0; i < episode_list.size(); i++)
    {
        if (episode_list[i]->doubleClicked() == true)
        {
            if (i + position > episode_list.size() - 1)
            {
                episode_list[0]->Send_videoPath_Playback_Path_Info();
                return;
            }
            else if (i + position < 0)
            {
                episode_list[episode_list.size() - 1]->Send_videoPath_Playback_Path_Info();
                return;
            }
            episode_list[i + position]->Send_videoPath_Playback_Path_Info();
            return;
        }
    }
}

void Video_Episode_Bar::Set_Episode(QList<QString> m_Video_Path_List)
{
    if (!STATUS_GROUPS->Is_Accepting_Create_Episodes()) return;
    STATUS_GROUPS->setIs_Accepting_Create_Episodes(false);

    for (int i = 0; i < episode_list.size(); i++)
    {
        delete episode_list[i];
    }
    episode_list.clear();

    for (int i = 0; i < m_Video_Path_List.size(); i++)
    {
        qDebug() << "  m_Video_Path_List();  " << m_Video_Path_List[i];
        Episode_Button* episode_button = new Episode_Button(QString("第%1集").arg(i + 1), this);
        episode_button->setVideoPath(m_Video_Path_List[i]);
        episode_button->show();
        episode_list.append(episode_button);
    }

    this->Set_Episode_Button_Position();
}

void Video_Episode_Bar::Set_Episode_Button_Position()
{
    int button_width = episode_button_width_ratio * this->width();
    int button_height = episode_button_height_ratio * this->width();
    int but_x = this->width() / 6;
    int but_K = this->width() / 10;
    int y = 0;

    for (int i = 0; i < episode_list.size(); i++)
    {
        int m = i % 3 * 2 + 1;
        episode_list[i]->setGeometry(but_x * m - button_width / 2, button_height * y + but_K * (y + 1), button_width, button_height);
        episode_list[i]->setButton_ID(i);
        qDebug() << "第" << i << "个按钮的位置和宽高为：" << episode_list[i]->geometry();

        if (i % 3 == 2) y += 1;
    }
    this->episode_button_height_sum = y * button_height + (y - 1) * but_K + button_height;
    this->setFixedHeight(this->episode_button_height_sum);
}

void Video_Episode_Bar::Set_Episode_Button_Status(int episode_num)
{
    for (int i = 0; i < episode_list.size(); i++)
    {
        if (episode_list[i]->Button_ID() == episode_num)
        {
            episode_list[i]->setDoubleClicked(true);
        }
        else
        {
            episode_list[i]->setDoubleClicked(false);
        }
    }
}
