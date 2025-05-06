#ifndef CENTRAL_BUNDLE_BRIDGE_H
#define CENTRAL_BUNDLE_BRIDGE_H

#include <QObject>

#define RELAY_SIGNALS Central_Bundle_Bridge::instance()

class Central_Bundle_Bridge : public QObject
{
    Q_OBJECT
public:
    explicit Central_Bundle_Bridge(QObject* parent = nullptr);
    static Central_Bundle_Bridge* instance();

signals:
    void File_URLs(QList<QString> m_Video_Path_List);
    void Send_Playback_videoPath_Path_Info(QString m_Video_Path);
    void Enter_Playback_Page();
    void Exit_Playback_Page();
    void Forward_Card_Theme_And_Year_Info(QString m_Theme, QString m_Year);
    void Button_Collection_Arrangement(int episode_num);
    void Send_Y_Axis(int y_axis);
    void Forward_Full_Screen();
    void Re_Adjust_Window_Size();
    void Forward_Self_Button_Name(QString button_name);
    void Show_All_Buttons();
    void Set_Button_ColorVisible();
    void Forward_Reset_Playback_Window();
    void Episode_Jump(int episode_num);

private:
    Q_DISABLE_COPY_MOVE(Central_Bundle_Bridge)
};

#endif // CENTRAL_BUNDLE_BRIDGE_H
