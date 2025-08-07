#include "ggamedetailsitem.h"

GGameDetailsItem::GGameDetailsItem(GAbstractGameSource *source, const QString &gameId)
    : QObject{source}
    , mSource(source)
    , mGameId(gameId)
{
}

GGameDetailsItem::~GGameDetailsItem()
{

}

GAbstractGameSource *GGameDetailsItem::source() const
{
    return mSource;
}

QString GGameDetailsItem::gameId() const
{
    return mGameId;
}

QString GGameDetailsItem::title() const
{
    return mTitle;
}

void GGameDetailsItem::setTitle(const QString &newTitle)
{
    if (mTitle == newTitle)
        return;
    mTitle = newTitle;
    Q_EMIT titleChanged();
}

QString GGameDetailsItem::path() const
{
    return mPath;
}

void GGameDetailsItem::setPath(const QString &newPath)
{
    if (mPath == newPath)
        return;
    mPath = newPath;
    Q_EMIT pathChanged();
}

QUrl GGameDetailsItem::portraitCoverImage() const
{
    return mPortraitCoverImage;
}

void GGameDetailsItem::setPortraitCoverImage(const QUrl &newPortraitCoverImage)
{
    if (mPortraitCoverImage == newPortraitCoverImage)
        return;
    mPortraitCoverImage = newPortraitCoverImage;
    Q_EMIT portraitCoverImageChanged();
}

QUrl GGameDetailsItem::landscapeCoverImage() const
{
    return mLandscapeCoverImage;
}

void GGameDetailsItem::setLandscapeCoverImage(const QUrl &newLandscapeCoverImage)
{
    if (mLandscapeCoverImage == newLandscapeCoverImage)
        return;
    mLandscapeCoverImage = newLandscapeCoverImage;
    Q_EMIT landscapeCoverImageChanged();
}

QUrl GGameDetailsItem::icon() const
{
    return mIcon;
}

void GGameDetailsItem::setIcon(const QUrl &newIcon)
{
    if (mIcon == newIcon)
        return;
    mIcon = newIcon;
    Q_EMIT iconChanged();
}

QUrl GGameDetailsItem::headerImage() const
{
    return mHeaderImage;
}

void GGameDetailsItem::setHeaderImage(const QUrl &newHeaderImage)
{
    if (mHeaderImage == newHeaderImage)
        return;
    mHeaderImage = newHeaderImage;
    Q_EMIT headerImageChanged();
}
