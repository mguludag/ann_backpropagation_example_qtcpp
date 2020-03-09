#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "myneuralnetwork.h"
#include <QDialog>
#include <QElapsedTimer>
#include <QLabel>
#include <QMainWindow>
#include <QStandardItemModel>
#include <QTableView>
#include <QThread>

//#include <QtCharts>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QThread *thread;
    QElapsedTimer *timer;
    QLabel *status;
    QStandardItemModel *model1;
    QStandardItemModel *mdl;
    QItemSelectionModel *selectionModel;
    QStandardItemModel *model;
    QStandardItemModel *modelTemp;
    std::vector<std::vector<std::array<QString, 17>>> *models;
    std::vector<std::array<QString, 17>> mod;
    std::array<QString, 17> rowData = {"*"};
    std::array<QString, 4> io = {};
    std::vector<MyNeuralNetwork *> iolist;
    int idx, max = 1, m_size;
    bool checked = false;
    MyNeuralNetwork *N[8];
    int *p_arr;
    int arr[8][4] = {{0, 0, 0, 0},
                     {0, 0, 1, 1},
                     {0, 1, 0, 0},
                     {0, 1, 1, 0},
                     {1, 0, 0, 0},
                     {1, 0, 1, 0},
                     {1, 1, 0, 1},
                     {1, 1, 1, 1}};

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void fillData(int row, MyNeuralNetwork &N);
    void fillDataLast(int row, MyNeuralNetwork &N);
    void start();

private slots:
    void on_pushButton_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_3_clicked();

    void on_spinBox_2_valueChanged(int arg1);

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void refreshTable();

    void on_checkBox_toggled(bool checked);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
