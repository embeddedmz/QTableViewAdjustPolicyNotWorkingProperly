#include "StressTestManager.h"

#include <QAbstractEventDispatcher>
#include <QDateTime>
#include <QDebug>
#include <QElapsedTimer>
#include <QFile>
#include <QThread>
#include <QTimer>

namespace
{
}

struct StressTestManager::Internals
{
    bool KeepStressTesting = true;
};

StressTestManager::StressTestManager(QObject* parent) :
    QObject(parent),
    m_Internals(new StressTestManager::Internals)
{
}

StressTestManager::~StressTestManager()
{
    delete m_Internals;
}

void StressTestManager::setKeepStressTesting(const bool keep)
{
    if (m_Internals->KeepStressTesting != keep)
    {
        m_Internals->KeepStressTesting = keep;
    }
}

void StressTestManager::startStressTest()
{
    for (size_t test = 0; test < 100 && /*!testError &&*/ !isCanceled(); ++test)
    {
        QThread::msleep(100);
    }

    processEvents();

    emit stressTestCompleted();
}

void StressTestManager::onThreadFinishTest()
{
    QThread::sleep(5);
}

void StressTestManager::processEvents()
{
    auto const dispatcher = QThread::currentThread()->eventDispatcher();
    if (!dispatcher)
    {
        qCritical() << "Thread with no dispatcher";
        
        return;
    }
    dispatcher->processEvents(QEventLoop::AllEvents);
}

bool StressTestManager::isCanceled()
{
    processEvents();
    return !m_Internals->KeepStressTesting;
}
