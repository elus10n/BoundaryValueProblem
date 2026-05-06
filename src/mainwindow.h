#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QPushButton>
#include <QTextEdit>
#include <QTableWidget>
#include <QTabWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

#include "Interface/wrapper.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSolveClicked();

private:
    Ui::MainWindow *ui;

    QChart *solutionChart;
    QChart *errorChart;

    void setupCharts();
    void updateTable(const FrontendOutput& data, TYPE taskType);
    void updateCharts(const FrontendOutput& data, TYPE taskType);
    void updateInfo(const FrontendOutput& data, TYPE taskType);
};

#endif // MAINWINDOW_H
