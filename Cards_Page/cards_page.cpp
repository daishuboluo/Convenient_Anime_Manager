#include "cards_page.h"

Cards_Page::Cards_Page(QWidget* parent)
    : QWidget{ parent }
{
    manager = new CardLayoutManager(this);
    QList<int> Ids = DATABASE_RELATEDS->getAllComprehensiveIdsOrderedByLocation();

    for (auto& id : Ids)
    {
        Anime_Card* card = new Anime_Card(manager);
        QVariantMap data = DATABASE_RELATEDS->getComprehensive(id);

        card->setCard_ID(id);
        card->setTheme_Text(data["title"].toString());
        card->setCard_Link_Address(data["image_path"].toString());
        card->setVideo_Folder(data["video_folder"].toString());
        card->setCardYear(QString::number(data["year"].toInt()));
        card->setCard_Image(QImage::fromData(DATABASE_RELATEDS->getImage(id)));
        card->setVideo_Path_List(DATABASE_RELATEDS->getVideo(id));

        manager->addCard(card);
    }

    scroll_area = new Ratio_Slider(this);
    scroll_area->setWidget(manager);
    scroll_area->setWidgetResizable(true);
}

void Cards_Page::resizeEvent(QResizeEvent* event)
{
    scroll_area->resize(event->size());
    QWidget::resizeEvent(event);
}
