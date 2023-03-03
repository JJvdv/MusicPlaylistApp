#include "mainwindow.h"

#include <QMessageBox>
#include <QTcpSocket>
#include <QRegularExpression>
#include <QtWidgets>
#include <QStandardItemModel>
#include <QTableView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    tcpServer(nullptr),
    tcpSocket(nullptr),
    model(new QStandardItemModel(this)),
    buttonStartListening(new QPushButton("Start listening")),
    labelStatus(new QLabel("Status")),
    view(new QTableView)
{
    QGridLayout *layout(new QGridLayout());
    layout->addWidget(buttonStartListening, 0, 0);
    layout->addWidget(labelStatus, 0, 1);
    layout->addWidget(view, 1, 0, 1, 2);

    QWidget *widget{new QWidget()};
    widget->setLayout(layout);
    setCentralWidget(widget);
    setWindowTitle("Container server");
    setMinimumSize(800, 100);

    setModelHeadings();
    adjustSize();

    view->setModel(model);
    view->setSortingEnabled(true);
    view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // First Part
    connect(buttonStartListening, &QPushButton::clicked, this, &MainWindow::startListening);
}

MainWindow::~MainWindow()
{
    if (tcpServer!=nullptr)
    {
        tcpServer->close();
        tcpServer->deleteLater();
    }

    if (tcpSocket!=nullptr)
    {
        tcpSocket->close();
        tcpSocket->deleteLater();
    }
}

void MainWindow::startListening()
{
    tcpServer = new QTcpServer(this);

    // Second Part ?
    if (!tcpServer->listen(QHostAddress::Any, 6164))
    {
        QMessageBox::critical(this, "Playlist Server", QString("Unable to start the server: %1.").arg(tcpServer->errorString()));
        close();
        return;
    }

    labelStatus->setText("Listening on port 6164");

    // Third Part
    connect(tcpServer, &QTcpServer::newConnection, this, &MainWindow::handleConnection);
}

void MainWindow::handleConnection()
{
    // Fourth Part
    tcpSocket = tcpServer->nextPendingConnection();

    // Fifth Part
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}


void MainWindow::readyRead()
{
    model->clear();
    setModelHeadings();

    // Sixth Part
    QByteArray data(tcpSocket->readAll());

    reader.addData(data);

    bool collect(false);
    QStringList detail;

    while (!reader.atEnd())
    {
        QXmlStreamReader::TokenType tt(reader.readNext());
        switch (tt)
        {
            case QXmlStreamReader::StartElement:
            {

                if (reader.name().toString()=="playlist")
                {
                    detail << reader.name().toString();
                }
                else if (reader.name().toString()=="artist" || reader.name().toString()=="album" || reader.name().toString()=="songname"  || reader.name().toString()=="rating")
                {
                    detail << reader.name().toString();
                    collect=true;
                }
                break;
            }

            case QXmlStreamReader::Characters:
            {
                if (collect)
                    detail << reader.text().toString();
                break;
            }

            case QXmlStreamReader::EndElement:
            {
                if (reader.name().toString()=="artist" || reader.name().toString()=="album" || reader.name().toString()=="songname"  || reader.name().toString()=="rating")
                    collect=false;
                else if (reader.name().toString()=="playlist")
                {
                    QList<QStandardItem*> row;

                    QStandardItem *itemArtist(nullptr);
                    QStandardItem *itemAlbum(nullptr);
                    QStandardItem *itemSongName(nullptr);
                    QStandardItem *itemRating(nullptr);

                    for (int i=1; i< detail.size(); i+=2)
                    {
                        if (detail.at(i) == "artist")
                            itemArtist = new QStandardItem(detail.at(i+1));
                        else if (detail.at(i) == "album")
                            itemAlbum = new QStandardItem(detail.at(i+1));
                        else if (detail.at(i) == "songname")
                            itemSongName = new QStandardItem(detail.at(i+1));
                        else if (detail.at(i) == "rating")
                            itemRating = new QStandardItem(detail.at(i+1));
                    }

                    if (detail.at(0) == "playlist")
                        row << itemArtist << itemAlbum << itemSongName << itemRating;

                    model->appendRow(row);
                    detail.clear();
                }
                break;
            }
            default:
                break;
        }
    }
    reader.clear();
}

void MainWindow::setModelHeadings()
{
    QStringList headerRow;
    headerRow.append("Artist");
    headerRow.append("Album");
    headerRow.append("Song Name");
    headerRow.append("Rating");

    model->setHorizontalHeaderLabels(headerRow);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int answer;

    answer = QMessageBox::warning(this, "Exit", "Are you sure you want to exit?", QMessageBox::Yes | QMessageBox::No);

    if (answer == QMessageBox::Yes)
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}
