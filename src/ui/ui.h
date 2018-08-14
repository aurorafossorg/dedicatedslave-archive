#ifndef UI_H
#define UI_H

#include <QWidget>

#include <dedicatedslave/logic/app.h>
#include "uidock.h"
#include "config/configdialog.h"

class QTableWidget;
class QLabel;
class QMenu;
class QActionGroup;
class QTextEdit;
class QFileSystemModel;
class QTreeView;
class QTabWidget;
class QProgressBar;
class QGroupBox;
class QMainWindow;

class QDockWidget;

class DedicatedSlaveUi : public QWidget{

    Q_OBJECT

public:

    DedicatedSlaveUi(const QString &dir, QWidget *parent = 0);
    QMenu* getContextMenu();
    void updateProgressBar(int value);
    void resetProgressBar();

protected:

    void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;

private slots:

    void slot_addInstanceCombo(int index);
    void slot_addInstNameEdit(QString instanceName);
    void slot_addInstDirEdit(QString instanceDir);
    void slot_instanceSelect(int row, int column);

private:

    QMainWindow *parentWin;
    void updateEdit();
    void updateEdit1(const QString &customer);
    void updateEdit2(const QString &paragraph);
    void conn_actionVerifyInst();
    void conn_actionRunInst();
    void updateModelInstTable();
    void initActions();
    void initStatusBar();
    void initMenus();
    void createToolBar();
    void conn_actionNewInst();
    void conn_actionNewInstDialog();
    void conn_actionRemoveInst();
    void conn_actionBackup();
    void conn_actionRestore();
    void conn_actionUndo();
    void conn_actionRedo();
    void conn_actionCut();
    void conn_actionCopy();
    void conn_actionPaste();
    void conn_actionOptions();
    void conn_actionHelp();
    void conn_actionCheckUpdates();
    void conn_actionAbout();
    void conn_actionAboutQt();
    void conn_actionSetLineSpacing();
    void conn_actionSetParagraphSpacing();

    DedicatedSlaveApp *ds_app;

    QString app_dir;
    QString app_newInstGame;
    QString app_newInstDir;
    QString app_newIntsName;
    int *app_slcInstPos;

    QTableWidget *ui_instanceTable;
    QDialog *ui_dialogConfig;
    QTextEdit *ui_textEdit;
    QLabel *ui_infoLabel;
    QProgressBar *ui_progressBar;
    QGroupBox *ui_newInstGroup;

    UiDockOptions *dockOptions;
    UiDockFileSystem *dockFileSystem;

    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuView;
    QMenu *menuTools;
    QMenu *menuFormat;
    QMenu *menuHelp;

    QActionGroup *actGroupAlign;

    QAction *actNewInst;
    QAction *actRemoveInst;
    QAction *actRunInst;
    QAction *actVerifyInst;
    QAction *actBackupInst;
    QAction *actRestoreInst;
    QAction *actExit;
    QAction *actUndo;
    QAction *actRedo;
    QAction *actCut;
    QAction *actCopy;
    QAction *actPaste;
    QAction *actOptions;
    QAction *actHelp;
    QAction *actCheckUpdates;
    QAction *actAbout;
    QAction *actAboutQt;

};

#endif // UI_H
