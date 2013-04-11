#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <qmediaplayer.h>

#include <QtGui/QMovie>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE
class QAbstractButton;
class QSlider;
class QLabel;
QT_END_NAMESPACE

class VideoPlayer : public QWidget
{
    Q_OBJECT
public:
    VideoPlayer(QWidget *parent = 0);
    ~VideoPlayer();
    QSize sizeHint() const;


public signals:
    /*
     * Emit playTo to tell MetaInfo change of position while playing
     * so that overlay infomations can be updated
     * Ideally this signal should be emitted every frame,
     * we emit it when mediaplayer sends position changed signal
     */
    void playTo(int millisecond);
    /*
     * Emit scanTo whenever slider is moved
     */
    void scanTo(int millisecond);

public slots:
    /*
     * open video file and prepare to play
     */
    void open(QString fileName);


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
    QSlider *positionSlider;
    //QLabel *errorLabel;
};

#endif
