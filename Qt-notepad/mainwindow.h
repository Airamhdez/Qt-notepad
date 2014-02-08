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

private:
    QMenuBar* mainMenu_;
    QMenu* mnuArchivo_;
    QPlainTextEdit* txtEditor_;
    QAction* actArchivoAbrir_;
    QAction* actArchivoGuardar_;
    QMenu* mnuFormato_;
    QAction* actFormatoFuente_;
    QMenu* mnuEditar_;
    QAction* actEditarCopiar_;
    QAction* actEditarPegar_;
};

#endif // MAINWINDOW_H
