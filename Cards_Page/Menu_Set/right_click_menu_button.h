#ifndef RIGHT_CLICK_MENU_BUTTON_H
#define RIGHT_CLICK_MENU_BUTTON_H

#include <QPushButton>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QPainterPath>
#include <QPainter>
#include <QEvent>
#include "../../Singleton_Set/image_processing.h"

class Right_Click_Menu_Button : public QPushButton
{
    Q_OBJECT
        Q_PROPERTY(QColor Background_Color READ Background_Color WRITE setBackground_Color FINAL)

public:
    explicit Right_Click_Menu_Button(QPixmap m_image, QString m_text, QWidget* parent = nullptr);
    void Draw_Image();
    void Draw_Theme_Text();
    void Draw_Shadow();
    void animation_start();
    QPropertyAnimation* Animation;

public:
    QColor Background_Color() const;
    void setBackground_Color(const QColor& newBackground_Color);

protected:
    void paintEvent(QPaintEvent* event) override;
    bool event(QEvent* event) override;

signals:
    void Clicked();

private:
    QPixmap m_image;
    QString m_text;
    QColor m_Background_Color = QColor(255, 255, 255, 255);
};

#endif // RIGHT_CLICK_MENU_BUTTON_H
