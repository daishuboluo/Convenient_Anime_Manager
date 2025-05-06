#ifndef ANIME_CARD_H
#define ANIME_CARD_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QEvent>
#include <QMouseEvent>


#include <QPropertyanimation.h>
#include <QGraphicsDropShadowEffect>
#include "../Singleton_Set/central_bundle_bridge.h"
#include "../Singleton_Set/status_group.h"  


class Anime_Card : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString cardYear READ cardYear WRITE setCardYear  FINAL)
    Q_PROPERTY(qreal Zoom_Ratio READ Zoom_Ratio WRITE setZoom_Ratio  FINAL)
    Q_PROPERTY(QColor text_color READ text_color WRITE setText_color  FINAL)
    Q_PROPERTY(QColor Grey_Barrier READ Grey_Barrier WRITE setGrey_Barrier  FINAL)
    Q_PROPERTY(QColor Circle_Color READ Circle_Color WRITE setCircle_Color   FINAL)
    Q_PROPERTY(QColor Triangle_Color READ Triangle_Color WRITE setTriangle_Color   FINAL)
    Q_PROPERTY(bool Type_Is_Visible READ Type_Is_Visible WRITE setType_Is_Visible   FINAL)
    Q_PROPERTY(int Card_ID READ Card_ID WRITE setCard_ID   FINAL)
    Q_PROPERTY(QImage Card_Image READ Card_Image WRITE setCard_Image   FINAL)
    Q_PROPERTY(QString Theme_Text READ Theme_Text WRITE setTheme_Text   FINAL)
    Q_PROPERTY(QString Card_Link_Address READ Card_Link_Address WRITE setCard_Link_Address   FINAL)
    Q_PROPERTY(QString Video_Folder READ Video_Folder WRITE setVideo_Folder   FINAL)
    Q_PROPERTY(QList<QString> Video_Path_List READ Video_Path_List WRITE setVideo_Path_List   FINAL)







public:
    explicit Anime_Card(QWidget *parent = nullptr);


    void animation_start();
    QPropertyAnimation* animation;
    QPropertyAnimation* animation2;
    QPropertyAnimation* animation3;
    QPropertyAnimation* animation4;
    QPropertyAnimation* animation5;
    int Animation_Time = 300;
    void Execute_Animation();
    void Reset_Animation();


    void Draw_Image();            // 绘制图片
    void Draw_Theme_Text();       // 绘制主题文字
    void Draw_Rounded_Triangle(); // 绘制圆角三角形
    void Draw_Circle();           // 绘制圆
    void Update_Card();          // 更新卡片


public:

    QString cardYear() const;
    void setCardYear(const QString &newCardYear);

    qreal Zoom_Ratio() const;
    void setZoom_Ratio(qreal newZoom_Ratio);

    QColor text_color() const;
    void setText_color(const QColor &newText_color);

    QColor Grey_Barrier() const;
    void setGrey_Barrier(const QColor &newGrey_Barrier);

    QColor Circle_Color() const;
    void setCircle_Color(const QColor &newCircle_Color);

    QColor Triangle_Color() const;
    void setTriangle_Color(const QColor &newTriangle_Color);

    bool Type_Is_Visible() const;
    void setType_Is_Visible(bool newType_Is_Visible);

    int Card_ID() const;
    void setCard_ID(int newCard_ID);

    QImage Card_Image() const; 
    void setCard_Image(const QImage &newCard_Image);

    QString Theme_Text() const; // 卡片标题
    void setTheme_Text(const QString &newTheme_Text);

    QString Card_Link_Address() const;
    void setCard_Link_Address(const QString &newCard_Link_Address);

    QString Video_Folder() const;
    void setVideo_Folder(const QString &newVideo_Folder);



    QList<QString> Video_Path_List() const;
    void setVideo_Path_List(const QList<QString> &newVideo_Path_List);


protected:
    void paintEvent(QPaintEvent* event) override;               // 绘制事件
    bool event(QEvent* event) override;                     // 事件

    void mousePressEvent(QMouseEvent *event) override;       // 鼠标点击事件
    void mouseReleaseEvent(QMouseEvent *event) override;     // 鼠标释放事件



signals:
    //发射视频地址和字幕地址
    void Video_URL_And_Subtitle_URL_In_Card(QList<QString> m_Video_Path_List);
    //被点击了
    void Card_Clicked();
    //发射主题和年份
    void Theme_And_Year_In_Card(QString m_Theme_Text, QString m_cardYear);



private:
    int m_Card_ID;                //卡片ID
    QString m_Theme_Text;         // 卡片标题
    QImage m_Card_Image;         // 卡片图片
    QString m_Card_Link_Address;  // 卡片图片链接地址
    QString m_Video_Folder;       // 视频文件夹地址
    QString m_cardYear;                // 卡片年份

    QList<QString> m_Video_Path_List;// 视频文件地址列表

    bool m_Type_Is_Visible = true;      //是否可视




    QList<QString> Video_Address_List; // 圆角三角形
    qreal m_Zoom_Ratio = 1.00;         // 放大比例
    QColor m_text_color = QColor(0, 0, 0, 255);
    QColor m_Grey_Barrier = QColor(0, 0, 0, 0);
    QColor m_Circle_Color = QColor(0, 0, 0, 0);
    QColor m_Triangle_Color = QColor(0, 0, 0, 0);
 

};

#endif // ANIME_CARD_H
