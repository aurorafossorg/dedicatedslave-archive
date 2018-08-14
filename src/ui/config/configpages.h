#ifndef DEDICATEDSLAVE_UI_CONFIGPAGES_H
#define DEDICATEDSLAVE_UI_CONFIGPAGES_H

#include <QWidget>
#include "configdialog.h"

class ConfigurationPage : public QWidget {
    Q_OBJECT
public:
	ConfigurationPage(QWidget *parent = 0);
private:
    ConfigDialog *parentWin;
};

class QueryPage : public QWidget {
public:
	QueryPage(QWidget *parent = 0);
};

class UpdatePage : public QWidget {
public:
	UpdatePage(QWidget *parent = 0);
};

#endif // DEDICATEDSLAVE_UI_CONFIGPAGES_H
