#ifndef TIME_BUTTON_MODULE_H
#define TIME_BUTTON_MODULE_H

#include <QWidget>
#include <QPainterPath>
#include <QPainter>
#include <QPushButton>
#include <QEvent>
#include <QPropertyAnimation>

class Time_Button_Module : public QPushButton
{
    Q_OBJECT
        Q_PROPERTY(QColor Button_Color READ Button_Color WRITE setButton_Color FINAL)
        Q_PROPERTY(QString Button_Text READ Button_Text WRITE setButton_Text FINAL)
        Q_PROPERTY(QColor Button_Text_Color READ Button_Text_Color WRITE setButton_Text_Color FINAL)

public:
    explicit Time_Button_Module(QWidget* parent = nullptr);
    QPropertyAnimation* animation;
    QPropertyAnimation* animation2;
    QPropertyAnimation* animation3;

    QColor Button_Color() const;
    void setButton_Color(const QColor& newButton_Color);
    QString Button_Text() const;
    void setButton_Text(const QString& newButton_Text);
    QColor Button_Text_Color() const;
    void setButton_Text_Color(const QColor& newButton_Text_Color);

protected:
    void paintEvent(QPaintEvent* event) override;
    bool event(QEvent* event) override;

signals:
    void emitButton_Text(QString text);
    void clicked_A();

private:
    QColor m_Button_Color = QColor(255, 255, 255, 0);
    QString m_Button_Text;
    QColor m_Button_Text_Color = QColor(0, 0, 0, 255);
};

#endif // TIME_BUTTON_MODULE_H
