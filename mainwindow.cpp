#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QDoubleValidator>
#include <QMessageBox>
#include <QFileInfo>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CandyBudgeting)
{
    ui->setupUi(this);

    // Currency validation
    ui->lineEdit_2->setValidator(new QDoubleValidator(0, 1e9, 2, this));

    // Load balance
    loadBalance();
    updateBalance();

    // Connect buttons
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::addClicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::subtractClicked);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadBalance()
{
    // load balance.txt
    QFile file(balanceFile);
    qDebug() << "Saving/loading balance.txt at:" << QFileInfo(balanceFile).absoluteFilePath();
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // open text stream in from file
        QTextStream in(&file);
        // read balance from file
        in >> balance;
        file.close();
    }
}

void MainWindow::saveBalance()
{
    // load balance.txt
    QFile file(balanceFile);
    qDebug() << "Saving/loading balance.txt at:" << QFileInfo(balanceFile).absoluteFilePath();
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // open text stream out to file
        QTextStream out(&file);
        // write balance to file
        out << balance;
        file.close();
    }
}

void MainWindow::updateBalance()
{
    ui->lineEdit->setText(QString::number(balance, 'f', 2));
}

void MainWindow::addClicked()
{
    bool ok = false;
    double amount = ui->lineEdit_2->text().toDouble(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid candy amount.");
        return;
    }
    balance += amount;
    updateBalance();
    saveBalance();
    ui->lineEdit_2->clear();
}

void MainWindow::subtractClicked()
{
    bool ok = false;
    double amount = ui->lineEdit_2->text().toDouble(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid candy amount.");
        return;
    }
    balance -= amount;
    updateBalance();
    saveBalance();
    ui->lineEdit_2->clear();
}
