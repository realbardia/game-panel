#ifndef GGAMESOURCEMANAGER_H
#define GGAMESOURCEMANAGER_H

#include <QMap>
#include <QObject>
#include <QSharedPointer>
#include <QQmlListProperty>

#include "types/ggamedetailsitem.h"

class GAbstractGameSource;
class GGameSourceManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<GGameDetailsItem> games READ games NOTIFY gamesChanged FINAL)

public:
    enum SourceType {
        SteamSource
    };
    Q_ENUM(SourceType)

    GGameSourceManager(QObject *parent = nullptr);
    virtual ~GGameSourceManager();

    QQmlListProperty<GGameDetailsItem> games();

public Q_SLOTS:
    bool addSource(SourceType type, const QString &name, const QString &path);

    QString saveConfigs() const;
    bool restoreConfigs(const QString &configs);

Q_SIGNALS:
    void gamesChanged();

protected:
    void reloadRequest();

private:
    struct SourceItem {
        QSharedPointer<GAbstractGameSource> source;
        SourceType type;
        QString name;
        QString path;
    };

    QMap<QString, SourceItem> mSources;
    QList<GGameDetailsItem*> mGamesCacheList;
};

#endif // GGAMESOURCEMANAGER_H
