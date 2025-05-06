#ifndef VIDEO_EPISODE_BAR_SHELL_H
#define VIDEO_EPISODE_BAR_SHELL_H

#include <QWidget>
#include "video_episode_bar.h"
#include "../Cards_Page/Ratio_Slider.h"

class Video_Episode_Bar_Shell : public QWidget
{
    Q_OBJECT

public:
    explicit Video_Episode_Bar_Shell(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    Video_Episode_Bar* video_episode_bar;
    Ratio_Slider* ratio_slider;
};

#endif // VIDEO_EPISODE_BAR_SHELL_H
