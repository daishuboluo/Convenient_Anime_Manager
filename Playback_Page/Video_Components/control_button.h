#ifndef CONTROL_BUTTON_H
#define CONTROL_BUTTON_H

#include <QPushButton>
#include <QPainter>
#include <QPropertyAnimation>
#include <QEvent>
#include <QMouseEvent>

class Control_Button : public QPushButton
{
    Q_OBJECT
        Q_PROPERTY(QColor hover_color READ hover_color WRITE Sethover_color FINAL)

public:
    explicit Control_Button(QString Button_pixmap, QString hover_text, QWidget* parent = nullptr);
    QPropertyAnimation* m_animation;

    QColor hover_color() const;
    void Sethover_color(const QColor& newHover_color);

protected:
    void paintEvent(QPaintEvent* event) override;
    bool event(QEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

signals:
    void Control_Button_clicked();

private:
    QPixmap m_Button_pixmap;
    QString m_hover_text;
    QColor m_hover_color = QColor(255, 255, 255, 0);
};

#endif // CONTROL_BUTTON_H
