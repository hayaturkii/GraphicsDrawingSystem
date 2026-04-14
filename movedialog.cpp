#include "movedialog.h"
#include "ui_movedialog.h"

moveDialog::moveDialog(QWidget *parent) : QDialog(parent), ui(new Ui::moveDialog)
{
    ui->setupUi(this);
}

moveDialog::~moveDialog()
{
    delete ui;
}

double moveDialog::getDx() const
{
    return ui->dxSpinBox->value();
}

double moveDialog::getDy() const
{
    return ui->dySpinBox->value();
}

void moveDialog::on_okButton_clicked()
{
    accept();
}

void moveDialog::on_cancelButton_clicked()
{
    reject();
}

