#include "floatingwidget.h"
#include "base/bittorrent/session.h"   // existing qBittorrent session class for speed info
#include "base/utils/misc.h"           // for Utils::Misc::friendlyUnit()
#include <QStyle>
#include <QApplication>

FloatingSpeedWidget::FloatingSpeedWidget(QWidget *parent)
    : QWidget(parent)
    , m_label(new QLabel(this))
    , m_timer(new QTimer(this))
{
    setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_ShowWithoutActivating);
    setWindowTitle(tr("Speed Monitor"));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_label);
    layout->setContentsMargins(8, 8, 8, 8);
    setLayout(layout);

    m_label->setAlignment(Qt::AlignCenter);
    m_label->setStyleSheet("QLabel { color: white; background: rgba(0,0,0,140); font: bold 12px; border-radius: 6px; padding: 4px; }");
    m_label->setText(tr("DL: 0 B/s  UL: 0 B/s"));

    m_timer->setInterval(1000);
    connect(m_timer, &QTimer::timeout, this, &FloatingSpeedWidget::updateSpeeds);
}

void FloatingSpeedWidget::startUpdates()
{
    m_timer->start();
    show();
}

void FloatingSpeedWidget::stopUpdates()
{
    m_timer->stop();
    hide();
}

void FloatingSpeedWidget::updateSpeeds()
{
    using BitTorrent::Session;

    qint64 downloadSpeed = Session::instance()->downloadSpeed();
    qint64 uploadSpeed = Session::instance()->uploadSpeed();

    QString text = QStringLiteral("DL: %1/s   UL: %2/s")
        .arg(formatSpeed(downloadSpeed))
        .arg(formatSpeed(uploadSpeed));

    m_label->setText(text);
}

QString FloatingSpeedWidget::formatSpeed(qint64 bytesPerSec)
{
    return Utils::Misc::friendlyUnit(bytesPerSec, true);
}
