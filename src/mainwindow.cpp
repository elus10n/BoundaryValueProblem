#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QApplication>
#include <QtCharts/QValueAxis>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setAlternatingRowColors(true);

    setupCharts();

    connect(ui->solveButton, &QPushButton::clicked, this, &MainWindow::onSolveClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupCharts()
{
    solutionChart = new QChart();
    solutionChart->setTitle("Графики решений");

    errorChart = new QChart();
    errorChart->setTitle("График погрешности");

    ui->solutionChartView->setChart(solutionChart);
    ui->solutionChartView->setRenderHint(QPainter::Antialiasing);

    ui->errorChartView->setChart(errorChart);
    ui->errorChartView->setRenderHint(QPainter::Antialiasing);

}

void MainWindow::onSolveClicked()
{
    try {
        std::unique_ptr<WrapperInterface> wrapper;

        if (ui->taskComboBox->currentIndex() == 3) {
            wrapper = std::make_unique<Task4Wrapper>();
        } else {
            throw std::runtime_error("error");
        }

        TYPE currentType = wrapper->get_type();

        FrontendOutput result = Wrapper(std::move(wrapper));

        updateInfo(result, currentType);
        updateTable(result, currentType);
        updateCharts(result, currentType);

    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка", e.what());
        ui->infoLabel->setText("Произошла ошибка при вычислениях.");
    }
}

void MainWindow::updateInfo(const FrontendOutput& data, TYPE taskType)
{
    QString info = QString("Для решения задачи использована равномерная сетка с числом разбиений n = %1;\n\n").arg(data.n);

    if (taskType == TYPE::MAIN) {
        info += "Задача должна быть решена с заданной точностью eps = 0.5 * 10^-6;\n";
        info += QString("Задача решена с достигнутой точностью eps2 = %1;\n").arg(data.epsilon, 0, 'g', 6);
        info += QString("Максимальная разность численных решений в общих узлах сетки наблюдается в точке x = %1.").arg(data.x_max_deflection);
    } else {
        info += "Задача должна быть решена с погрешностью не более eps = 0.5 * 10^-6;\n";
        info += QString("Задача решена с погрешностью eps1 = %1;\n").arg(data.epsilon, 0, 'g', 6);
        info += QString("Максимальное отклонение аналитического и численного решений наблюдается в точке x = %1.").arg(data.x_max_deflection);
    }

    ui->infoLabel->setText(info);
}

void MainWindow::updateTable(const FrontendOutput& data, TYPE taskType)
{
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(5);

    QString col3 = (taskType == TYPE::MAIN) ? "v2(x_2i)[Сетка 2n]" : "u(x_i) [Аналит]";
    ui->tableWidget->setHorizontalHeaderLabels({"№ узла", "x_i", "v(x_i)", col3, "Разность"});

    int totalNodes = data.grid.size();
    int step = 1;

    if (totalNodes > 200) {
        step = totalNodes / 200;
    }

    int displayRows = totalNodes / step + ((totalNodes % step == 0) ? 0 : 1);
    ui->tableWidget->setRowCount(displayRows);

    int row = 0;
    for (int i = 0; i < totalNodes; i += step) {
        double x = data.grid[i];
        double v1 = data.numerical[i];
        double v2 = (taskType == TYPE::MAIN) ? data.to_compare[i * 2] : data.to_compare[i];
        double diff = std::abs(v1 - v2);

        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(i)));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(x, 'f', 5)));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(v1, 'g', 6)));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(v2, 'g', 6)));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(diff, 'g', 6)));
        row++;
    }

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::updateCharts(const FrontendOutput& data, TYPE taskType)
{
    solutionChart->removeAllSeries();
    errorChart->removeAllSeries();

    QLineSeries *seriesV = new QLineSeries();
    seriesV->setName("v(x) [Текущая сетка]");

    QLineSeries *seriesCompare = new QLineSeries();
    seriesCompare->setName((taskType == TYPE::MAIN) ? "v2(x) [Двойная сетка]" : "u(x) [Аналитическое]");

    QLineSeries *seriesError = new QLineSeries();
    seriesError->setName("Погрешность");

    for (size_t i = 0; i < data.grid.size(); ++i) {
        double x = data.grid[i];
        double v1 = data.numerical[i];
        double v2 = (taskType == TYPE::MAIN) ? data.to_compare[i * 2] : data.to_compare[i];

        seriesV->append(x, v1);
        seriesCompare->append(x, v2);
        seriesError->append(x, std::abs(v1 - v2));
    }

    solutionChart->addSeries(seriesV);
    solutionChart->addSeries(seriesCompare);
    solutionChart->createDefaultAxes();

    errorChart->addSeries(seriesError);
    errorChart->createDefaultAxes();
}



