#ifndef ANIME_MANAGEMENT_HOMEPAGE_H
#define ANIME_MANAGEMENT_HOMEPAGE_H

#include <QWidget>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QPainterPath>
#include <QSizeGrip>
#include <QStatusBar>

#include "Horizontal_Navigation_Page/horizontal_navigation_page.h"
#include "Cards_Page/cards_page.h"
#include "Playback_Page/playback_page.h"
#include "Singleton_Set/status_group.h"
#include "Horizontal_Navigation_Page/show_all.h"
#include "Left_Window_Tip_Area/left_window_tip.h"

class Anime_Management_Homepage : public QWidget {
    Q_OBJECT
        Q_PROPERTY(qreal Current_Position_Ratio READ Current_Position_Ratio WRITE setCurrent_Position_Ratio FINAL)

public:
    explicit Anime_Management_Homepage(QWidget* parent = nullptr);
    ~Anime_Management_Homepage();

    Horizontal_Navigation_Page* Navigation_Page;
    Cards_Page* cards_page;
    Playback_Page* Play_Page;
    Show_All* show_all;
    Left_Window_Tip* left_window_tip;

    QPropertyAnimation* m_animation;
    QPropertyAnimation* m_animation_size;

    void updateMask();
    void updateCursorShape(const QPoint& pos);
    void handleWindowResize(const QPoint& globalMousePos);

    qreal Current_Position_Ratio() const;
    void setCurrent_Position_Ratio(qreal newCurrent_Position_Ratio);

public slots:
    void Switch_Page();
    void Window_Size_Plus_Minus();
    void Window_Minimize();
    void Window_Maximize();
    void Window_Close();


protected:
    void resizeEvent(QResizeEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    bool eventFilter(QObject* watched, QEvent* event) override;

private:
    QPoint m_startWindowPosition;
    bool m_isDragging = false;
    QPoint m_dragStartPosition;

    bool m_bPressed = false;
    bool m_bDragWindow = false;
    bool m_bDragTop = false;
    bool m_bDragLeft = false;
    bool m_bDragRight = false;
    bool m_bDragBottom = false;

    QPoint m_ptPress;
    QPoint m_ptDrag;
    QSize m_originalSize;

    int m_borderWidth = 20;
    qreal m_Current_Position_Ratio = 1.0;
};

#endif // ANIME_MANAGEMENT_HOMEPAGE_H
