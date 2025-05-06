#ifndef STATUS_GROUP_H
#define STATUS_GROUP_H

#include <QObject>

#define STATUS_GROUPS Status_Group::instance()

class Status_Group : public QObject {
    Q_OBJECT
        Q_PROPERTY(bool Is_Accepting_Create_Episodes READ Is_Accepting_Create_Episodes WRITE setIs_Accepting_Create_Episodes FINAL)
        Q_PROPERTY(bool Is_Accepting_Anime_Info READ Is_Accepting_Anime_Info WRITE setIs_Accepting_Anime_Info FINAL)
        Q_PROPERTY(bool Is_Video_Playback_Status READ Is_Video_Playback_Status WRITE setIs_Video_Playback_Status FINAL)
        Q_PROPERTY(bool Window_Dragging_Status READ Window_Dragging_Status WRITE setWindow_Dragging_Status FINAL)

public:
    explicit Status_Group(QObject* parent = nullptr);
    static Status_Group* instance();

    bool Is_Accepting_Create_Episodes() const;
    void setIs_Accepting_Create_Episodes(bool newIs_Accepting_Create_Episodes);

    bool Is_Accepting_Anime_Info() const;
    void setIs_Accepting_Anime_Info(bool newIs_Accepting_Anime_Info);

    bool Is_Video_Playback_Status() const;
    void setIs_Video_Playback_Status(bool newIs_Video_Playback_Status);

    bool Window_Dragging_Status() const;
    void setWindow_Dragging_Status(bool newWindow_Dragging_Status);

private:
    Q_DISABLE_COPY_MOVE(Status_Group)

    bool m_Is_Accepting_Create_Episodes = true;
    bool m_Is_Accepting_Anime_Info = true;
    bool m_Is_Video_Playback_Status = false;
    bool m_Window_Dragging_Status = false;
};

#endif // STATUS_GROUP_H
