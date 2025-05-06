#ifndef CONTROL_AREA_H
#define CONTROL_AREA_H

#include <QWidget>
#include "progress_bar.h"
#include "control_button.h"
#include "playback_status_button.h"
#include "../../Singleton_Set/central_bundle_bridge.h"

class Control_Area : public QWidget
{
    Q_OBJECT
public:
    explicit Control_Area(QWidget* parent = nullptr);

public:
    Progress_Bar* progress_bar;
    Progress_Bar* volume_bar;
    Playback_Status_Button* playback_status_button;
    Playback_Status_Button* mute_button;
    Playback_Status_Button* full_screen_button;
    Control_Button* next_button;
    Control_Button* previous_button;

signals:

protected:
    void resizeEvent(QResizeEvent* event) override;

private:

};

#endif // CONTROL_AREA_H
