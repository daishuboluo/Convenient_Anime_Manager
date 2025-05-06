#include "status_group.h"


Q_GLOBAL_STATIC(Status_Group, fileRelatedInstance)  


Status_Group::Status_Group(QObject *parent) : QObject{parent} {}


Status_Group* Status_Group::instance() 
{
    return fileRelatedInstance; 
}


bool Status_Group::Is_Accepting_Create_Episodes() const
{
    return m_Is_Accepting_Create_Episodes;
}

void Status_Group::setIs_Accepting_Create_Episodes(bool newIs_Accepting_Create_Episodes)
{
    m_Is_Accepting_Create_Episodes = newIs_Accepting_Create_Episodes;
}

bool Status_Group::Is_Accepting_Anime_Info() const
{
    return m_Is_Accepting_Anime_Info;
}

void Status_Group::setIs_Accepting_Anime_Info(bool newIs_Accepting_Anime_Info)
{
    m_Is_Accepting_Anime_Info = newIs_Accepting_Anime_Info;
}

bool Status_Group::Is_Video_Playback_Status() const
{
    return m_Is_Video_Playback_Status;
}

void Status_Group::setIs_Video_Playback_Status(bool newIs_Video_Playback_Status)
{
    m_Is_Video_Playback_Status = newIs_Video_Playback_Status;
}

bool Status_Group::Window_Dragging_Status() const
{
    return m_Window_Dragging_Status;
}

void Status_Group::setWindow_Dragging_Status(bool newWindow_Dragging_Status)
{
    m_Window_Dragging_Status = newWindow_Dragging_Status;
}
