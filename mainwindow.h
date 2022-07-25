#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class StressTestManager;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected slots:
    void startStressTest();
    void stopStressTest();
    void onStressTestFinished();

private:
    Ui::MainWindow *ui;

    QThread* m_stressTestThread = nullptr;
    StressTestManager* m_stressTestManager = nullptr;
    bool m_isStressTesting = false;
};
#endif // MAINWINDOW_H
