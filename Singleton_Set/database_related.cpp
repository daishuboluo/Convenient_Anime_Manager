#include "Database_Related.h"
#include <QStandardPaths>
#include <QDebug>

Q_GLOBAL_STATIC(Database_Related, databaseInstance)

Database_Related::Database_Related(QObject* parent)
    : QObject(parent)
{
    QDir dir;
    if (!dir.exists("Database_SQLite") && !dir.mkdir("Database_SQLite")) {
        qCritical() << "无法创建数据库目录!";
        return;
    }
    m_databasePath = "Database_SQLite/Card_Info_Database.db";
    if (!initializeDatabase()) {
        qCritical() << "数据库初始化失败!";
    }
}

Database_Related::~Database_Related()
{
    if (m_database.isOpen()) m_database.close();
}

Database_Related* Database_Related::instance()
{
    return databaseInstance();
}

bool Database_Related::initializeDatabase()
{
    m_database = QSqlDatabase::addDatabase("QSQLITE", "Card_Info_Database.db");
    m_database.setDatabaseName(m_databasePath);

    if (!m_database.open()) {
        qWarning() << "无法打开数据库:" << m_database.lastError().text();
        return false;
    }

    return createTables();
}

bool Database_Related::createTables()
{
    return createImageTable() &&
        createVideoTable() &&
        createComprehensiveTable();
}

bool Database_Related::createImageTable()
{
    QSqlQuery query(m_database);
    QString sql = "CREATE TABLE IF NOT EXISTS images ("
        "id INTEGER PRIMARY KEY, "
        "image_data BLOB NOT NULL)";

    if (!query.exec(sql)) {
        qWarning() << "无法创建图像表:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Database_Related::createVideoTable()
{
    QSqlQuery query(m_database);
    QString sql = "CREATE TABLE IF NOT EXISTS videos ("
        "id INTEGER PRIMARY KEY, "
        "paths TEXT NOT NULL)";

    if (!query.exec(sql)) {
        qWarning() << "无法创建视频表:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Database_Related::createComprehensiveTable()
{
    QSqlQuery query(m_database);
    QString sql = "CREATE TABLE IF NOT EXISTS comprehensive ("
        "id INTEGER PRIMARY KEY, "
        "Location_Data INTEGER, "
        "title TEXT, "
        "year INTEGER, "
        "image_path TEXT, "
        "video_folder TEXT)";

    if (!query.exec(sql)) {
        qWarning() << "无法创建综合表:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Database_Related::insertImage(const QByteArray& imageData, int id)
{
    QSqlQuery query(m_database);
    query.prepare("INSERT OR REPLACE INTO images (id, image_data) VALUES (:id, :image_data)");
    query.bindValue(":id", id);
    query.bindValue(":image_data", imageData);

    if (!query.exec()) {
        qWarning() << "无法插入图像:" << query.lastError().text();
        return false;
    }
    return true;
}

QByteArray Database_Related::getImage(int id)
{
    QSqlQuery query(m_database);
    query.prepare("SELECT image_data FROM images WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec() || !query.next()) {
        qWarning() << "无法获取图像:" << query.lastError().text();
        return QByteArray();
    }

    return query.value(0).toByteArray();
}

bool Database_Related::deleteImage(int id)
{
    QSqlQuery query(m_database);
    query.prepare("DELETE FROM images WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qWarning() << "无法删除图像:" << query.lastError().text();
        return false;
    }
    return true;
}

QList<int> Database_Related::getAllImageIds()
{
    QList<int> ids;
    QSqlQuery query(m_database);
    query.prepare("SELECT id FROM images");

    if (!query.exec()) {
        qWarning() << "无法获取图像ID:" << query.lastError().text();
        return ids;
    }

    while (query.next()) {
        ids.append(query.value(0).toInt());
    }

    return ids;
}

bool Database_Related::imageExists(int id)
{
    QSqlQuery query(m_database);
    query.prepare("SELECT 1 FROM images WHERE id = :id LIMIT 1");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qWarning() << "检查图片ID是否存在失败:" << query.lastError().text();
        return false;
    }

    return query.next();
}

bool Database_Related::insertVideo(const QStringList& paths, int id)
{
    QSqlQuery query(m_database);
    query.prepare("INSERT OR REPLACE INTO videos (id, paths) VALUES (:id, :paths)");
    query.bindValue(":id", id);
    query.bindValue(":paths", QString(QJsonDocument(QJsonArray::fromStringList(paths)).toJson()));

    if (!query.exec()) {
        qWarning() << "无法插入视频:" << query.lastError().text();
        return false;
    }
    return true;
}

QStringList Database_Related::getVideo(int id)
{
    QSqlQuery query(m_database);
    query.prepare("SELECT paths FROM videos WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec() || !query.next()) {
        qWarning() << "无法获取视频:" << query.lastError().text();
        return QStringList();
    }

    QJsonDocument doc = QJsonDocument::fromJson(query.value(0).toString().toUtf8());
    if (!doc.isArray()) {
        qWarning() << "视频表中的JSON格式无效";
        return QStringList();
    }

    QStringList paths;
    QJsonArray array = doc.array();
    for (const QJsonValue& value : array) {
        if (value.isString()) {
            paths.append(value.toString());
        }
    }
    return paths;
}

bool Database_Related::deleteVideo(int id)
{
    QSqlQuery query(m_database);
    query.prepare("DELETE FROM videos WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qWarning() << "无法删除视频:" << query.lastError().text();
        return false;
    }

    return true;
}

bool Database_Related::videoExists(int id)
{
    QSqlQuery query(m_database);
    query.prepare("SELECT 1 FROM videos WHERE id = :id LIMIT 1");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qWarning() << "检查视频ID是否存在失败:" << query.lastError().text();
        return false;
    }

    return query.next();
}

bool Database_Related::insertComprehensive(const QString& title,
    int year,
    const QString& imagePath,
    const QString& videoFolder,
    int Location_Data,
    int id)
{
    QSqlQuery query(m_database);
    query.prepare("INSERT OR REPLACE INTO comprehensive "
        "(id, Location_Data, title, year, image_path, video_folder) "
        "VALUES (:id, :Location_Data, :title, :year, :image_path, :video_folder)");
    query.bindValue(":id", id);
    query.bindValue(":Location_Data", Location_Data);
    query.bindValue(":title", title);
    query.bindValue(":year", year);
    query.bindValue(":image_path", imagePath);
    query.bindValue(":video_folder", videoFolder);

    if (!query.exec()) {
        qWarning() << "无法插入综合数据:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Database_Related::Insert_Comprehensive_At_Specific_Position(const QString& title,
    int year,
    const QString& imagePath,
    const QString& videoFolder,
    int Location_Data,
    int id,
    bool Before_After_Status)
{
    m_database.transaction();

    try {
        if (comprehensiveExists(id)) {
            qWarning() << "ID已存在，无法插入";
            m_database.rollback();
            return false;
        }

        int newLocation = Before_After_Status ? Location_Data : Location_Data + 1;

        QSqlQuery updateQuery(m_database);
        updateQuery.prepare("UPDATE comprehensive SET Location_Data = Location_Data + 1 "
            "WHERE Location_Data >= :newLocation");
        updateQuery.bindValue(":newLocation", newLocation);

        if (!updateQuery.exec()) {
            qWarning() << "更新位置信息失败:" << updateQuery.lastError().text();
            m_database.rollback();
            return false;
        }

        QSqlQuery insertQuery(m_database);
        insertQuery.prepare("INSERT INTO comprehensive "
            "(id, Location_Data, title, year, image_path, video_folder) "
            "VALUES (:id, :Location_Data, :title, :year, :image_path, :video_folder)");
        insertQuery.bindValue(":id", id);
        insertQuery.bindValue(":Location_Data", newLocation);
        insertQuery.bindValue(":title", title);
        insertQuery.bindValue(":year", year);
        insertQuery.bindValue(":image_path", imagePath);
        insertQuery.bindValue(":video_folder", videoFolder);

        if (!insertQuery.exec()) {
            qWarning() << "插入新记录失败:" << insertQuery.lastError().text();
            m_database.rollback();
            return false;
        }

        m_database.commit();
        return true;

    }
    catch (...) {
        m_database.rollback();
        qWarning() << "插入过程中发生异常";
        return false;
    }
}

QVariantMap Database_Related::getComprehensive(int id)
{
    QVariantMap result;
    QSqlQuery query(m_database);
    query.prepare("SELECT title, year, image_path, video_folder, Location_Data FROM comprehensive WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec() || !query.next()) {
        qWarning() << "无法获取综合数据:" << query.lastError().text();
        return result;
    }

    result["title"] = query.value(0).toString();
    result["year"] = query.value(1).toInt();
    result["image_path"] = query.value(2).toString();
    result["video_folder"] = query.value(3).toString();
    result["Location_Data"] = query.value(4).toInt();

    return result;
}

bool Database_Related::deleteComprehensive(int id)
{
    m_database.transaction();

    try {
        QSqlQuery getLocationQuery(m_database);
        getLocationQuery.prepare("SELECT Location_Data FROM comprehensive WHERE id = :id");
        getLocationQuery.bindValue(":id", id);

        if (!getLocationQuery.exec() || !getLocationQuery.next()) {
            qWarning() << "无法找到要删除的记录:" << getLocationQuery.lastError().text();
            m_database.rollback();
            return false;
        }

        int deletedLocation = getLocationQuery.value(0).toInt();

        QSqlQuery deleteQuery(m_database);
        deleteQuery.prepare("DELETE FROM comprehensive WHERE id = :id");
        deleteQuery.bindValue(":id", id);

        if (!deleteQuery.exec()) {
            qWarning() << "删除记录失败:" << deleteQuery.lastError().text();
            m_database.rollback();
            return false;
        }

        QSqlQuery updateQuery(m_database);
        updateQuery.prepare("UPDATE comprehensive SET Location_Data = Location_Data - 1 "
            "WHERE Location_Data > :deletedLocation");
        updateQuery.bindValue(":deletedLocation", deletedLocation);

        if (!updateQuery.exec()) {
            qWarning() << "更新位置信息失败:" << updateQuery.lastError().text();
            m_database.rollback();
            return false;
        }

        m_database.commit();
        return true;

    }
    catch (...) {
        m_database.rollback();
        qWarning() << "删除过程中发生异常";
        return false;
    }
}

QList<int> Database_Related::getAllComprehensiveIds()
{
    QList<int> ids;
    QSqlQuery query(m_database);
    query.prepare("SELECT id FROM comprehensive");
    m_database.transaction();

    if (!query.exec()) {
        qWarning() << "无法获取综合数据的ID:" << query.lastError().text();
        return ids;
    }

    while (query.next()) {
        ids.append(query.value(0).toInt());
    }

    return ids;
}

QList<int> Database_Related::getAllComprehensiveIdsOrderedByLocation()
{
    QList<int> ids;
    QSqlQuery query(m_database);
    query.prepare("SELECT id FROM comprehensive ORDER BY Location_Data ASC");

    if (!query.exec()) {
        qWarning() << "无法获取按位置排序的综合数据ID:" << query.lastError().text();
        return ids;
    }

    while (query.next()) {
        ids.append(query.value(0).toInt());
    }

    return ids;
}

bool Database_Related::comprehensiveExists(int id)
{
    QSqlQuery query(m_database);
    query.prepare("SELECT 1 FROM comprehensive WHERE id = :id LIMIT 1");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qWarning() << "检查综合记录ID是否存在失败:" << query.lastError().text();
        return false;
    }

    return query.next();
}
