#ifndef DATABASE_RELATED_H
#define DATABASE_RELATED_H

#include <QObject>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDir>
#include <QSqlError>
#include <QJsonArray>
#include <QJsonDocument>

#define DATABASE_RELATEDS Database_Related::instance()

class Database_Related : public QObject
{
    Q_OBJECT

public:
    explicit Database_Related(QObject* parent = nullptr);
    ~Database_Related();

public:
    static Database_Related* instance();
    bool initializeDatabase();
    bool createTables();

    bool insertImage(const QByteArray& imageData, int id);
    QByteArray getImage(int id);
    bool deleteImage(int id);
    QList<int> getAllImageIds();
    bool imageExists(int id);

    bool insertVideo(const QStringList& paths, int id);
    QStringList getVideo(int id);
    bool deleteVideo(int id);
    bool videoExists(int id);

    bool insertComprehensive(const QString& title,
        int year,
        const QString& imagePath,
        const QString& videoFolder,
        int Location_Data,
        int id);
    bool Insert_Comprehensive_At_Specific_Position(const QString& title,
        int year,
        const QString& imagePath,
        const QString& videoFolder,
        int Location_Data,
        int id,
        bool Before_After_Status = true);
    QVariantMap getComprehensive(int id);
    bool deleteComprehensive(int id);
    QList<int> getAllComprehensiveIds();
    QList<int> getAllComprehensiveIdsOrderedByLocation();
    bool comprehensiveExists(int id);

private:
    QSqlDatabase m_database;
    QString m_databasePath;
    Q_DISABLE_COPY_MOVE(Database_Related)

        bool createImageTable();
    bool createVideoTable();
    bool createComprehensiveTable();
};

#endif // DATABASE_RELATED_H
