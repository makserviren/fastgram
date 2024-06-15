#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegularExpression>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setText("+"); // Set default text for the line edit
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::checkPhoneNumber(const QString &num) {
    // Regular expression patterns for different countries
    QStringList patterns;

    // Patterns for Ukraine
    patterns << "^\\+380\\d{9}$" // Format +380xxxxxxxxx
             << "^\\+38\\(\\d{3}\\)\\d{7}$"; // Format +38(xxx)xxxxxxx

    // Patterns for Russia
    patterns << "^\\+7\\d{10}$" // Format +7xxxxxxxxxx
             << "^\\+7 \\d{3} \\d{3}-\\d{2}-\\d{2}$"; // Format +7 xxx xxx-xx-xx

    // Patterns for USA
    patterns << "^\\+1(\\d{10})$" // Format +1xxxxxxxxxx
             << "^\\+1 \\(\\d{3}\\) \\d{3}-\\d{4}$"; // Format +1 (xxx) xxx-xxxx

    // Patterns for Kazakhstan
    patterns << "^\\+7\\d{9}$"; // Format +7xxxxxxxxx

    // Check each phone number format
    foreach (const QString &pattern, patterns) {
        QRegularExpression nv(pattern);
        if (nv.match(num).hasMatch()) {
            return true; // If the number matches any of the formats, return true
        }
    }

    // If the number doesn't match any of the formats, show an error message
    QMessageBox::critical(this, "Error", "Please insert a valid phone number");
    return false;
}

void MainWindow::on_pushButton_2_clicked()
{
    QString phoneNumber = ui->lineEdit->text(); // Get the entered phone number from the QLineEdit
    bool isValidPhoneNumber = checkPhoneNumber(phoneNumber); // Call the function to check the phone number
    if (!isValidPhoneNumber) {
        // If the number doesn't match the correct format, show an error message
        QMessageBox::critical(this, "Error", "Please insert a valid phone number");
        // Clear the phone number input field and set focus to it
        ui->lineEdit->clear();
        ui->lineEdit->setText("+"); // Set default text for the line edit
        ui->lineEdit->setFocus();
        return; // Stop the method execution since an invalid number was entered
    }
    // If the number matches the correct format, you can continue with other actions here
}
