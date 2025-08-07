#define GGAMESOURCE_CONFIG_HEADER QStringLiteral("GGameSourceConfig")
#define GGAMESOURCE_CONFIG_VERSION 1

#include "ggamesourcemanager.h"
#include "gsteamgamesource.h"

#include <QDebug>
#include <QDataStream>
#include <QIODevice>

GGameSourceManager::GGameSourceManager(QObject *parent)
    : QObject{parent}
{
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

QString GGameSourceManager::saveConfigs() const
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream << GGAMESOURCE_CONFIG_HEADER;
    stream << GGAMESOURCE_CONFIG_VERSION;

    stream << (int)mSources.size();
    for (const auto &item: mSources)
    {
        stream << (int)item.type;
        stream << item.name;
        stream << item.path;
    }

    return QString::fromUtf8(data.toBase64());
}

bool GGameSourceManager::restoreConfigs(const QString &configs)
{
    const auto data = QByteArray::fromBase64(configs.toUtf8());
    QDataStream stream(data);

    QString header;
    stream >> header;
    if (header != GGAMESOURCE_CONFIG_HEADER)
    {
        qDebug() << "GGameSourceManager::restoreConfigs: invalid header";
        return false;
    }

    mSources.clear();

    int version;
    stream >> version;
    switch (version)
    {
    case 1:
    {
        int size;
        stream >> size;
        while (size > 0)
        {
            int type;
            QString name;
            QString path;

            stream >> type;
            stream >> name;
            stream >> path;

            addSource(static_cast<SourceType>(type), name, path);
            size--;
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
