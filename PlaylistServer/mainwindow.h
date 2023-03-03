#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QXmlStreamReader>

class QPushButton;
class QLabel;
class QStandardItemModel;
class QTableView;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startListening();
    void handleConnection();
    void readyRead();

private:
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;
    QStandardItemModel *model;
    QXmlStreamReader reader;

    QPushButton *buttonStartListening;
    QLabel *labelStatus;
    QTableView *view;

    void setModelHeadings();
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
