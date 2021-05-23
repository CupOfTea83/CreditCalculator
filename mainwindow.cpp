#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLineEdit>
#include <QPushButton>
#include <QPixmap>
#include <QPalette>
#include <QLocale>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), m_dobVal(0, 1000000000000, 2, this), m_intVal(0, 500, this)
{
       ui->setupUi(this);

       QPixmap backimg(":/rec/img/blue_diagonal_stripes2560x1600.jpg");
       backimg.scaled(this->size(), Qt::KeepAspectRatio);
       QPalette palet;
       palet.setBrush(QPalette::Background, backimg);
       this->setPalette(palet);

       ui->rubLineEdit->installEventFilter(this);
       ui->percentLineEdit->installEventFilter(this);
       ui->monLineEdit->installEventFilter(this);

       ui->monLineEdit->setValidator(&m_intVal);

       QLocale locale(QLocale::English);

       m_dobVal.setNotation(QDoubleValidator::StandardNotation);
       m_dobVal.setLocale(locale);
       ui->rubLineEdit->setValidator(&m_dobVal);
       ui->percentLineEdit->setValidator(&m_dobVal);

       connect(ui->numButton1, SIGNAL(clicked()), this, SLOT(digit_numbers()));
       connect(ui->numButton2, SIGNAL(clicked()), this, SLOT(digit_numbers()));
       connect(ui->numButton3, SIGNAL(clicked()), this, SLOT(digit_numbers()));
       connect(ui->numButton4, SIGNAL(clicked()), this, SLOT(digit_numbers()));
       connect(ui->numButton5, SIGNAL(clicked()), this, SLOT(digit_numbers()));
       connect(ui->numButton6, SIGNAL(clicked()), this, SLOT(digit_numbers()));
       connect(ui->numButton7, SIGNAL(clicked()), this, SLOT(digit_numbers()));
       connect(ui->numButton8, SIGNAL(clicked()), this, SLOT(digit_numbers()));
       connect(ui->numButton9, SIGNAL(clicked()), this, SLOT(digit_numbers()));
       connect(ui->numButton0, SIGNAL(clicked()), this, SLOT(digit_numbers()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QLineEdit *focused = nullptr;

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->rubLineEdit && event->type() == QEvent::FocusOut)
        focused = ui->rubLineEdit;
    else if(watched == ui->percentLineEdit && event->type() == QEvent::FocusOut)
        focused = ui->percentLineEdit;
    else if(watched == ui->monLineEdit && event->type() == QEvent::FocusOut)
        focused = ui->monLineEdit;

    return false;
}


void MainWindow::digit_numbers()
{
    QPushButton *button = (QPushButton *) sender();
    if(focused != nullptr)
    {
        if(focused == ui->monLineEdit)
        {
            int num = (focused->text() + button->text()).toDouble();
            QString out = QString::number(num, 'g', 12);
            focused -> setText(out);
        }else if(focused->text().contains(".") && button->text() == "0")
        {
            focused->setText(focused->text() + button->text());
        }else if(focused == ui->rubLineEdit)
        {
            double num = floor((focused->text() + button->text()).toDouble()*100)/100;
            QString out = QString::number(num, 'g', 12);
            focused -> setText(out);

        }else
        {
            double num = (focused->text() + button->text()).toDouble();
            QString out = QString::number(num, 'g', 12);
            focused -> setText(out);
        }
    }

    oldRub = ui->rubLineEdit->text();
    oldMon = ui->monLineEdit->text();
    oldPerc = ui->percentLineEdit->text();
}



void MainWindow::on_numButtonDot_clicked()
{
    if(!(focused->text().contains(".")))
        focused->setText(focused->text() + ".");
}

void MainWindow::on_calculateButton_clicked()
{
    if(!((ui->rubLineEdit->text() == "") || (ui->monLineEdit->text() == "") || (ui->percentLineEdit->text() == "")))
    {
    double lend;
    double mon;
    double perc;

    lend = (ui->rubLineEdit->text()).toDouble();
    mon = (ui->monLineEdit->text()).toDouble();
    perc = (ui->percentLineEdit->text()).toDouble();

    if(!((lend == 0) || (mon == 0) || (perc == 0)))
    {

        double monpay;
        double overpay;
        double sum;

        sum = round((lend + (lend*(perc / 100) * (mon / 12)))*100)/100;
        overpay = round((sum - lend)*100)/100;
        monpay = round((sum / mon)*100)/100;

        ui->monpayLabel->setText(QString::number(monpay, 'g', 12));
        ui->sumLabel->setText(QString::number(sum, 'g', 12));
        ui->overpayLabel->setText(QString::number(overpay, 'g', 12));
    }
    }
}

void MainWindow::on_resetButton_clicked()
{
    ui->rubLineEdit->setText("");
    ui->monLineEdit->setText("");
    ui->percentLineEdit->setText("");

    ui->monpayLabel->setText("");
    ui->sumLabel->setText("");
    ui->overpayLabel->setText("");
}

void MainWindow::on_cancelButton_clicked()
{
    ui->rubLineEdit->setText(oldRub);
    ui->monLineEdit->setText(oldMon);
    ui->percentLineEdit->setText(oldPerc);

    on_calculateButton_clicked();
}

void MainWindow::on_rubLineEdit_editingFinished()
{
    oldRub = ui->rubLineEdit->text();
}

void MainWindow::on_percentLineEdit_editingFinished()
{
    oldPerc = ui->percentLineEdit->text();
}

void MainWindow::on_monLineEdit_editingFinished()
{
    oldMon = ui->monLineEdit->text();
}

void MainWindow::on_pushButton_clicked()
{
    QString oldStr = focused->text();
    oldStr.chop(1);
    focused->setText(oldStr);
}
