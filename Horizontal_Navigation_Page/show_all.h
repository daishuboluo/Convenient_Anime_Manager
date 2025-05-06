#ifndef SHOW_ALL_H
#define SHOW_ALL_H

#include <QPushButton>
#include <QPainter>
#include <QMouseEvent>
#include "../Singleton_Set/central_bundle_bridge.h"

class Show_All : public QPushButton
{
    Q_OBJECT
        Q_PROPERTY(bool isClicked READ isClicked WRITE setIsClicked)

public:
    explicit Show_All(QWidget* parent = nullptr);
    void Get_Button_Number();
    bool isClicked() const;
    void setIsClicked(bool isClicked);

public slots:
    void set_isClicked(bool isClicked);

signals:
    void button_clicked();

protected:
    void resizeEvent(QResizeEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

private:
    int but_h;
    int m_but_w;
    bool m_isClicked = true;
    QString Button_name;
};

#endif // SHOW_ALL_H
