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
    Q_PROPERTY(QString storeFileName READ storeFileName WRITE setStoreFileName NOTIFY storeFileNameChanged FINAL)

public:
    enum SourceType {
        SteamSource
    };
    Q_ENUM(SourceType)

    GGameSourceManager(QObject *parent = nullptr);
    virtual ~GGameSourceManager();

    QQmlListProperty<GGameDetailsItem> games();

    QString storeFileName() const;
    void setStoreFileName(const QString &newStoreFileName);

public Q_SLOTS:
    bool addSource(SourceType type, const QString &name, const QString &path);

    bool saveConfigs() const;
    bool restoreConfigs();

Q_SIGNALS:
    void gamesChanged();
    void storeFileNameChanged();

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

    QString mStoreFileName;
};

#endif // GGAMESOURCEMANAGER_H
