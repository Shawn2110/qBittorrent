#pragma once

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QVBoxLayout>

class FloatingSpeedWidget final : public QWidget
{
    Q_OBJECT

public:
    explicit FloatingSpeedWidget(QWidget *parent = nullptr);
    void startUpdates();
    void stopUpdates();

private slots:
    void updateSpeeds();

private:
    QLabel *m_label;
    QTimer *m_timer;
    QString formatSpeed(qint64 bytesPerSec);
};
