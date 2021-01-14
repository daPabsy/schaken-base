#include "mainwindow.h"
#include "SchaakStuk.h"
#include <QMessageBox>
#include <QtWidgets>
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    scene = new ChessBoard;
    QGraphicsView *view = new QGraphicsView(scene);
    setCentralWidget(view);
    g.setStartBord(); // zet alle schaakstukken op hun startpositie
    update(); // weergeeft de huige staat van het spel

    connect(scene,SIGNAL(clicked(int,int)),this,SLOT(clicked(int,int)));

    createActions();
    createMenus();
}


// Deze functie wordt opgeroepen telkens er op het schaakbord
// geklikt wordt. x,y geeft de positie aan waar er geklikt
// werd; r is de 0-based rij, k de 0-based kolom
void MainWindow::clicked(int r, int k) {
    // Wat hier staat is slechts een voorbeeldje dat wordt afgespeeld ter illustratie.
    // Jouw code zal er helemaal anders uitzien en zal enkel de aanpassing in de spelpositie maken en er voor
    // zorgen dat de visualisatie (al dan niet via update) aangepast wordt.

    scene->removeAllMarking(); // Alle markering wordt ongedaan gemaakt

    if ( g.getMoving() == nullptr ) { // Er is nog GEEN SchaakStuk aangeklikt
        if ( g.getPiece(r, k) == nullptr ) {
            cout << "Select a valid piece!" << endl;
        }
        else if ( g.getPiece(r, k)->getKleur() != g.getTurnMove() ) {
            cout << "Seleect a piece of your color!" << endl;
        }
        else {
            // Volgende keer dat er geklikt wordt kan er herkend worden of er reeds
            // een SchaakStuk werd aangeklikt
            g.setMovingAndPieceToMove(true, g.getPiece(r, k));
            scene->setTileSelect(r, k, true); // Markeert het SchaakStuk dat verplaatst moet worden
            if ( display_moves->isChecked() ) { // Geldige zetten laten zien?
                for( const pair<int, int> & i : g.getPiece(r, k)->geldige_zetten(g) ) {
                    scene->setTileFocus(i.first, i.second, true); // Markeert de mogelijke zetten
                }
            }
            cout << "Selected a piece!" << endl;
        }
    }
    else { // Er is reeds een SchaakStuk aangeklikt
        pair<int, int> moveTo; // Positie naar waar verplaatst moet worden
        moveTo.first = r;
        moveTo.second = k;
        if ( g.move(g.getMoving(), moveTo) ) {
            scene->clearBoard(); // Clear chessBoard
            update(); // Maak chessBoard opnieuw
        }
        if ( g.schaak(g.getTurnMove()) ) { // MessageBox wanneer tegenstander je schaak heeft gezet
            QMessageBox checkBox;
            checkBox.setWindowTitle("Pablo's Chess Simulator");
            checkBox.setText(QString("Schaak!"));
            checkBox.exec();
        }
    }


//    if (display_kills->isChecked()) {
//        // Markeer de stukken die je kan slaan
//        scene->setPieceThreat(3,0,true);
//        scene->setPieceThreat(3,3,true);
//    }
//    if (display_threats->isChecked()) {
//        // Markeer jouw bedreigde stukken
//        scene->setPieceThreat(2,4,true);
//        scene->setPieceThreat(1,1,true);
//    }
//
//    QMessageBox box1;
//    box1.setText(QString("Illustratie voor click; zwart is aan de beurt"));
//    box1.exec();
//
//    scene->removeAllPieceThreats();  // Eens een stuk gekozen is, worden alle bedreigde stukken niete langer gemarkeerd
//    scene->setTileSelect(2,4,true);  // De geselecteerde positie wordt steeds gemarkeerd
//    if (display_moves->isChecked()) {
//        // Geef de mogelijke zetten weer
//        scene->setTileFocus(3,3,true);
//        scene->setTileFocus(3,4,true);
//    }
//
//    box1.setText(QString("Illustratie na click; zwart kiest doelpositie"));
//    box1.exec();
//    scene->clearBoard();
//    scene->removeAllMarking();
//
//    scene->setItem(3,0,P->piece());
//    scene->setItem(1,1,p1->piece());
//    scene->setItem(0,3,Q->piece());
//    scene->setItem(0,4,K->piece());
//    scene->setItem(2,7,L->piece());
//    scene->setItem(5,3,Kw->piece());
//    scene->setItem(3,3,p2->piece());
//
//    if (display_kills->isChecked()) {
//        scene->setPieceThreat(2,4,true);
//        scene->setPieceThreat(1,1,true);
//    }
//    if (display_threats->isChecked()) {
//        scene->setPieceThreat(3,0,true);
//    }
//
//
//    box1.setText(QString("Illustratie na doelpositie gekozen is; nu is wit aan de beurt"));
//    box1.exec();
//
//    scene->removeAllPieceThreats();
//
//    scene->setTileSelect(2,7,true);
//    if (display_moves->isChecked()) {
//        for (int r=0;r<8;r++) {
//            if (r==2) continue;
//            int c=7-abs(r-2);
//            scene->setTileFocus(r,c,true);
//        }
//        if (display_threats->isChecked()) {
//            scene->setTileThreat(0,5,true);
//            scene->setTileThreat(3,6,true);
//            scene->setTileThreat(5,4,true);
//            scene->setTileThreat(6,3,true);
//        }
//    }
//
//    box1.setText(QString("Wit stuk geselecteerd; wit moet nu een doelpositie kiezen"));
//    box1.exec();
//    scene->removeAllMarking();
//    // etc. etc. ...
}

void MainWindow::newGame()
{}

void MainWindow::save() {
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save game"), "",
                                                    tr("Chess File (*.chs);;All Files (*)"));

    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }
        QDataStream out(&file);
        out << QString("Rb") << QString("Hb") << QString("Bb") << QString("Qb") << QString("Kb") << QString("Bb") << QString("Hb") << QString("Rb");
        for  (int i=0;i<8;i++) {
            out << QString("Pb");
        }
        for  (int r=3;r<7;r++) {
            for (int k=0;k<8;k++) {
                out << QString(".");
            }
        }
        for  (int i=0;i<8;i++) {
            out << QString("Pw");
        }
        out << QString("Rw") << QString("Hw") << QString("Bw") << QString("Qw") << QString("Kw") << QString("Bw") << QString("Hw") << QString("Rw");
    }
}

void MainWindow::open() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Load game"), "",
                                                    tr("Chess File (*.chs);;All Files (*)"));
    if (fileName.isEmpty())
        return;
    else {

        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }

        try {
            QDataStream in(&file);
            QString debugstring;
            for (int r=0;r<8;r++) {
                for (int k=0;k<8;k++) {
                    QString piece;
                    in >> piece;
                    debugstring += "\t" + piece;
                    if (in.status()!=QDataStream::Ok) {
                        throw QString("Error reading file "+fileName);
                    }
                }
                debugstring += "\n";
            }
            QMessageBox::information(this, tr("Debug"),
                                     debugstring);
        } catch (QString& Q) {
            QMessageBox::information(this, tr("Error reading file"),
                                     Q);
        }
    }
    update();
}


void MainWindow::undo() {
    QMessageBox box;
    box.setText(QString("Je hebt undo gekozen"));
    box.exec();
}

void MainWindow::redo() {
    QMessageBox box;
    box.setText(QString("Je hebt redo gekozen"));
    box.exec();
}


void MainWindow::visualizationChange() {
    QMessageBox box;
    QString visstring = QString(display_moves->isChecked()?"T":"F")+(display_kills->isChecked()?"T":"F")+(display_threats->isChecked()?"T":"F");
    box.setText(QString("Visualization changed : ")+visstring);
    box.exec();
}


// Update de inhoud van de grafische weergave van het schaakbord (scene)
// en maak het consistent met de game state in variabele g.
void MainWindow::update() {
    // Itereer over alle mogelijke plaatsen van het schaakbord
    for ( int r = 0; r < 8; r++) {
        for ( int k = 0; k < 8; k++ ) {
            SchaakStuk * updatePiece = g.getPiece(r, k);
            // als updatePiece geen nullptr is kan deze gevisualiseerd worden
            if ( updatePiece != nullptr ) {
                scene->setItem(updatePiece->position.first, updatePiece->position.second, updatePiece->piece());
            }
        }
    }
}


void MainWindow::createActions() {
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Start a new game"));
    connect(newAct, &QAction::triggered, this, &MainWindow::newGame);

    openAct = new QAction(tr("&Open"), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Read game from disk"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save game to disk"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Abandon game"));
    connect(exitAct, &QAction::triggered, this, &MainWindow::on_actionExit_triggered);

    undoAct = new QAction(tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo last move"));
    connect(undoAct, &QAction::triggered, this, &MainWindow::undo);

    redoAct = new QAction(tr("&redo"), this);
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setStatusTip(tr("Redo last undone move"));
    connect(redoAct, &QAction::triggered, this, &MainWindow::redo);

    display_moves= new QAction(tr("&valid moves"), this);
    display_moves->setStatusTip(tr("Show valid moves"));
    display_moves->setCheckable(true);
    display_moves->setChecked(true);
    connect(display_moves, &QAction::triggered, this, &MainWindow::visualizationChange);

    display_kills= new QAction(tr("threathed &enemy"), this);
    display_kills->setStatusTip(tr("Highlight threathened pieces (enemy)"));
    display_kills->setCheckable(true);
    display_kills->setChecked(true);
    connect(display_kills, &QAction::triggered, this, &MainWindow::visualizationChange);

    display_threats= new QAction(tr("threathed &player"), this);
    display_threats->setStatusTip(tr("Highlight threathened pieces (player)"));
    display_threats->setCheckable(true);
    display_threats->setChecked(true);
    connect(display_threats, &QAction::triggered, this, &MainWindow::visualizationChange);
}

void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(exitAct);

    gameMenu = menuBar()->addMenu(tr("&Game"));
    gameMenu->addAction(undoAct);
    gameMenu->addAction(redoAct);

    visualizeMenu = menuBar()->addMenu(tr("&Visualize"));
    visualizeMenu->addAction(display_moves);
    visualizeMenu->addAction(display_kills);
    visualizeMenu->addAction(display_threats);
}

void MainWindow::on_actionExit_triggered() {
    if (QMessageBox::Yes == QMessageBox::question(this,
                                                  tr("Spel verlaten"),
                                                  tr("Bent u zeker dat u het spel wil verlaten?\nNiet opgeslagen wijzigingen gaan verloren.")))
    {
        QApplication::quit();
    }
}

