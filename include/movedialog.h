#ifndef MOVEDIALOG_H
#define MOVEDIALOG_H

#include <QDialog>

namespace Ui { class moveDialog; }

class moveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit moveDialog(QWidget *parent = nullptr);
    ~moveDialog();
    double getDx() const;
    double getDy() const;

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::moveDialog *ui;
};

#endif // MOVEDIALOG_H
