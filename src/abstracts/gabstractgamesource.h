#ifndef GABSTRACTGAMESOURCE_H
#define GABSTRACTGAMESOURCE_H

#include <QObject>
#include <QTimer>
#include <QVariantList>

class GGameDetailsItem;
class GAbstractGameSource : public QObject
{
    Q_OBJECT
public:
    GAbstractGameSource(QObject *parent = nullptr);
    virtual ~GAbstractGameSource();

    QList<GGameDetailsItem *> games() const;

public Q_SLOTS:
    void refresh();
    virtual void run(GGameDetailsItem *game) = 0;

Q_SIGNALS:
    void gamesChanged();

protected:
    virtual void reload() = 0;
    void setGames(const QList<GGameDetailsItem *> &newGames);

private:
    QTimer *mReloadTimer = nullptr;
    QList<GGameDetailsItem*> mGames;
};

#endif // GABSTRACTGAMESOURCE_H
