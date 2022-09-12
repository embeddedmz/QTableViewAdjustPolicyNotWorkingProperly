#ifndef STRESSTESTMANAGER_H
#define STRESSTESTMANAGER_H

#include <QObject>

class StressTestManager final : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(StressTestManager)
public:
    explicit StressTestManager(QObject* parent = nullptr);
    ~StressTestManager() override;

public slots:
    // call it from another thread via QMetaObject::invokeMethod !
    void setKeepStressTesting(const bool keep);
    void startStressTest();

    void onThreadFinishTest();

signals:
    void stressTestCompleted();

private:
    bool isCanceled();
    void processEvents();

private:
    struct Internals;
    Internals* m_Internals;
};

#endif // STRESSTESTMANAGER_H
