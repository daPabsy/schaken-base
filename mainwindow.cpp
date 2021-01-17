#include "mainwindow.h"
//#include "SchaakStuk.h"
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

// Laat de bedreigde stukken zien van beide de kleur die aan de beurt is
void MainWindow::actuallyDisplayThreats(const zw & color) {
    if ( display_threats->isChecked() ) {
        displayThreats(g.getTurnMove()); // Laat de bedreigde stukken zien van kleur die momenteel aan de beurt is
    }
}

// Laat de de bedreigde stukken zien van de kleur die momenteel aan de beurt is
void MainWindow::displayThreats(const zw & color) {
    // Overloop alle vakjes
    for ( int i = 0; i < 8; i++ ) {
        for ( int j =0; j < 8; j++ ) {
            // Vind een stuk van de eigen kleur
            if ( g.getPiece(i, j) != nullptr && g.getPiece(i, j)->getKleur() == color ) {
                const pair<int, int> p = make_pair(i, j);
                for ( int k = 0; k < 8; k++ ) {
                    for ( int l = 0; l < 8; l++ ) {
                        // Vind een stuk van de andere kleur
                        SchaakStuk * enemy = g.getPiece(k, l);
                        if ( enemy != nullptr && enemy->getKleur() != color && enemy->piece().type() != Piece::King ) {
                            const vector<pair<int, int>> & moves = enemy->geldige_zetten(g,
                                                                                         false); // Verkrijg geldige zetten
                            const vector<pair<int, int>> & possibleMoves = g.checkForKingCheck(moves, enemy); // Zetten waar King niet schaakmat staat
                            for (const pair<int, int> & o : possibleMoves) { // Overloop de zetten
                                // Bij een gelijkenis wordt deze gemarkeerd op het bord
                                if (o == p) {
                                    scene->setPieceThreat(i, j, true); // Markeer de bedreigingen
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

// Laat de stukken zien die geslagen kunnen worden door de kleur aan beurt
// dit is gewoon de kleur verwisselen en de bedreigde stukken markeren
void MainWindow::displayKills(const zw & color) {
    if ( display_kills->isChecked() ) {
        if ( color == zwart ) { // Verwissel kleur
            displayThreats(wit); // Laat de bedreigde stukken zien van kleur die momenteel aan de beurt is
        }
        else if ( color == wit ) {
            displayThreats(zwart);
        }
    }
}

// Laat geldige zetten zien op het schaakBord, worden blauw gemarkeerd
void MainWindow::displayMoves(const int & r, const int & k) {

    SchaakStuk * toMove = g.getPiece(r, k); // Verkrijg te verplaatsen SchaakStuk
    const vector<pair<int, int>> & moves = toMove->geldige_zetten(g, false); // Verkrijg geldige zetten

    // Is het de koning die we willen verplaatsen?
    if ( g.checkKing(r, k) ){
        for ( const pair<int, int> & i : moves ) {
            scene->setTileFocus(i.first, i.second, true); // Markeer de geldige zetten
        }
    }
        // Koning mag niet schaak komen te staan
    else {
        const vector<pair<int, int>> & possibleMoves = g.checkForKingCheck(moves, toMove);
        for ( const pair<int, int> & i : possibleMoves ) {
            scene->setTileFocus(i.first, i.second, true); // Markeer de geldige zetten
        }
    }
}

// Laat de bedreigingen zien van een bepaald SchaakStuk, worden rood gemarkeerd
void MainWindow::displayThreatsMoves(const int & r, const int & k) {

    SchaakStuk * toMove = g.getPiece(r, k); // Verkrijg te verplaatsen SchaakStuk
    const vector<pair<int, int>> & moves = toMove->geldige_zetten(g, false); // Verkrijg geldige zetten

    // Is het de koning die we willen verplaatsen?
    if ( g.checkKing(r, k) ){
        const vector<pair<int, int>> & threats = g.getThreats(moves, g.getTurnMove(), toMove);
        for ( const pair<int, int> & i : threats ) {
            scene->setTileThreat(i.first, i.second, true); // Markeer de bedreigingen
        }
    }
    // Koning mag niet schaak komen te staan
    else {
        const vector<pair<int, int>> & possibleMoves = g.checkForKingCheck(moves, toMove); // Zetten waar King niet schaakmat staat
        const vector<pair<int, int>> threats = g.getThreats(possibleMoves, g.getTurnMove(), toMove);
        for ( const pair<int, int> & i : threats ) {
            scene->setTileThreat(i.first, i.second, true); // Markeer de bedreigingen
        }
    }
}




// Deze functie wordt opgeroepen telkens er op het schaakbord
// geklikt wordt. x,y geeft de positie aan waar er geklikt
// werd; r is de 0-based rij, k de 0-based kolom
void MainWindow::clicked(int r, int k) {

    // Alle markering en threats van vorige click wordt ongedaan gemaakt
    scene->removeAllMarking();
    scene->removeAllPieceThreats();

    // Laat de stukken zien die bedreigd worden
    actuallyDisplayThreats(g.getTurnMove());
    // Laat stukken zien van de andere kleur die veroverd kunnen worden
    displayKills(g.getTurnMove());

    if ( g.getMoving() == nullptr ) { // Er is nog GEEN SchaakStuk aangeklikt
        if ( g.getPiece(r, k) == nullptr ) { // Het aangeklikte SchaakStuk mag geen nullptr zijn

            cout << "Select a valid piece!" << endl;
        }
            // SchaakStuk moet van de eigen kleur zijn
        else if ( g.getPiece(r, k)->getKleur() != g.getTurnMove() ) {

            cout << "Select a piece of your own color!" << endl;
        }
        else {
            scene->removeAllMarking();
            scene->removeAllPieceThreats();

            // Volgende keer dat er geklikt wordt kan er herkend worden of er reeds
            // een SchaakStuk werd aangeklikt
            g.setMovingAndPieceToMove(true, g.getPiece(r, k));

            // Markeert het SchaakStuk dat verplaatst moet worden groen
            scene->setTileSelect(r, k, true);


            // Laat de geldige zetten zien van het geselecteerde SchaakStuk
            if ( display_moves->isChecked() ) { displayMoves(r, k); }

            // TODO voor een of andere rare reden kan ik enkel rode vakjes kleuren wanneer ook display_moves is gecheckt
            // Laat de bedreigingen zien door andere SchaakStukken wanneer er geklikt word op een SchaakStuk
            if ( display_threats->isChecked() ) { displayThreatsMoves(r, k); }

            // SchaakStuk is geselecteerd voor de volgende keer dat er geklikt wordt
        }
    }

    else { // Er is reeds een SchaakStuk aangeklikt
        const pair<int, int> & moveTo = make_pair(r, k); // Positie naar waar er verplaatst moet worden

        // Verplaats gekozen SchaakStuk
        if ( g.move(g.getMoving(), moveTo) ) { // Verplaats
            scene->clearBoard(); // Clear chessBoard
            update(); // Maak chessBoard opnieuw visueel zichtbaar

            if ( g.getPiece(r, k)->piece().type() && g.promotion(g.getPiece(r, k)) ) { // Kan er een pion gepromoveerd worden?
                promotionBoard(g.getPiece(r, k), g.getTurnMove()); // Haalt het selectiescherm op
                scene->clearBoard();
                update(); // Update het bord weer
            }

            // Laat de stukken zien die bedreigd worden
            actuallyDisplayThreats(g.getTurnMove());
            // Laat stukken zien van de andere kleur die veroverd kunnen worden
            displayKills(g.getTurnMove());

            g.setTurnMove(); // Verander van beurt

            // Er wordt eerst gecheckt op pat en daarna pas op schaakmat anders
            // krijgen we schaakmat bij pat

            if ( g.pat(g.getTurnMove()) ) { // MessageBox wanneer tegenstander je pat heeft gezet
                QMessageBox patBox;
                patBox.setWindowTitle("Pablo's Chess Simulator");
                patBox.setText(QString("Pat!; Start a new game under file!"));
                patBox.exec();
            }

            else if ( g.schaakmat(g.getTurnMove()) ) { // MessageBox wanneer tegenstander je schaakmat heeft gezet
                QMessageBox checkMateBox;
                checkMateBox.setWindowTitle("Pablo's Chess Simulator");
                checkMateBox.setText(QString("Checkmate!; Start a new game under file!"));
                checkMateBox.exec();
            }

            else if ( g.schaak(g.getTurnMove()) ) { // MessageBox wanneer tegenstander je schaak heeft gezet
                QMessageBox checkBox;
                checkBox.setWindowTitle("Pablo's Chess Simulator");
                checkBox.setText(QString("Check!"));
                checkBox.exec();
            }
        }
        // g.move geeft false terug, speler heeft een unvalid move geselecteerd
        else {
            // Laat de stukken zien die bedreigd worden
            actuallyDisplayThreats(g.getTurnMove());
            // Laat stukken zien van de andere kleur die veroverd kunnen worden
            displayKills(g.getTurnMove());
            cout << "Select a valid move!" << endl;
        }
    }
}


// Laat een menu zien om de promotie van de pion uit te selecteren en
// vervangt deze ook met de keuze
void MainWindow::promotionBoard(SchaakStuk * s, const zw & color) {

    QMessageBox promotionBox;
    promotionBox.setWindowTitle("Pablo's Chess Simulator");
    promotionBox.setText(QString("Your pawn can be promoted!"));
    promotionBox.exec();

    // Laat een drop-down menu zien om een promotie te kiezen voor de pion
    QInputDialog promotion;
    QStringList pieces;
    pieces << "Rook" << "Knight" << "Bishop" << "Queen";
    QString piece = promotion.getItem(this, "Select your choice here!", "Promotion:", pieces);

    int r = s->position.first;
    int k = s->position.second;

    if ( piece == "Rook" ) {
        g.capturedPiece(s->position); // Verwijdert de pion
        g.setPiece(r, k, new Toren(color, false)); // Zet een nieuwe toren op de plaats van de pion
    }
    else if ( piece == "Knight" ) {
        g.capturedPiece(s->position);
        g.setPiece(r, k, new Paard(color, false));
    }
    else if ( piece == "Bishop" ) {
        g.capturedPiece(s->position);
        g.setPiece(r, k, new Loper(color, false));
    }
    else if ( piece == "Queen" ) {
        g.capturedPiece(s->position);
        g.setPiece(r, k, new Koningin(color, false));
    }
}


// Nieuw spel starten
void MainWindow::newGame() {
    // Verwijder elk SchaakStuk op het bord
    for ( int i = 0; i < 8; i++ ) {
        for ( int j = 0; j < 8; j++ ) {
            if ( g.getPiece(i, j) != nullptr ) {
                delete g.getPiece(i, j);
            }
            else {
                g.setNullptr(i, j, nullptr);
            }
        }
    }
    if ( g.getTurnMove() == zwart ) { // Wit begint steeds met spelen
        g.setTurnMove();
    }
    scene->removeAllMarking();
    scene->clearBoard();
    g.setStartBord(); // Zet het startBord terug op
    update(); // Update het bord visueel
}

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
void MainWindow::update() const {
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

