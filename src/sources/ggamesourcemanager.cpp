#define GGAMESOURCE_CONFIG_HEADER QStringLiteral("GGameSourceConfig")
#define GGAMESOURCE_CONFIG_VERSION 1
#define GGAMESOURCE_CONFIG_PATH QString(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + '/' + mStoreFileName + ".json")

#include "ggamesourcemanager.h"
#include "gsteamgamesource.h"

#include <QDebug>
#include <QDataStream>
#include <QIODevice>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QStandardPaths>
#include <QDir>

GGameSourceManager::GGameSourceManager(QObject *parent)
    : QObject{parent}
{
    QDir().mkpath(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation));
}

GGameSourceManager::~GGameSourceManager()
{
}

QQmlListProperty<GGameDetailsItem> GGameSourceManager::games()
{
    return QQmlListProperty<GGameDetailsItem>(this, &mGamesCacheList);
}

bool GGameSourceManager::addSource(GGameSourceManager::SourceType type, const QString &name, const QString &path)
{
    if (mSources.contains(name))
    {
        qDebug() << "GGameSourceManager::addSource: name is exists" << name;
        return false;
    }

    SourceItem item;
    switch (static_cast<int>(type))
    {
    case SourceType::SteamSource:
    {
        auto steam = new GSteamGameSource;
        steam->setSourceDirectory(path);
        item.source = QSharedPointer<GAbstractGameSource>(steam);
    }
        break;

    default:
        return false;
    }

    connect(item.source.data(), &GAbstractGameSource::gamesChanged, this, &GGameSourceManager::reloadRequest);

    item.type = type;
    item.name = name;
    item.path = path;

    mSources[name] = item;
    return true;
}

bool GGameSourceManager::saveConfigs() const
{
    QJsonArray sources;
    for (const auto &item: mSources)
    {
        QJsonObject obj;
        obj["type"] = (int)item.type;
        obj["name"] = item.name;
        obj["path"] = item.path;

        sources << obj;
    }

    QJsonObject root;
    root["header"] = GGAMESOURCE_CONFIG_HEADER;
    root["version"] = GGAMESOURCE_CONFIG_VERSION;
    root["sources"] = sources;

    const auto storePath = GGAMESOURCE_CONFIG_PATH;
    QFile f(storePath);
    if (!f.open(QFile::WriteOnly))
        return false;

    f.write( QJsonDocument(root).toJson() );
    f.close();
    return true;
}

bool GGameSourceManager::restoreConfigs()
{
    const auto storePath = GGAMESOURCE_CONFIG_PATH;
    QFile f(storePath);
    if (!f.open(QFile::ReadOnly))
        return false;

    QJsonParseError error;
    const auto document = QJsonDocument::fromJson(f.readAll(), &error);
    f.close();

    if (error.error != QJsonParseError::NoError)
    {
        qDebug() << error.errorString();
        return false;
    }

    const auto root = document.object();
    if (root.value("header").toString() != GGAMESOURCE_CONFIG_HEADER)
    {
        qDebug() << "GGameSourceManager::restoreConfigs: invalid header";
        return false;
    }

    mSources.clear();

    switch (root.value("version").toInt())
    {
    case 1:
    {
        for (const auto v: root.value("sources").toArray())
        {
            const auto obj = v.toObject();
            const auto type = obj.value("type").toInt();
            const auto name = obj.value("name").toString();
            const auto path = obj.value("path").toString();

            addSource(static_cast<SourceType>(type), name, path);
        }
    }
        break;

    default:
        qDebug() << "GGameSourceManager::restoreConfigs: invalid version";
        return false;
    }

    return true;
}

void GGameSourceManager::reloadRequest()
{
    mGamesCacheList.clear();
    for (const auto &item: mSources)
        mGamesCacheList << item.source->games();

    Q_EMIT gamesChanged();
}

QString GGameSourceManager::storeFileName() const
{
    return mStoreFileName;
}

void GGameSourceManager::setStoreFileName(const QString &newStoreFileName)
{
    if (mStoreFileName == newStoreFileName)
        return;
    mStoreFileName = newStoreFileName;
    restoreConfigs();
    Q_EMIT storeFileNameChanged();
}
