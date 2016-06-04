#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QClipboard>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

template<int D> int getDigit(long long val)
{
    return getDigit<D-1>(val/10);
}

template<>      int getDigit<1>(long long val)
{
    return val % 10;
}

void MainWindow::on_pushButton_clicked()
{
//    std::cout << "CLICKED GENERATE" << std::endl;
//    std::cout.flush();
    // See http://geekswithblogs.net/willemf/archive/2005/10/30/58561.aspx
    // See http://xml-fx.com/services/saidvalidator/testpage.aspx
    int year = ui->spnYear->value();
    long long month = ui->spnMonth->value();
    long long day = ui->spnDay->value();
    int genderOffset = qrand() % ((4 + 1) - 0) + 0;
    int gender = genderOffset; // 0-4 is female
    if (ui->rdbMale->isChecked()) {
        gender = genderOffset + 5; // 5-9 is male
    }
    int random3 = qrand() % ((999 + 1) - 0) + 0;;
    int country = 0; // 0 is SA
    int thing = qrand() % ((9 + 1) - 8) + 8; // can be any thing, but usualy 8 or 9
    // Calculate the checksum
    int checksum = 0;
    long long tempID = (year    * 100000000000)
                + (month   * 1000000000)
                + (day     * 10000000)
                + (gender  * 1000000)
                + (random3 * 1000)
                + (country * 100)
                + (thing   * 10);

//    std::cout << "tempID = " << tempID << std::endl;
//    std::cout.flush();
    // Checksum Step 1: Add all the digits in the odd positions (excluding last digit)
    int total1 = getDigit<3>(tempID)
                + getDigit<5>(tempID)
                + getDigit<7>(tempID)
                + getDigit<9>(tempID)
                + getDigit<11>(tempID)
                + getDigit<13>(tempID);
//    std::cout << "total1 = " << total1 << std::endl;
//    std::cout.flush();
    // Checksum Step 2: Concatinate the even positions into a number and multiply the it by 2
    int total2 = (getDigit<2>(tempID)
                  + getDigit<4>(tempID)  * 10
                  + getDigit<6>(tempID)  * 100
                  + getDigit<8>(tempID)  * 1000
                  + getDigit<10>(tempID) * 10000
                  + getDigit<12>(tempID) * 100000
                  ) * 2;
//    std::cout << "total2 = " << total2 << "      [total2 / 2 = " << (total2/2) << "]" << std::endl;
//    std::cout.flush();
    // Checksum Step 3: Add the digits of the result in step 2 above
    int total3 = 0;
    int tempTotal2 = total2;
    while (tempTotal2 > 0) {
        int digit = tempTotal2 % 10;
        total3 = total3 + digit;
        tempTotal2 = tempTotal2 / 10;
    }
//    std::cout << "total3 = " << total3 << std::endl;
//    std::cout.flush();
    // Checksum Step 4: Add the numbers from step 1 and step 3
    int total4 = total1 + total3;
//    std::cout << "total4 = " << total4 << std::endl;
//    std::cout.flush();
    // Checksum Step 5: If the answer in step 4 is 10 then use 0, other wise subtract the last digit of the result from 10 and use that number
    checksum = 10 - (total4 % 10);
    if (checksum == 10) {
        checksum = 0;
    }
//    std::cout << "checksum = " << checksum << std::endl;
//    std::cout.flush();
    // Build the final value
    long long finalID = tempID + checksum;
    // Print result
//    std::cout << "FINAL ID = " << finalID << std::endl;
//    std::cout.flush();
    // Update the UI
    ui->txtID->setText(QString::number(finalID));
//    std::cout.flush();
}

void MainWindow::on_btnCopy_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(ui->txtID->text());
}
