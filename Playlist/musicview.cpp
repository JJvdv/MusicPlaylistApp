#include "musicview.h"
#include "musicinput.h"
#include "listwriter.h"
#include "listreader.h"
#include "musictablemodel.h"

#include <QTableView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QCloseEvent>
#include <QMessageBox>
#include <QTextStream>
#include <QTcpSocket>
#include <QDomDocument>

MusicView::MusicView(QWidget *parent) :
    QWidget(parent),
    model(new MusicTableModel),
    view(new QTableView),
    btnAddMusic(new QPushButton("Add Music")),
    btnRead(new QPushButton("Read")),
    btnWrite(new QPushButton("Write")),
    btnExit(new QPushButton("Exit")),
    btnWriteServer(new QPushButton("Write To Server"))
{
    setupGUI();

    connect(btnAddMusic, &QPushButton::clicked, this, &MusicView::addMusic);
    connect(btnRead, &QPushButton::clicked, this, &MusicView::readList);
    connect(btnWrite, &QPushButton::clicked, this, &MusicView::writeList);
    connect(btnExit, SIGNAL(clicked()), this, SLOT(close()));
    connect(btnWriteServer, &QPushButton::clicked, this, &MusicView::writeToServer);

    setWindowTitle("Playlist");
    setMinimumSize(600, 300);

}

void MusicView::closeEvent(QCloseEvent *event)
{
    int response;

    response = QMessageBox::warning(this, "Exit", "Are you sure you want to Exit ?", QMessageBox::Yes | QMessageBox::No);

    if (response == QMessageBox::Yes)
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }

}

void MusicView::addMusic()
{
    MusicInput newMusic;
    QTextStream cout(stdout);

    newMusic.exec();

    if (newMusic.result() == QDialog::Accepted)
    {
        model->addMusic(newMusic.getMusic());
    }
    else
    {
        cout << "Dialog close - no data available!" << endl;
    }
}

//TODO: Change QTextStream to QMessageBox
void MusicView::readList()
{
    QList<Music*> list;
    ListReader lr;
    QTextStream cout(stdout);

    list = lr.read();

    model->clear();

    foreach(Music* m, list)
    {
        model->addMusic(m);
    }

    view->resizeColumnsToContents();

    cout << "Playlist read from file!" << endl;
}

//TODO: Change Prompt message to QMessageBox
void MusicView::writeList()
{
    QString prompt("Playlist written to file!");
    ListWriter lw(model);
    QTextStream cout(stdout);

    if(!lw.write())
    {
        prompt = "Error: Playlist not written to file!";
    }

    cout << prompt << endl;
}

//TODO: Add Delegates?
void MusicView::setupGUI()
{
    QVBoxLayout *layout(new QVBoxLayout(this));
    layout->addWidget(view);
    layout->addWidget(btnAddMusic);
    layout->addWidget(btnRead);
    layout->addWidget(btnWrite);
    layout->addWidget(btnWriteServer);
    layout->addWidget(btnExit);

    view->resizeColumnsToContents();
    view->setModel(model);

}

void MusicView::writeToServer()
{
    QDomDocument doc;
    QTcpSocket *tcpSocket(new QTcpSocket(this));
    QTextStream cout(stdout);

    QDomElement root = doc.createElement("playlist");

    doc.appendChild(root);

    for(int i = 0; i < model->rowCount(QModelIndex()); i++)
    {
        QDomElement aElem = doc.createElement("artist");
        QDomText aText = doc.createTextNode(model->data(model->index(i, 0), Qt::DisplayRole).toString());
        root.appendChild(aElem);
        aElem.appendChild(aText);

        QDomElement alElem = doc.createElement("album");
        QDomText alText = doc.createTextNode(model->data(model->index(i, 1), Qt::DisplayRole).toString());
        root.appendChild(alElem);
        alElem.appendChild(alText);

        QDomElement sElem = doc.createElement("songname");
        QDomText sText = doc.createTextNode(model->data(model->index(i, 2), Qt::DisplayRole).toString());
        root.appendChild(sElem);
        sElem.appendChild(sText);

        QDomElement rElem = doc.createElement("rating");
        QDomText rText = doc.createTextNode(QString::number(model->data(model->index(i, 3), Qt::DisplayRole).toInt()));
        root.appendChild(rElem);
        rElem.appendChild(rText);
    }

    //TODO: CHeck why only last element is sent through to server
    tcpSocket->connectToHost("127.0.0.1", 6164);

    if (tcpSocket->waitForConnected())
    {
        QString data = doc.toString();

        emit xmlText(data);

        tcpSocket->write(data.toLatin1());
        tcpSocket->waitForBytesWritten(10000);
        tcpSocket->close();

        cout << "Written to Server Successfully!!" << endl;
    }
    else
    {
        emit linkError("Could not connect to host!");
    }

    emit finished();
}
