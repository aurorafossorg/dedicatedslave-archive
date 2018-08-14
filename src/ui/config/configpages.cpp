#include <QtWidgets>

#include "configpages.h"
#include "configdialog.h"

ConfigurationPage::ConfigurationPage(QWidget *parent)
    : QWidget(parent)
{
    //parentWin = qobject_cast<QObject*>(parent);
    parentWin = dynamic_cast<ConfigDialog*>(parent);
    if(parentWin != 0){
        QString _string = parentWin->getDirSteamcmd();

        QGroupBox *configGroup = new QGroupBox(tr("Server configuration"));

        QLabel *dirLabelMain = new QLabel(tr("Dir:"));
        QLineEdit *dirValueMain = new QLineEdit(QApplication::applicationDirPath());
        QHBoxLayout *dirMain = new QHBoxLayout;
        dirMain->addWidget(dirLabelMain);
        dirMain->addWidget(dirValueMain);

        QLabel *serverLabel = new QLabel(tr("Server:"));
        QComboBox *serverCombo = new QComboBox;
        serverCombo->addItem(tr("Qt (Australia)"));
        serverCombo->addItem(tr("Qt (Germany)"));
        serverCombo->addItem(tr("Qt (Norway)"));
        serverCombo->addItem(tr("Qt (People's Republic of China)"));
        serverCombo->addItem(tr("Qt (USA)"));
        QHBoxLayout *serverLayout = new QHBoxLayout;
        serverLayout->addWidget(serverLabel);
        serverLayout->addWidget(serverCombo);

        QLabel *dirLabelApp = new QLabel(tr("dirApp:"));
        QLineEdit *dirValueApp = new QLineEdit(parentWin->getDirApp());
        QHBoxLayout *dirApp = new QHBoxLayout;
        dirApp->addWidget(dirLabelApp);
        dirApp->addWidget(dirValueApp);

        QLabel *dirLabelSteamcmd = new QLabel(tr("dirSteamcmd:"));
        QLineEdit *dirValueSteamcmd = new QLineEdit(parentWin->getDirSteamcmd());
        QHBoxLayout *dirSteamcmd = new QHBoxLayout;
        dirSteamcmd->addWidget(dirLabelSteamcmd);
        dirSteamcmd->addWidget(dirValueSteamcmd);

        QLabel *dirLabelSettings = new QLabel(tr("dirSettings:"));
        QLineEdit *dirValueSettings = new QLineEdit(parentWin->getDirSettings());
        QHBoxLayout *dirSettings = new QHBoxLayout;
        dirSettings->addWidget(dirLabelSettings);
        dirSettings->addWidget(dirValueSettings);

        QLabel *hasLabelSteamcmd = new QLabel(tr("hasSteamcmd"));
        QCheckBox *hasValueSteamcmd = new QCheckBox(tr("hasSteamcmd"));
        hasValueSteamcmd->setTristate(parentWin->hasSteamcmd());
        hasValueSteamcmd->setDisabled(true);

        QPushButton *buttonInstall = new QPushButton("Install", this);
        //buttonInstall->setGeometry(QRect(QPoint(100, 100)), QSize(200, 50));
        connect(buttonInstall, SIGNAL(clicked()), parentWin, SLOT(installSteamcmd()));
        QHBoxLayout *hasSteamcmd = new QHBoxLayout;
        hasSteamcmd->addWidget(hasLabelSteamcmd);
        hasSteamcmd->addWidget(hasValueSteamcmd);
        hasSteamcmd->addWidget(buttonInstall);

        QVBoxLayout *configLayout = new QVBoxLayout;
        configLayout->addLayout(serverLayout);
        configLayout->addLayout(dirMain);
        configLayout->addLayout(dirApp);
        configLayout->addLayout(dirSteamcmd);
        configLayout->addLayout(dirSettings);
        configLayout->addLayout(hasSteamcmd);
        configGroup->setLayout(configLayout);

        QVBoxLayout *mainLayout = new QVBoxLayout;
        mainLayout->addWidget(configGroup);
        mainLayout->addStretch(1);
        setLayout(mainLayout);
    }
}

UpdatePage::UpdatePage(QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *updateGroup = new QGroupBox(tr("Package selection"));
    QCheckBox *systemCheckBox = new QCheckBox(tr("Update system"));
    QCheckBox *appsCheckBox = new QCheckBox(tr("Update applications"));
    QCheckBox *docsCheckBox = new QCheckBox(tr("Update documentation"));

    QGroupBox *packageGroup = new QGroupBox(tr("Existing packages"));

    QListWidget *packageList = new QListWidget;
    QListWidgetItem *qtItem = new QListWidgetItem(packageList);
    qtItem->setText(tr("Qt"));
    QListWidgetItem *qsaItem = new QListWidgetItem(packageList);
    qsaItem->setText(tr("QSA"));
    QListWidgetItem *teamBuilderItem = new QListWidgetItem(packageList);
    teamBuilderItem->setText(tr("Teambuilder"));

    QPushButton *startUpdateButton = new QPushButton(tr("Start update"));

    QVBoxLayout *updateLayout = new QVBoxLayout;
    updateLayout->addWidget(systemCheckBox);
    updateLayout->addWidget(appsCheckBox);
    updateLayout->addWidget(docsCheckBox);
    updateGroup->setLayout(updateLayout);

    QVBoxLayout *packageLayout = new QVBoxLayout;
    packageLayout->addWidget(packageList);
    packageGroup->setLayout(packageLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(updateGroup);
    mainLayout->addWidget(packageGroup);
    mainLayout->addSpacing(12);
    mainLayout->addWidget(startUpdateButton);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

QueryPage::QueryPage(QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *packagesGroup = new QGroupBox(tr("Look for packages"));

    QLabel *nameLabel = new QLabel(tr("Name:"));
    QLineEdit *nameEdit = new QLineEdit;

    QLabel *dateLabel = new QLabel(tr("Released after:"));
    QDateTimeEdit *dateEdit = new QDateTimeEdit(QDate::currentDate());

    QCheckBox *releasesCheckBox = new QCheckBox(tr("Releases"));
    QCheckBox *upgradesCheckBox = new QCheckBox(tr("Upgrades"));

    QSpinBox *hitsSpinBox = new QSpinBox;
    hitsSpinBox->setPrefix(tr("Return up to "));
    hitsSpinBox->setSuffix(tr(" results"));
    hitsSpinBox->setSpecialValueText(tr("Return only the first result"));
    hitsSpinBox->setMinimum(1);
    hitsSpinBox->setMaximum(100);
    hitsSpinBox->setSingleStep(10);

    QPushButton *startQueryButton = new QPushButton(tr("Start query"));

    QGridLayout *packagesLayout = new QGridLayout;
    packagesLayout->addWidget(nameLabel, 0, 0);
    packagesLayout->addWidget(nameEdit, 0, 1);
    packagesLayout->addWidget(dateLabel, 1, 0);
    packagesLayout->addWidget(dateEdit, 1, 1);
    packagesLayout->addWidget(releasesCheckBox, 2, 0);
    packagesLayout->addWidget(upgradesCheckBox, 3, 0);
    packagesLayout->addWidget(hitsSpinBox, 4, 0, 1, 2);
    packagesGroup->setLayout(packagesLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(packagesGroup);
    mainLayout->addSpacing(12);
    mainLayout->addWidget(startQueryButton);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}
