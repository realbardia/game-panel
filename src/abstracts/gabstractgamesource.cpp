#include "gabstractgamesource.h"
#include "types/ggamedetailsitem.h"

#include <QVariant>

GAbstractGameSource::GAbstractGameSource(QObject *parent)
    : QObject{parent}
{
    mReloadTimer = new QTimer(this);
    mReloadTimer->setSingleShot(true);
    mReloadTimer->setInterval(10);

    connect(mReloadTimer, &QTimer::timeout, this, &GAbstractGameSource::reload);
}

GAbstractGameSource::~GAbstractGameSource()
{
}

void GAbstractGameSource::refresh()
{
    mReloadTimer->stop();
    mReloadTimer->start();
}

QList<GGameDetailsItem *> GAbstractGameSource::games() const
{
    return mGames;
}

void GAbstractGameSource::setGames(const QList<GGameDetailsItem *> &newGames)
{
    if (mGames == newGames)
        return;
    mGames = newGames;
    Q_EMIT gamesChanged();
}
