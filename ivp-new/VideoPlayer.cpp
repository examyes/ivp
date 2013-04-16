#include "VideoPlayer.h"

#include <QtWidgets>
#include <qvideowidget.h>
#include <qvideosurfaceformat.h>

VideoPlayer::VideoPlayer(QWidget *parent, Overlay* _overlay)
    : QWidget(parent)
    , mediaPlayer(0, QMediaPlayer::VideoSurface)
    , playButton(0)
    , positionSlider(0)
{


    // video widget

    videoView = new QGraphicsView(this);
    scene = new QGraphicsScene(videoView);
    videoView->setScene(scene);

    videoItem = new QGraphicsVideoItem;
    mediaPlayer.setVideoOutput(videoItem);

    scene->addItem(videoItem);

    //videoWidget = new QVideoWidget(this);
    //videoWidget->setAttribute(Qt::WA_TranslucentBackground);

    // playbutton
    playButton = new QPushButton(this);
    playButton->setEnabled(false);
    playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    connect(playButton, SIGNAL(clicked()),
            this, SLOT(play()));

    // slider
    positionSlider = new QSlider(Qt::Horizontal, this);
    positionSlider->setRange(0, 0);
    connect(positionSlider, SIGNAL(sliderMoved(int)),
            this, SLOT(setPosition(int)));

    // layout
    // I decide to do layout myself...
    layoutChildren();
    /*
    QBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->setMargin(0);
    controlLayout->addWidget(playButton);
    controlLayout->addWidget(positionSlider);
    QBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(videoWidget);
    layout->addLayout(controlLayout);
    setLayout(layout);
    */


    // overlay

    overlay = _overlay;
    /*
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::red);
    overlay->setAutoFillBackground(true);
    overlay->setPalette(Pal);
    */
    overlay->setParent(this);
    overlay->show();

    // media player setup
    //mediaPlayer.setVideoOutput(videoWidget);
    connect(&mediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State)),
            this, SLOT(mediaStateChanged(QMediaPlayer::State)));
    connect(&mediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    connect(&mediaPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));
    connect(&mediaPlayer, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(handleError()));
}

VideoPlayer::~VideoPlayer() {
}

void VideoPlayer::open(QString fileName)
{
    if (!fileName.isEmpty()) {

        mediaPlayer.setMedia(QUrl::fromLocalFile(fileName));
        playButton->setEnabled(true);

        // resize overlay
        resizeOverlay();
        layoutChildren();
    }
}

void VideoPlayer::layoutChildren(){
    QSize mysize = this->size();
    QSize buttonSize = playButton->sizeHint();
    QSize sliderSize = positionSlider->sizeHint();

    int bottomHeight = buttonSize.height() + sliderSize.height();
    int buttonLeft = (mysize.width() - buttonSize.width()) / 2;

    playButton->move(buttonLeft, mysize.height() - buttonSize.height());
    positionSlider->setGeometry(0, mysize.height() - bottomHeight,
            mysize.width(), sliderSize.height());

    videoItem->setOffset(QPointF());
    videoView->setGeometry(0, 0, mysize.width(), mysize.height() - bottomHeight);

    videoView->lower();
}

void VideoPlayer::resizeOverlay(){
    QSizeF s = videoItem->nativeSize();
    QSize videoSize = QSize(int(s.width()), int(s.height()));

    QSize playerSize = videoView->size();
    Qt::AspectRatioMode mode = videoItem->aspectRatioMode();

    QSize overlaySize(videoSize.width(), videoSize.height());
    overlaySize.scale(playerSize, mode);

    int left = (playerSize.width() - overlaySize.width()) / 2;
    int top = (playerSize.height() - overlaySize.height()) / 2;

    videoItem->setOffset(QPointF(left, top));
    videoItem->setSize(QSizeF(overlaySize.width(), overlaySize.height()));

    overlay->setGeometry(left, top, overlaySize.width(), overlaySize.height());
    overlay->raise();

    printf("video size :%d %d\n", videoSize.width(), videoSize.height());
    printf("Overlay resize: %d %d %d %d\n", left, top, overlaySize.width(), overlaySize.height());
}

void VideoPlayer::resizeEvent(QResizeEvent *e) {
    layoutChildren();
    resizeOverlay();
}


void VideoPlayer::play() {
    switch(mediaPlayer.state()) {
    case QMediaPlayer::PlayingState:
        mediaPlayer.pause();
        break;
    default:
        mediaPlayer.play();
        break;
    }
}

void VideoPlayer::mediaStateChanged(QMediaPlayer::State state) {
    switch(state) {
    case QMediaPlayer::PlayingState:
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        emit seekTo(0);
        break;
    default:
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        emit seekTo(0);
        break;
    }
}

void VideoPlayer::positionChanged(qint64 position) {
    positionSlider->setValue(position);
    resizeOverlay();
    emit playTo(position);
}

void VideoPlayer::durationChanged(qint64 duration) {
    positionSlider->setRange(0, duration);
}

void VideoPlayer::setPosition(int position) {
    mediaPlayer.setPosition(position);
    emit seekTo(position);
}

void VideoPlayer::handleError() {
    playButton->setEnabled(false);
}

QSize VideoPlayer::sizeHint() const{
    return QSize(400,600);
}
