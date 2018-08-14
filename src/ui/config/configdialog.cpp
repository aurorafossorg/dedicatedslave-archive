#include <QtWidgets>

#include "configdialog.h"
#include "configpages.h"

// A modal dialog is a dialog that blocks input to other visible windows in the same application.
// Dialogs that are used to request a file name from the user or that are used to set application preferences are usually modal.
// Dialogs can be application modal (the default) or window modal.
ConfigDialog::ConfigDialog(DedicatedSlaveApp *app) {

    _app = app;
    _dirSteamcmd = app->getDirSteamcmd();
    _dirApp = app->getDirApp();
    _dirSettings = app->getDirSettings();
    _hasSteamcmd = app->hasSteamcmd();

    contentsWidget = new QListWidget;
    contentsWidget->setViewMode(QListView::IconMode);
    contentsWidget->setIconSize(QSize(96, 84));
    contentsWidget->setMovement(QListView::Static);
    contentsWidget->setMaximumWidth(128);
    contentsWidget->setSpacing(12);

    pagesWidget = new QStackedWidget;
    pagesWidget->addWidget(new ConfigurationPage(this));
    pagesWidget->addWidget(new UpdatePage);
    pagesWidget->addWidget(new QueryPage);

    QPushButton *closeButton = new QPushButton(tr("Close"));

    createIcons();
    contentsWidget->setCurrentRow(0);

    connect(closeButton, &QAbstractButton::clicked, this, &QWidget::close);

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(contentsWidget);
    horizontalLayout->addWidget(pagesWidget, 1);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(closeButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(horizontalLayout);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Config Dialog"));
}

void ConfigDialog::instalSteamcmd(){
    _app->installSteamcmd();
}

bool ConfigDialog::hasSteamcmd(){
    return _hasSteamcmd;
}

QString ConfigDialog::getDirSteamcmd(){
    return _dirSteamcmd;
}

QString ConfigDialog::getDirApp(){
    return _dirApp;
}

QString ConfigDialog::getDirSettings(){
    return _dirSettings;
}

void ConfigDialog::createIcons(){
    QListWidgetItem *configButton = new QListWidgetItem(contentsWidget); // config button
    configButton->setIcon(QIcon(":/images/config.png"));
    configButton->setText(tr("Configuration"));
    configButton->setTextAlignment(Qt::AlignHCenter);
    configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    QListWidgetItem *updateButton = new QListWidgetItem(contentsWidget); // update button
    updateButton->setIcon(QIcon(":/images/update.png"));
    updateButton->setText(tr("Update"));
    updateButton->setTextAlignment(Qt::AlignHCenter);
    updateButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    QListWidgetItem *queryButton = new QListWidgetItem(contentsWidget); // query button
    queryButton->setIcon(QIcon(":/images/query.png"));
    queryButton->setText(tr("Query"));
    queryButton->setTextAlignment(Qt::AlignHCenter);
    queryButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    connect(contentsWidget, &QListWidget::currentItemChanged, this, &ConfigDialog::changePage);
}

void ConfigDialog::changePage(QListWidgetItem *current, QListWidgetItem *previous){
    if (!current)
        current = previous;

    pagesWidget->setCurrentIndex(contentsWidget->row(current));
}
