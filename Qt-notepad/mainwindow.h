#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QFileDialog>
#include <QFile>
#include <QFontDialog>
#include <QClipboard>
#include <QMessageBox>
#include <QToolBar>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void alAbrir();
    void alGuardar();
    void alFuente();
    void alAcercaDe();

private:
    QMenuBar* mainMenu_;
    QToolBar* tlbBarra;
    QMenu* mnuArchivo_;
    QPlainTextEdit* txtEditor_;
    QAction* actArchivoAbrir_;
    QAction* actArchivoGuardar_;
    QAction* actArchivoSalir_;
    QMenu* mnuFormato_;
    QAction* actFormatoFuente_;
    QMenu* mnuEditar_;
    QAction* actEditarCopiar_;
    QAction* actEditarPegar_;
    QAction* actEditarCortar_;
    QAction* actEditarDeshacer_;
    QAction* actEditarRehacer_;
    QMenu* mnuAyuda_;
    QAction* actAyudaAcercaDe_;
};

#endif // MAINWINDOW_H
