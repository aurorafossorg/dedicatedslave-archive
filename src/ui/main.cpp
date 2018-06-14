#include "mainwindow.h"
#include <QDebug>
#include <QApplication>
#include <QSplashScreen>
#include <QDir>

const bool DS_DEV = false;

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg){
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    //qDebug() << "C++ Style Debug Message";
    //qDebug( "C Style Debug Message" );
    case QtDebugMsg:
        if(DS_DEV){
            fprintf(stderr, "\033[1;34mDebug:\033[0m \033[30m%s\033[0m (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        }
        break;
    //qInfo is qt5.5+ only.
    //qInfo() << "C++ Style Info Message";
    //qInfo( "C Style Info Message" );
    case QtInfoMsg:
        fprintf(stderr, "\033[30mInfo:\033[0m \033[30m%s\033[0m (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    //qWarning() << "C++ Style Warning Message";
    //qWarning( "C Style Warning Message" );
    case QtWarningMsg:
        fprintf(stderr, "\033[1;33mWarning:\033[0m \033[30m%s\033[0m (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    //qCritical() << "C++ Style Critical Error Message";
    //qCritical( "C Style Critical Error Message" );
    case QtCriticalMsg:
        fprintf(stderr, "\033[31mCritical:\033[0m \033[30m%s\033[0m (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    //qFatal does not have a C++ style method.
    //qFatal( "C Style Fatal Error Message" );
    case QtFatalMsg:
        fprintf(stderr, "\033[31mFatal:\033[0m \033[30m%s\033[0m (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        abort();
    }
}

int main(int argc, char *argv[]){

    if(DS_DEV){
        // Message Handler
        qInstallMessageHandler(myMessageOutput);
    }

    // Resource
    qDebug() << "\tInitializing resources...";
    Q_INIT_RESOURCE(ui);
    qDebug() << "\tResources initialized.";

    // QApllication
    QApplication app(argc, argv); // QApplication
    app.setApplicationDisplayName("DedicatedSlave");

    // Arguments
    QStringList args = QApplication::instance()->arguments();
    args.takeFirst(); // skip the first argument, which is the program's name
    if (args.isEmpty()) {
//        printf("Usage: dedicatedslave arg1 [arg2... argN]\n\n"
//               "\tTEST 123\n");
        QApplication::instance()->quit();
    }
    foreach (QString arg, args) {
        qDebug() << arg;
    }

    // TODO: hardcoded image of splashscreen

    // Splash Screen
    QSplashScreen *splashScreen = new QSplashScreen;
    splashScreen->setPixmap(QPixmap("/home/alex1a/ProgrammingFiles/dedicatedslave/1.png"));
    splashScreen->show();
    splashScreen->showMessage(QObject::tr("Initiating your program now..."), Qt::AlignLeft | Qt::AlignTop, Qt::black);

    // Program
    qApp->processEvents();
    //qInfo() << "\tQDir::currentPath" << QDir::currentPath();
    //qInfo() << "\tApplication::applicationDirPath" << QApplication::applicationDirPath();
    //qInfo() << "\tQApplication::applicationVersion" << QApplication::applicationVersion();

    qInfo() << "(CLASS)\tInitializing 'MainWindow' class...";
    MainWindow mainWin(QCoreApplication::applicationDirPath());
    qInfo() << "(CLASS)\t'MainWindow' initialized.";
    mainWin.setWindowTitle(QObject::tr("DedicatedSlave"));
    QTimer::singleShot(2500, &mainWin, SLOT(showMaximized())); // Show MainWindow
    splashScreen->finish(&mainWin); // Close Splash Screen when MainWindow show
    return app.exec();
}
