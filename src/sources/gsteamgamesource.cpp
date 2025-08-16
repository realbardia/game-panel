#include "gsteamgamesource.h"

#include <QFileInfo>
#include <QDebug>
#include <QDir>
#include <QJsonDocument>
#include <QRegularExpression>
#include <QString>
#include <QVariantMap>
#include <QList>
#include <QChar>
#include <QDebug>

#include "types/ggamedetailsitem.h"
#include "tools/acfparser.h"

GSteamGameSource::GSteamGameSource(QObject *parent)
    : GAbstractGameSource{parent}
{}

GSteamGameSource::~GSteamGameSource()
{
}

void GSteamGameSource::reload()
{
    QList<GGameDetailsItem*> games;

    QFileInfo info(mSourceDirectory);
    if (!info.exists())
    {
        qDebug() << "ERR:" << mSourceDirectory << "not exists.";
    }
    else if (!info.isDir())
    {
        qDebug() << "ERR:" << mSourceDirectory << "is not directory.";
    }
    else if (!mSourceDirectory.isEmpty())
    {
        const auto steamappsPath = mSourceDirectory + QStringLiteral("/steamapps/");
        const auto libraryCachePath = mSourceDirectory + QStringLiteral("/appcache/librarycache/");

        for (const auto &f: QDir(steamappsPath).entryList({"appmanifest_*.acf"}, QDir::Files))
        {
            const auto path = steamappsPath + f;
            QFile appFile(path);
            if (!appFile.open(QFile::ReadOnly))
            {
                qDebug() << appFile.errorString() << path;
                continue;
            }

            const auto data = QString::fromUtf8( appFile.readAll() );

            bool ok;
            QString error;
            const auto result = ACFParser::parseACFFileContent(data, &ok, &error);
            if (!ok)
            {
                qDebug() << "Error:" << error << path;
                continue;
            }

            const auto appDetails = result.value( QStringLiteral("AppState") ).toMap();
            const auto title = appDetails.value( QStringLiteral("name") ).toString();
            const auto gameId = appDetails.value( QStringLiteral("appid") ).toString();

            const auto portraitCover = libraryCachePath + '/' + gameId + '/' + QStringLiteral("library_600x900.jpg");
            const auto landscapeCover = libraryCachePath + '/' + gameId + '/' + QStringLiteral("header.jpg");
            const auto headerImage = libraryCachePath + '/' + gameId + '/' + QStringLiteral("library_hero.jpg");
            const auto icon = libraryCachePath + '/' + gameId + '/' + QStringLiteral("logo.png");

            auto item = new GGameDetailsItem(this, gameId);
            item->setTitle(title);
            item->setPath(path);

            if (QFileInfo::exists(portraitCover))
                item->setPortraitCoverImage(QUrl::fromLocalFile(portraitCover));
            if (QFileInfo::exists(landscapeCover))
                item->setLandscapeCoverImage(QUrl::fromLocalFile(landscapeCover));
            if (QFileInfo::exists(headerImage))
                item->setHeaderImage(QUrl::fromLocalFile(headerImage));
            if (QFileInfo::exists(icon))
                item->setIcon(QUrl::fromLocalFile(icon));

            games << item;
        }
    }

    setGames(games);
}

QString GSteamGameSource::sourceDirectory() const
{
    return mSourceDirectory;
}

void GSteamGameSource::setSourceDirectory(const QString &newSourceDirectory)
{
    if (mSourceDirectory == newSourceDirectory)
        return;
    mSourceDirectory = newSourceDirectory;
    refresh();
    Q_EMIT sourceDirectoryChanged();
}

void GSteamGameSource::run(GGameDetailsItem *game)
{

}
