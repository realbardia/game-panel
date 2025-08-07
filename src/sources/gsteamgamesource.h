#ifndef GSTEAMGAMESOURCE_H
#define GSTEAMGAMESOURCE_H

#include <QObject>

#include "abstracts/gabstractgamesource.h"

class GSteamGameSource : public GAbstractGameSource
{
    Q_OBJECT
    Q_PROPERTY(QString sourceDirectory READ sourceDirectory WRITE setSourceDirectory NOTIFY sourceDirectoryChanged FINAL)

public:
    GSteamGameSource(QObject *parent = nullptr);
    virtual ~GSteamGameSource();

    QString sourceDirectory() const;
    void setSourceDirectory(const QString &newSourceDirectory);

public Q_SLOTS:
    void run(GGameDetailsItem *game) override;

Q_SIGNALS:
    void sourceDirectoryChanged();

protected:
    void reload() override;

private:
    QString mSourceDirectory;
};

#endif // GSTEAMGAMESOURCE_H
