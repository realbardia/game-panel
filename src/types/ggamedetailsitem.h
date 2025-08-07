#ifndef GGAMEDETAILSITEM_H
#define GGAMEDETAILSITEM_H

#include <QObject>
#include <QUrl>
#include <QPointer>

#include "abstracts/gabstractgamesource.h"

class GGameDetailsItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(GAbstractGameSource *source READ source NOTIFY sourceChanged FINAL)
    Q_PROPERTY(QString gameId READ gameId NOTIFY gameIdChanged FINAL)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged FINAL)
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged FINAL)
    Q_PROPERTY(QUrl portraitCoverImage READ portraitCoverImage WRITE setPortraitCoverImage NOTIFY portraitCoverImageChanged FINAL)
    Q_PROPERTY(QUrl landscapeCoverImage READ landscapeCoverImage WRITE setLandscapeCoverImage NOTIFY landscapeCoverImageChanged FINAL)
    Q_PROPERTY(QUrl icon READ icon WRITE setIcon NOTIFY iconChanged FINAL)
    Q_PROPERTY(QUrl headerImage READ headerImage WRITE setHeaderImage NOTIFY headerImageChanged FINAL)

public:
    GGameDetailsItem(GAbstractGameSource *source, const QString &gameId);
    virtual ~GGameDetailsItem();

    GAbstractGameSource *source() const;
    QString gameId() const;

    QString title() const;
    void setTitle(const QString &newTitle);

    QString path() const;
    void setPath(const QString &newPath);

    QUrl portraitCoverImage() const;
    void setPortraitCoverImage(const QUrl &newPortraitCoverImage);

    QUrl landscapeCoverImage() const;
    void setLandscapeCoverImage(const QUrl &newLandscapeCoverImage);

    QUrl icon() const;
    void setIcon(const QUrl &newIcon);

    QUrl headerImage() const;
    void setHeaderImage(const QUrl &newHeaderImage);

Q_SIGNALS:
    void sourceChanged();
    void gameIdChanged();
    void titleChanged();
    void pathChanged();
    void portraitCoverImageChanged();
    void landscapeCoverImageChanged();
    void iconChanged();
    void headerImageChanged();

private:
    QPointer<GAbstractGameSource> mSource;

    QString mGameId;
    QString mTitle;
    QString mPath;
    QUrl mPortraitCoverImage;
    QUrl mLandscapeCoverImage;
    QUrl mIcon;
    QUrl mHeaderImage;
};

#endif // GGAMEDETAILSITEM_H
