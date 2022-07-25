#include "StressTestManager.h"
#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QThread>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->Start, &QPushButton::clicked,
        this, &MainWindow::startStressTest);
    QObject::connect(ui->Stop, &QPushButton::clicked,
        this, &MainWindow::stopStressTest);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startStressTest()
{
    if (m_stressTestThread != nullptr || m_stressTestManager != nullptr)
    {
        // something is wrong here
        return;
    }

    m_stressTestThread = new QThread(this);
    m_stressTestThread->setObjectName("StressTestThread");
    m_stressTestManager = new StressTestManager();

    QObject::connect(m_stressTestManager, &StressTestManager::stressTestCompleted,
        this, &MainWindow::onStressTestFinished);

    m_stressTestManager->moveToThread(m_stressTestThread);
    m_stressTestThread->start();

    m_isStressTesting = true;

    QMetaObject::invokeMethod(m_stressTestManager, "setKeepStressTesting", Qt::QueuedConnection,
        Q_ARG(bool, true));

    QMetaObject::invokeMethod(m_stressTestManager, "startStressTest", Qt::QueuedConnection);
}

void MainWindow::stopStressTest()
{
    if (m_stressTestThread == nullptr || m_stressTestManager == nullptr)
    {
        return;
    }

    QMetaObject::invokeMethod(m_stressTestManager, "setKeepStressTesting",
        Qt::QueuedConnection, Q_ARG(bool, false));

    m_stressTestThread->quit(); // QT bug : doesn't work since wait() will wait indefinitely
    m_stressTestThread->wait();

    delete m_stressTestManager; m_stressTestManager = nullptr;
    delete m_stressTestThread; m_stressTestThread = nullptr;

    m_isStressTesting = false;

    QMessageBox::warning(this, "Application", "Stress test aborted !");
}

void MainWindow::onStressTestFinished()
{
    m_isStressTesting = false;

    if (m_stressTestThread == nullptr || m_stressTestManager == nullptr)
    {
        return;
    }

    m_stressTestThread->quit();
    m_stressTestThread->wait();

    delete m_stressTestManager; m_stressTestManager = nullptr;
    delete m_stressTestThread; m_stressTestThread = nullptr;

    QMessageBox::warning(this, "Application", "Stress test finished !");
}
