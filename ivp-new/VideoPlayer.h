#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <qmediaplayer.h>

#include <QtGui/QMovie>
#include <QtWidgets/QWidget>
#include <QGraphicsView>
#include <QGraphicsVideoItem>

#include "Overlay.h"

QT_BEGIN_NAMESPACE
class QAbstractButton;
class QSlider;
class QLabel;
QT_END_NAMESPACE

class VideoPlayer : public QWidget
{
    Q_OBJECT
public:
    VideoPlayer(QWidget *parent, Overlay* _overlay);
    ~VideoPlayer();
    QSize sizeHint() const;

protected:
    void resizeEvent(QResizeEvent *e);

signals:
    /*
     * Emit playTo to tell MetaInfo change of position while playing
     * so that overlay infomations can be updated
     * Ideally this signal should be emitted every frame,
     * we emit it when mediaplayer sends position changed signal
     */
    void playTo(int millisecond);
    /*
     * Emit seekTo whenever slider is moved
     */
    void seekTo(int millisecond);

    void openClick();

public slots:
    /*
     * open video file and prepare to play
     */
    void open(QString fileName);
    //QSize resolution = media.canonicalResource().resolution();



private slots:
    void mediaStateChanged(QMediaPlayer::State state);
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);
    void setPosition(int position);
    void handleError();
    void play();

private:
    QMediaPlayer mediaPlayer;
    QAbstractButton *playButton;
    QAbstractButton *openButton;
    QSlider *positionSlider;
    Overlay *overlay;
    QSize videoSize;
    //QVideoWidget *videoWidget;
    // test
    QGraphicsView *videoView;
    QGraphicsVideoItem *videoItem;
    QGraphicsScene *scene;


    void layoutChildren();
    void resizeOverlay();
    //QLabel *errorLabel;
};

#endif
