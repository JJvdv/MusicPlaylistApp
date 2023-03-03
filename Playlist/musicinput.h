#ifndef MUSICINPUT_H
#define MUSICINPUT_H

#include <QDialog>
#include <QObject>

class QPushButton;
class QLineEdit;
class QSpinBox;
class Music;


class MusicInput : public QDialog
{
    Q_OBJECT
public:
    MusicInput();
    ~MusicInput();

    Music* getMusic() const;

private slots:
    void processInput();

private:
    void setupGUI();
    Music *music;

    QSpinBox *spnRating;

    QLineEdit *edtArtist;
    QLineEdit *edtAlbum;
    QLineEdit *edtSongName;

    QPushButton *btnSubmit;
    QPushButton *btnClose;


};

#endif // MUSICINPUT_H
