#ifndef MUSICVIEW_H
#define MUSICVIEW_H

#include <QWidget>
#include <QTcpSocket>

class MusicList;
class QPushButton;
class QTableView;
class MusicTableModel;

class MusicView :  public QWidget
{
    Q_OBJECT
public:
    explicit MusicView(QWidget *parent = nullptr);

     void closeEvent(QCloseEvent *event);

private slots:
    void addMusic();
    void readList();
    void writeList();
    void writeToServer();

signals:
    void xmlText(QString);
    void linkError(QString msg);
    void finished();

private:
    void setupGUI();

    MusicTableModel *model;

    QTableView *view;

    QPushButton *btnAddMusic;
    QPushButton *btnRead;
    QPushButton *btnWrite;
    QPushButton *btnExit;
    QPushButton *btnWriteServer;
};

#endif // MUSICVIEW_H
