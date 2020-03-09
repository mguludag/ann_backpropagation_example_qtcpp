#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qApp->setStyle("Fusion");
                QPalette darkPalette;
                darkPalette.setColor(QPalette::Window, QColor(53,53,53));
                darkPalette.setColor(QPalette::WindowText, Qt::white);
                darkPalette.setColor(QPalette::Base, QColor(25,25,25));
                darkPalette.setColor(QPalette::AlternateBase, QColor(53,53,53));
                darkPalette.setColor(QPalette::ToolTipBase, QColor(53,53,53));
                darkPalette.setColor(QPalette::ToolTipText, Qt::white);
                darkPalette.setColor(QPalette::Text, Qt::white);
                darkPalette.setColor(QPalette::Button, QColor(53,53,53));
                darkPalette.setColor(QPalette::ButtonText, Qt::white);
                darkPalette.setColor(QPalette::BrightText, Qt::red);
                darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
                darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
                darkPalette.setColor(QPalette::HighlightedText, Qt::black);
                darkPalette.setColor(QPalette::Disabled,QPalette::Text,QColor(164,166,168));
                darkPalette.setColor(QPalette::Disabled,QPalette::WindowText,QColor(164,166,168));
                darkPalette.setColor(QPalette::Disabled,QPalette::ButtonText,QColor(164,166,168));
                darkPalette.setColor(QPalette::Disabled,QPalette::HighlightedText,QColor(164,166,168));
                darkPalette.setColor(QPalette::Disabled,QPalette::Base,QColor(68,68,68));
                darkPalette.setColor(QPalette::Disabled,QPalette::Window,QColor(68,68,68));
                darkPalette.setColor(QPalette::Disabled,QPalette::Highlight,QColor(68,68,68));
#ifdef UNIX
                qApp->setPalette(darkPalette);
#endif

                qRegisterMetaType<QVector<int>>("QVector<int>");
                timer = new QElapsedTimer();
                status = new QLabel(ui->statusBar);
                status->setText("Ready");
                status->resize(status->width() * 2, status->height());
                model1 = new QStandardItemModel(8, 4);
                model1->setHeaderData(0, Qt::Horizontal, "X1");
                model1->setHeaderData(1, Qt::Horizontal, "X2");
                model1->setHeaderData(2, Qt::Horizontal, "X3");
                model1->setHeaderData(3, Qt::Horizontal, "Y");

                mdl = new QStandardItemModel(0, 2);
                mdl->setHeaderData(0, Qt::Horizontal, "Property");
                mdl->setHeaderData(1, Qt::Horizontal, "Test Results");
                ui->treeView->setModel(mdl);

                for (int i = 0; i < 8; ++i) {
                    N[i] = new MyNeuralNetwork();
                }

                p_arr = *arr;
                for (int i = 0; i < 8; ++i) {
                    for (int j = 0; j < 4; ++j) {
                        model1->setData(model1->index(i, j), arr[i][j]);
                    }
                }
                ui->tableView->setModel(model1);
                //ui->tableView->contentsRect().size();

                model = new QStandardItemModel(0, 17);
                modelTemp = new QStandardItemModel(0, 17);
                model->setHeaderData(0, Qt::Horizontal, "X1");
                model->setHeaderData(1, Qt::Horizontal, "X2");
                model->setHeaderData(2, Qt::Horizontal, "X3");
                model->setHeaderData(3, Qt::Horizontal, "W11");
                model->setHeaderData(4, Qt::Horizontal, "W12");
                model->setHeaderData(5, Qt::Horizontal, "W13");
                model->setHeaderData(6, Qt::Horizontal, "W21");
                model->setHeaderData(7, Qt::Horizontal, "W22");
                model->setHeaderData(8, Qt::Horizontal, "W23");
                model->setHeaderData(9, Qt::Horizontal, "W31");
                model->setHeaderData(10, Qt::Horizontal, "W32");
                model->setHeaderData(11, Qt::Horizontal, "WB1");
                model->setHeaderData(12, Qt::Horizontal, "WB2");
                model->setHeaderData(13, Qt::Horizontal, "WB3");
                model->setHeaderData(14, Qt::Horizontal, "Y");
                model->setHeaderData(15, Qt::Horizontal, "Y2");
                model->setHeaderData(16, Qt::Horizontal, "Error Rate");

                modelTemp->setHeaderData(0, Qt::Horizontal, "X1");
                modelTemp->setHeaderData(1, Qt::Horizontal, "X2");
                modelTemp->setHeaderData(2, Qt::Horizontal, "X3");
                modelTemp->setHeaderData(3, Qt::Horizontal, "W11");
                modelTemp->setHeaderData(4, Qt::Horizontal, "W12");
                modelTemp->setHeaderData(5, Qt::Horizontal, "W13");
                modelTemp->setHeaderData(6, Qt::Horizontal, "W21");
                modelTemp->setHeaderData(7, Qt::Horizontal, "W22");
                modelTemp->setHeaderData(8, Qt::Horizontal, "W23");
                modelTemp->setHeaderData(9, Qt::Horizontal, "W31");
                modelTemp->setHeaderData(10, Qt::Horizontal, "W32");
                modelTemp->setHeaderData(11, Qt::Horizontal, "WB1");
                modelTemp->setHeaderData(12, Qt::Horizontal, "WB2");
                modelTemp->setHeaderData(13, Qt::Horizontal, "WB3");
                modelTemp->setHeaderData(14, Qt::Horizontal, "Y");
                modelTemp->setHeaderData(15, Qt::Horizontal, "Y2");
                modelTemp->setHeaderData(16, Qt::Horizontal, "Error Rate");

                models = new std::vector<std::vector<std::array<QString, 17>>>;

                if (ui->spinBox->maximum() < 2 && !checked)
                    ui->spinBox_2->setDisabled(true);
                else
                    ui->spinBox_2->setDisabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fillData(int row, MyNeuralNetwork &N)
{
    for (unsigned int i = 0; i < 17; ++i) {
        if (i < 3) {
            model->setData(model->index(row, int(i)), QString::number(N.getinOut()[i]));
            rowData[i] = QString::number(N.getinOut()[i]);
        } else if (i < 11 && i > 2) {
            model->setData(model->index(row, int(i)), QString::number(N.getWeights()[i - 3]));
            rowData[i] = QString::number(N.getWeights()[i - 3]);
        } else if (i < 14 && i > 10) {
            model->setData(model->index(row, int(i)), QString::number(N.getBias()[i - 11]));
            rowData[i] = QString::number(N.getBias()[i - 11]);
        } else if (i == 14) {
            model->setData(model->index(row, int(i)), QString::number(N.getinOut()[3]));
            rowData[i] = QString::number(N.getinOut()[3]);
        } else if (i == 15) {
            model->setData(model->index(row, int(i)), QString::number(N.getF()[2]));
            rowData[i] = QString::number(N.getF()[2]);
        } else {
            model->setData(model->index(row, int(i)), QString::number(N.getError()));
            rowData[i] = QString::number(N.getError());
        }
    }
    mod.push_back(rowData);
}

void MainWindow::fillDataLast(int row, MyNeuralNetwork &N)
{
    for (unsigned int i = 0; i < 17; ++i) {
        if (i < 3) {
            model->setData(model->index(row, int(i)), QString::number(N.getinOut()[i]));
        } else if (i < 11 && i > 2) {
            model->setData(model->index(row, int(i)), QString::number(N.getWeights()[i - 3]));
        } else if (i < 14 && i > 10) {
            model->setData(model->index(row, int(i)), QString::number(N.getBias()[i - 11]));
        } else if (i == 14) {
            model->setData(model->index(row, int(i)), QString::number(N.getinOut()[3]));
        } else if (i == 15) {
            model->setData(model->index(row, int(i)), QString::number(N.getF()[2]));
        } else {
            model->setData(model->index(row, int(i)), QString::number(N.getError()));
        }
    }
}

void MainWindow::start()
{
    for (int i = 0; i < max; ++i) {
        for (uint j = 0; j < iolist.size(); ++j) {
            iolist[j]->run();
            if (checked)
                fillData(int(j), *iolist[j]);
            else if (i + 1 == max)
                fillDataLast(int(j), *iolist[j]);
        }
        if (checked) {
            models->push_back(mod);
            mod.clear();
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
    ui->pushButton_4->setDisabled(true);
    model->removeRows(0, model->rowCount());
    ui->tableView_2->setModel(nullptr);
    selectionModel = ui->tableView->selectionModel();
    QModelIndexList indexes = selectionModel->selectedIndexes();
    iolist.clear();

    for (int i = 0; i < model1->rowCount(); ++i) {
        if (indexes.size() > 0) {
            for (auto &index : indexes) {
                if (index.column() == 0) {
                    if (index.row() != i) {
                        N[i]->setinOut(arr[i][0], arr[i][1], arr[i][2], arr[i][3]);
                        iolist.push_back(N[i]);
                    }
                }
            }
        } else {
            N[i]->setinOut(arr[i][0], arr[i][1], arr[i][2], arr[i][3]);
            iolist.push_back(N[i]);
        }
    }

    model->insertRows(0, int(iolist.size()));
    checked = ui->checkBox->checkState();
    max = ui->spinBox->value();

    //if (max > 100000)
    //    ui->spinBox_2->setMinimum(max - 100000);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    thread = QThread::create([&] { start(); });
    status->setText("Running...");
    timer->start();
    connect(thread, SIGNAL(finished()), this, SLOT(refreshTable()));
    thread->start();
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    if (arg1 > 2 && ui->checkBox->checkState())
        ui->spinBox_2->setEnabled(true);
    else
        ui->spinBox_2->setEnabled(false);
}

void MainWindow::on_pushButton_3_clicked()
{
    N[0]->resetWeights();
    models->clear();
    mod.clear();
    model->removeRows(0, model->rowCount());
    ui->pushButton_2->setDisabled(true);
}

void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    if (m_size > 1 && ui->checkBox->checkState()) {
        modelTemp->removeRows(0, modelTemp->rowCount());
        modelTemp->insertRows(0, model->rowCount());
        for (int i = 0; i < modelTemp->rowCount(); ++i) {
            for (int j = 0; j < modelTemp->columnCount(); ++j) {
                if (j < 3) {
                    modelTemp->setData(modelTemp->index(int(i), int(j)),
                                       models->at(arg1 - 1).at(i).at(j));
                } else if (j < 11 && j > 2) {
                    modelTemp->setData(modelTemp->index(int(i), int(j)),
                                       models->at(arg1 - 1).at(i).at(j));
                } else if (j < 14 && j > 10) {
                    modelTemp->setData(modelTemp->index(int(i), int(j)),
                                       models->at(arg1 - 1).at(i).at(j));
                } else if (j == 14) {
                    modelTemp->setData(modelTemp->index(int(i), int(j)),
                                       models->at(arg1 - 1).at(i).at(j));
                } else if (j == 15) {
                    modelTemp->setData(modelTemp->index(int(i), int(j)),
                                       models->at(arg1 - 1).at(i).at(j));
                } else {
                    modelTemp->setData(modelTemp->index(int(i), int(j)),
                                       models->at(arg1 - 1).at(i).at(j));
                }
            }
        }

        ui->tableView_2->setModel(modelTemp);
        ui->tableView_2->resizeColumnsToContents();
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->tableView->clearSelection();
    ui->pushButton_2->setText("Test");
    ui->pushButton_2->setDisabled(true);
}

void MainWindow::on_pushButton_2_clicked()
{
    selectionModel = ui->tableView->selectionModel();
    QModelIndexList indexes = selectionModel->selectedIndexes();
    mdl->removeRows(0, mdl->rowCount());
    mdl->insertRows(0, 17);

    N[idx]->setinOut(arr[idx][0], arr[idx][1], arr[idx][2], arr[idx][3]);
    N[idx]->test();

    mdl->setData(mdl->index(0, 0), "X1 X2 X3 / Y:");
    mdl->setData(mdl->index(1, 0), "W11 W12 W13:");
    mdl->setData(mdl->index(2, 0), "W21 W22 W23:");
    mdl->setData(mdl->index(3, 0), "W31 W32:");
    mdl->setData(mdl->index(4, 0), "WB1 WB2 WB3:");
    mdl->setData(mdl->index(5, 0), "Error:");
    mdl->setData(mdl->index(6, 0), "Result:");

    mdl->setData(mdl->index(0, 1),
                 QString::number(N[idx]->getinOut().at(0)) + " "
                     + QString::number(N[idx]->getinOut().at(1)) + " "
                     + QString::number(N[idx]->getinOut().at(2)) + "  "
                     + QString::number(N[idx]->getinOut().at(3)));
    mdl->setData(mdl->index(1, 1),
                 QString::number(N[idx]->getWeights().at(0)) + " "
                     + QString::number(N[idx]->getWeights().at(1)) + " "
                     + QString::number(N[idx]->getWeights().at(2)));
    mdl->setData(mdl->index(2, 1),
                 QString::number(N[idx]->getWeights().at(3)) + " "
                     + QString::number(N[idx]->getWeights().at(4)) + " "
                     + QString::number(N[idx]->getWeights().at(5)));
    mdl->setData(mdl->index(3, 1),
                 QString::number(N[idx]->getWeights().at(6)) + " "
                     + QString::number(N[idx]->getWeights().at(7)));
    mdl->setData(mdl->index(4, 1),
                 QString::number(N[idx]->getBias().at(0)) + " "
                     + QString::number(N[idx]->getBias().at(1)) + " "
                     + QString::number(N[idx]->getBias().at(2)));
    mdl->setData(mdl->index(5, 1), QString::number(N[idx]->getError()));
    mdl->setData(mdl->index(6, 1), QString::number(N[idx]->getF().at(2)));
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    idx = index.row();
    ui->pushButton_2->setText("Test");
    ui->pushButton_2->setText(ui->pushButton_2->text()
                              + " (Input: " + QString::number(index.row() + 1) + ")");
    if (model->rowCount() > 0) {
        ui->pushButton_2->setEnabled(true);
    }
}

void MainWindow::refreshTable()
{
    status->setText("Finished: " + QString::number(timer->elapsed()) + " msecs");
    m_size = models->size();
    if (iolist.size() < 8)
        ui->pushButton_2->setEnabled(true);
    else
        ui->pushButton_2->setEnabled(false);

    ui->pushButton_2->setDisabled(false);
    ui->pushButton_3->setDisabled(false);
    ui->pushButton_4->setDisabled(false);

    ui->tableView_2->setModel(model);
    ui->tableView_2->resizeColumnsToContents();

    if (checked) {
        ui->spinBox_2->setMaximum(max);
        ui->spinBox_2->setValue(max);
    }
    QApplication::restoreOverrideCursor();
}

void MainWindow::on_checkBox_toggled(bool checked)
{
    ui->spinBox_2->setEnabled(checked);
    //    if(checked)
    //        ui->tableView_2->setModel(model);
    //    else
    //        ui->tableView_2->setModel(nullptr);
}
