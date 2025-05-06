#include "show_all.h"

Show_All::Show_All(QWidget* parent)
    : QPushButton(parent)
{
    this->setCursor(Qt::PointingHandCursor);
    this->setFixedSize(100, 59);
    Button_name = "全部";

    connect(RELAY_SIGNALS, &Central_Bundle_Bridge::Set_Button_ColorVisible, this, [this] {
        set_isClicked(false);
        });
    connect(this, &Show_All::button_clicked, RELAY_SIGNALS, &Central_Bundle_Bridge::Show_All_Buttons);
}

void Show_All::Get_Button_Number()
{
    m_but_w = this->height() * 1.69;
    but_h = this->height() * 0.80;
}

void Show_All::resizeEvent(QResizeEvent* event)
{
    Get_Button_Number();
}

void Show_All::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(Qt::NoPen);

    QFont font;
    font.setPixelSize(this->height() / 4);
    font.setBold(true);
    painter.setFont(font);

    if (m_isClicked)
    {
        painter.setBrush(QColor(255, 65, 129, 255));
    }
    else
    {
        painter.setBrush(QColor(255, 255, 255, 255));
    }
    painter.drawRoundedRect(0, 0, m_but_w, but_h, 10, 10);

    painter.setPen(m_isClicked ? QColor(255, 255, 255, 255) : QColor(0, 0, 0, 255));
    painter.drawText(0, 0, m_but_w, but_h, Qt::AlignCenter, Button_name);
}

void Show_All::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (isClicked())
        {
            setIsClicked(true);
        }
        else
        {
            setIsClicked(true);
            emit button_clicked();
        }
    }
}

bool Show_All::isClicked() const
{
    return m_isClicked;
}

void Show_All::setIsClicked(bool isClicked)
{
    m_isClicked = isClicked;
    update();
}

void Show_All::set_isClicked(bool isClicked)
{
    m_isClicked = isClicked;
    update();
}
