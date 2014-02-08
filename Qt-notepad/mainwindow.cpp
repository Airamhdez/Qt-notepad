#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //Establecemos el tamaño inicial de la ventana
    this->setGeometry(30, 30, 800, 600);

    //Establecemos el título de la ventana
    this->setWindowTitle(tr("Super editor de texto"));

    //instanciamos la variavle txtEditor indicandole con el this que hereda de la clase padre QMainwindow
    txtEditor_ = new QPlainTextEdit(this);
    setCentralWidget(txtEditor_);

    //inicializamos los menús
    mainMenu_ = new QMenuBar(this);
    /*tr es una funcion de qt que es bueno usarla cada vez que queramos
    introducir una cadena de texto por si el dia de mañana queremos traducir
    nuestro codigo, luego la palabra archivo es el nombre del qmenu y le ponemos
    el & delante para que nos muestre la letra A subrayada y podamos pulsar alt+A
    nos seleccione ese menu*/
    mnuArchivo_ = new QMenu(tr("&Archivo"), this);
    mainMenu_->addMenu(mnuArchivo_);
    //con esto colocamos correctamente el menú para que se muestre bien
    setMenuBar(mainMenu_);
    //instanciamos y asociamos las acciones Abrir y Guardar
    actArchivoAbrir_ = new QAction(tr("&Abrir"), this);
    //añadimos un atajo de teclado para la opción abrir
    actArchivoAbrir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    mnuArchivo_->addAction(actArchivoAbrir_);
    actArchivoGuardar_ = new QAction(tr("&Guardar"), this);
    mnuArchivo_->addAction(actArchivoGuardar_);
    actArchivoSalir_ = new QAction(tr("&Salir"), this);
    actArchivoSalir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    mnuArchivo_->addAction(actArchivoSalir_);

    mnuEditar_ = new QMenu(tr("&Editar"), this);
    mainMenu_->addMenu(mnuEditar_);

    actEditarCopiar_ = new QAction(tr("&Copiar"), this);
    actEditarCopiar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    mnuEditar_->addAction(actEditarCopiar_);

    actEditarPegar_ = new QAction(tr("&Pegar"), this);
    actEditarPegar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_V));
    mnuEditar_->addAction(actEditarPegar_);

    QIcon cortar(":/new/iconos/Iconos/icono-cortar.png");
    actEditarCortar_ = new QAction(cortar, tr("&Cortar"), this);
    actEditarCortar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_X));
    mnuEditar_->addAction(actEditarCortar_);

    actEditarDeshacer_ = new QAction(tr("&Deshacer"), this);
    actEditarDeshacer_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
    mnuEditar_->addAction(actEditarDeshacer_);

    actEditarRehacer_ = new QAction(tr("&Rehacer"), this);
    actEditarRehacer_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y));
    mnuEditar_->addAction(actEditarRehacer_);

    mnuFormato_ = new QMenu(tr("&Formato"), this);
    mainMenu_->addMenu(mnuFormato_);

    actFormatoFuente_ = new QAction(tr("&Fuente"), this);
    mnuFormato_->addAction(actFormatoFuente_);

    mnuAyuda_ = new QMenu(tr("&Ayuda"), this);
    mainMenu_->addMenu(mnuAyuda_);

    actAyudaAcercaDe_ = new QAction(tr("&Acerca de"), this);
    mnuAyuda_->addAction(actAyudaAcercaDe_);

    //creamos una toolbar
    tlbBarra = new QToolBar(this);
    addToolBar(tlbBarra);
    tlbBarra->addAction(actArchivoAbrir_);
    tlbBarra->addAction(actArchivoGuardar_);
    tlbBarra->addAction(actEditarCopiar_);
    tlbBarra->addAction(actEditarCortar_);
    tlbBarra->addAction(actEditarPegar_);
    tlbBarra->addAction(actEditarDeshacer_);
    tlbBarra->addAction(actEditarRehacer_);
    tlbBarra->addAction(actFormatoFuente_);

    //conectamos las acciones de los menús con nuestros slots
    connect(actArchivoAbrir_, SIGNAL(triggered()), this, SLOT(alAbrir()));
    connect(actArchivoGuardar_, SIGNAL(triggered()), this, SLOT(alGuardar()));
    connect(actEditarCopiar_, SIGNAL(triggered()), txtEditor_, SLOT(copy()));
    connect(actEditarPegar_, SIGNAL(triggered()), txtEditor_, SLOT(paste()));
    connect(actEditarCortar_, SIGNAL(triggered()), txtEditor_, SLOT(cut()));
    connect(actEditarDeshacer_, SIGNAL(triggered()), txtEditor_, SLOT(undo()));
    connect(actEditarRehacer_, SIGNAL(triggered()), txtEditor_, SLOT(redo()));
    connect(actFormatoFuente_, SIGNAL(triggered()), this, SLOT(alFuente()));
    connect(actArchivoSalir_, SIGNAL(triggered()), this, SLOT(close()));
    connect(actAyudaAcercaDe_, SIGNAL(triggered()), this, SLOT(alAcercaDe()));

}

MainWindow::~MainWindow()
{

}

void MainWindow::alAbrir()
{
    QString nombreArchivo;
    nombreArchivo = QFileDialog::getOpenFileName(this,
                                                 tr("Abrir archivo de texto plano"),
                                                 "",
                                                 tr("Archivos de texto plano (*.txt)"));
    if(nombreArchivo != "")
    {
        //Intentamos abrir el archivo
        QFile archivo;
        archivo.setFileName(nombreArchivo);
        if(archivo.open(QFile::ReadOnly))
        {
            //si se pudo abrir el archivo, lo leemos y colocamos
            txtEditor_->setPlainText(archivo.readAll());
            //Se cierra el fichero
            archivo.close();
        }
    }
}

void MainWindow::alGuardar()
{
    //Mostramos un diálogo de guardado de ficheros y almacenamos
    QString nombreArchivo;
    nombreArchivo = QFileDialog::getSaveFileName(this,
                                                 tr("Guardar archivo como"),
                                                 "",
                                                 tr("Archivo de texto plano (*.txt)"));
    if(nombreArchivo != "")
    {
        //Intentamos abrir el archivo
        QFile archivo;
        archivo.setFileName(nombreArchivo);
        if(archivo.open(QFile::WriteOnly | QFile::Truncate))
        {
            //Si se pudo abrir el archivo, escribimos el contenido del texto
            archivo.write(txtEditor_->toPlainText().toUtf8());
            //Se cierra el fichero
            archivo.close();
        }
    }

}

void MainWindow::alFuente()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, txtEditor_->font(), this);
    if (ok) {
       // Si el usuario hizo click en OK, se establece la fuente seleccionada
       txtEditor_->setFont(font);
    }

}

void MainWindow::alAcercaDe()
{
    QMessageBox mensaje;
    mensaje.setText("Editor creado por Airam Hernandez Sacramento");
    mensaje.exec();
}
