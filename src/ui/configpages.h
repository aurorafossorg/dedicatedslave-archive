#ifndef DEDICATEDSLAVE_UI_CONFIGPAGES_H
#define DEDICATEDSLAVE_UI_CONFIGPAGES_H

#include <QWidget>

class ConfigurationPage : public QWidget {
public:
	ConfigurationPage(QWidget *parent = 0);
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