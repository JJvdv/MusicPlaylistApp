#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QObject>

class QPushButton;
class QLineEdit;

class Login : public QDialog
{
    Q_OBJECT
public:
    Login();

private slots:
    void processInput();

private:
    void setupGUI();

    QString m_username, m_password;

    QPushButton *btnProcess;

    QLineEdit *edtUsername;
    QLineEdit *edtPassword;
};

#endif // LOGIN_H
