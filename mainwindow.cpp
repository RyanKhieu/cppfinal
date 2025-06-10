#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QDoubleValidator>
#include <QMessageBox>
#include <QFileInfo>
#include <QDebug>
#include <QRandomGenerator>
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CandyBudgeting)
{
    ui->setupUi(this);

    // currency validation
    ui->lineEdit_2->setValidator(new QDoubleValidator(0, 1e9, 2, this));
    ui->lineEdit_3->setValidator(new QDoubleValidator(0, 1e9, 2, this));

    // load balance
    loadBalance();
    updateBalance();

    // connect buttons
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::addClicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::subtractClicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::tryClicked);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadBalance()
{
    // load balance.txt
    QFile file(balanceFile);
    qDebug() << "Loading balance.txt at:" << QFileInfo(balanceFile).absoluteFilePath();

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
    qDebug() << "Saving balance.txt at:" << QFileInfo(balanceFile).absoluteFilePath();

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

void MainWindow::tryClicked()
{
    bool ok = false;
    double amount = ui->lineEdit_3->text().toDouble(&ok);

    if (!ok) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid candy amount.");
        return;
    }

    balance -= amount;
    updateBalance();
    saveBalance();
    QString emojis[4] = {"🍬", "🍭", "🍫", "🍡"};
    ui->lineEdit_4->clear();
    for (int i = 0; i < 3; i++) {
        int val = QRandomGenerator::global()->bounded(4);
        QString currentText = ui->lineEdit_4->text();
        currentText += emojis[val];
        ui->lineEdit_4->setText(currentText);
        QApplication::processEvents();
        QThread::msleep(750);
    }
    QString currentText = ui->lineEdit_4->text();
    if (currentText == "🍬🍬🍬") {
        balance += amount * 2;
    }
    else if (currentText == "🍭🍭🍭") {
        balance += amount * 5;
    }
    else if (currentText == "🍫🍫🍫") {
        balance += amount * 10;
    }
    else if (currentText == "🍡🍡🍡") {
        balance += amount * 100;
    }

    updateBalance();
    saveBalance();
}
