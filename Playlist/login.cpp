#include "login.h"

#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QRegularExpression>
#include <QVBoxLayout>
#include <QMessageBox>

Login::Login() :
    btnProcess(new QPushButton("Login")),
    edtUsername(new QLineEdit),
    edtPassword(new QLineEdit)
{
    setupGUI();

    connect(btnProcess, &QPushButton::clicked, this, &Login::processInput);

    setWindowTitle("Login Screen");
}

// Add better Regular Expression for password
void Login::processInput()
{
    m_username = edtUsername->text();
    m_password = edtPassword->text();

    QRegularExpression reUsername("[A][d][m][i][n]");
    QRegularExpression rePassword("[A][d][m][i][n][@][1]");

    QRegularExpressionMatch uMatch = reUsername.match(m_username);
    QRegularExpressionMatch pMatch = rePassword.match(m_password);

    bool hasMatch = uMatch.hasMatch() && pMatch.hasMatch();

    if(hasMatch == true)
    {
        accept();

        QMessageBox::information(this, "Credentials", "Successfully logged in!");
    }
    else
    {
        QMessageBox::critical(this, "Credentials", "Username or password is incorrect");
        reject();
    }

}

void Login::setupGUI()
{
    QVBoxLayout *layout(new QVBoxLayout(this));

    QLabel *lblUsername(new QLabel("Username"));
    QLabel *lblPassword(new QLabel("Password"));

    edtUsername->setEchoMode(QLineEdit::Password);
    edtPassword->setEchoMode(QLineEdit::Password);

    layout->addWidget(lblUsername);
    layout->addWidget(edtUsername);
    layout->addWidget(lblPassword);
    layout->addWidget(edtPassword);
    layout->addWidget(btnProcess);

}
