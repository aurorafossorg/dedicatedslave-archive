#include "MainWindow.h"
#include <QApplication>

using namespace DedicatedSlave;

int main(int argc, char *argv[]){
	QApplication app(argc, argv);
	app.setApplicationDisplayName("DedicatedSlave");
	MainWindow mainwindow;
	mainwindow.show();
	return app.exec();
}