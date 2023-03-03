#include "musicinput.h"
#include "music.h"

#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QLabel>

MusicInput::MusicInput() :
    music(new Music),
    spnRating(new QSpinBox),
    edtArtist(new QLineEdit),
    edtAlbum(new QLineEdit),
    edtSongName(new QLineEdit),
    btnSubmit(new QPushButton("Submit")),
    btnClose(new QPushButton("Close"))
{
    setupGUI();

    connect(btnSubmit, &QPushButton::clicked, this, &MusicInput::processInput);
    connect(btnSubmit, &QPushButton::clicked, this, &MusicInput::accept);
    connect(btnClose, &QPushButton::clicked, this, &QWidget::close);
    connect(btnClose, &QPushButton::clicked, this, &MusicInput::reject);

    setWindowTitle("Add Song");

}

MusicInput::~MusicInput()
{

}

Music *MusicInput::getMusic() const
{
    return music;
}

void MusicInput::processInput()
{
    music->setArtist(edtArtist->text());
    music->setAlbum(edtAlbum->text());
    music->setName(edtSongName->text());
    music->setRating(spnRating->value());
}

void MusicInput::setupGUI()
{
    QVBoxLayout *layout(new QVBoxLayout(this));

    QLabel *lblArist(new QLabel("Artist"));
    QLabel *lblAlbum(new QLabel("Album"));
    QLabel *lblSongName(new QLabel("Song Name"));
    QLabel *lblRating(new QLabel("Rating"));

    spnRating->setMinimum(0);
    spnRating->setMaximum(10);

    layout->addWidget(lblArist);
    layout->addWidget(edtArtist);
    layout->addWidget(lblAlbum);
    layout->addWidget(edtAlbum);
    layout->addWidget(lblSongName);
    layout->addWidget(edtSongName);
    layout->addWidget(lblRating);
    layout->addWidget(spnRating);
    layout->addWidget(btnSubmit);
    layout->addWidget(btnClose);
}
