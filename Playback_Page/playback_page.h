#ifndef PLAYBACK_PAGE_H
#define PLAYBACK_PAGE_H

#include <QWidget>
#include <QPainter>
#include <QtMultimedia>
#include "video_playback_area.h"
#include "video_control_area.h"
#include "video_info_bar.h"
#include "Video_Components/back_button.h"
#include "video_episode_bar_shell.h"

class Playback_Page : public QWidget
{
    Q_OBJECT

public:
    explicit Playback_Page(QWidget* parent = nullptr);

signals:

protected:
    void resizeEvent(QResizeEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
 

private:
    Video_Playback_Area* Main_Video;
    Video_Control_Area* Overlay_Subtitles_And_Controls;
    Video_Playback_Area* Preview_Video;
    Video_Info_Bar* Video_Info;
    QMediaPlayer* player;
    Back_Button* back_button;
    Video_Episode_Bar_Shell* episode_bar_shell;
};

#endif // PLAYBACK_PAGE_H
