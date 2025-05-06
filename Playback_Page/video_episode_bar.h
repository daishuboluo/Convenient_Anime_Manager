#ifndef VIDEO_EPISODE_BAR_H
#define VIDEO_EPISODE_BAR_H

#include <QWidget>
#include <QPainter>
#include "./Video_Components/episode_button.h"
#include "../Singleton_Set/central_bundle_bridge.h"
#include "../Singleton_Set/status_group.h"
#include "../Cards_Page/Ratio_Slider.h"

class Video_Episode_Bar : public QWidget
{
    Q_OBJECT

public:
    explicit Video_Episode_Bar(QWidget* parent = nullptr);
    void Set_Episode_Button_Position();

signals:

public slots:
    void Set_Episode(QList<QString> m_Video_Path_List);
    void Set_Episode_Button_Status(int episode_num);
    void Set_Button_Position(int button_num);
    void Set_Play_Position(int position);

private:
    QList<Episode_Button*> episode_list;
    qreal episode_button_width_ratio = 0.27;
    qreal episode_button_height_ratio = 0.16;
    int episode_button_height_sum = 0;
    int button_move_step = 0;
};

#endif // VIDEO_EPISODE_BAR_H
