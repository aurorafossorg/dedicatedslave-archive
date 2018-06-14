// Includes

#include <QtWidgets>
#include "ui.h"

DedicatedSlaveUi::DedicatedSlaveUi(const QString &dir, QWidget *parent)
    : QWidget(parent), app_slcInstPos(new int[2])
{
    app_slcInstPos[0] = -1;
    parentWin = qobject_cast<QMainWindow*>(parent);
	if(parentWin != 0 ) { // After casting parent widget QMainWindow, need to check if is not null (Async)
		// Core
		qInfo() << "(CLASS)\tInitializing 'DedicatedSlaveApp' class...";
		ds_app = new DedicatedSlaveApp(dir, this);
		qInfo() << "(CLASS)\t'DedicatedSlaveApp' initialized.";

        //QObject::connect(&ds_app, SIGNAL(signal_verifyComplete(int)), this);

		// Variables
		app_dir = dir;

		// Actions
		initActions();
        qInfo() << "\tActions initialized.";

		// Main Components

		// Instance List
		ui_instanceTable = new QTableWidget;
		ui_instanceTable->setRowCount(0);
		ui_instanceTable->setColumnCount(3);
		QStringList header;
		header << "Name" << "Game" << "Status";
		ui_instanceTable->setHorizontalHeaderLabels(header);
		connect(ui_instanceTable, SIGNAL(cellClicked(int,int)), this, SLOT(slot_instanceSelect(int, int)));
		// Text Edit
		ui_textEdit = new QTextEdit(this);
		ui_textEdit->setAlignment(Qt::AlignCenter);
		// Info Label
		ui_infoLabel = new QLabel(tr("<i>Welcome to DedicatedSlave, this is the information label</i>"));
		ui_infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
		ui_infoLabel->setAlignment(Qt::AlignCenter);
		// Options Dock
		dockOptions = new UiDockOptions("Instance Options", parentWin);
		// Filesystem Dock
		dockFileSystem = new UiDockFileSystem("Workspace File System", parentWin);
        qInfo() << "\tMain Components initialized.";
		// Toolbar
		QToolBar *fileToolBar = parentWin->addToolBar(tr("File Toolbar"));
		fileToolBar->addAction(actNewInst);
		fileToolBar->addAction(actRemoveInst);
		fileToolBar->addAction(actRunInst);
		fileToolBar->addAction(actVerifyInst);
		QToolBar *editToolBar = parentWin->addToolBar(tr("Edit Toolbar"));
		editToolBar->addAction(actUndo);
        qInfo() << "\tToolbar initialized.";

		// Menus

		initMenus();
        qInfo() << "\tMenus initialized.";
		// Toggle View Menus
		menuView->addAction(dockOptions->toggleViewAction());
		menuView->addAction(dockFileSystem->toggleViewAction());
		menuView->addAction(fileToolBar->toggleViewAction());
		menuView->addAction(editToolBar->toggleViewAction());

		// Main

		QVBoxLayout *layout = new QVBoxLayout;
		QWidget *topFiller = new QWidget;
		topFiller->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
		QWidget *bottomFiller = new QWidget;
		bottomFiller->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
		layout->setMargin(5);
		layout->addWidget(topFiller);
		layout->addWidget(ui_textEdit);
		layout->addWidget(ui_instanceTable);
		layout->addWidget(ui_infoLabel);

		/* TODO: Causing segfault
		** #0  0x00007ffff74c5040 in QLayout::addChildWidget(QWidget*) () from libQt5Widgets.so.5
		** #1  0x00007ffff74bcb8c in QBoxLayout::insertWidget(int, QWidget*, int, QFlags<Qt::AlignmentFlag>) () from libQt5Widgets.so.5
		** #2  0x000055555556fcf5 in DedicatedSlaveUi::DedicatedSlaveUi (this=0x555555861320, dir=..., parent=<optimized out>) at src/ui/ui.cpp:81
		** #3  0x0000555555566d82 in MainWindow::MainWindow (this=0x7fffffffd900, dir=..., parent=<optimized out>, flags=...) at src/ui/mainwindow.cpp:7
		** #4  0x000055555556639e in main (argc=<optimized out>, argv=<optimized out>) at src/ui/main.cpp:84
		*/
		//layout->addWidget(ui_progressBar);

		layout->addWidget(bottomFiller);
		setLayout(layout);
		// Parent properties
		parentWin->statusBar()->showMessage(tr("A context menu is available by right-clicking"));
		parentWin->addDockWidget(Qt::RightDockWidgetArea, dockOptions);
		parentWin->addDockWidget(Qt::RightDockWidgetArea, dockFileSystem);
		parentWin->setCentralWidget(this);
        qInfo() << "\tParent properties has been set.";

		// Populate

		updateModelInstTable();
		updateEdit(); // ????? remove
	}
}

void DedicatedSlaveUi::contextMenuEvent(QContextMenuEvent *event){
	this->getContextMenu()->exec(event->globalPos());
}


QMenu* DedicatedSlaveUi::getContextMenu(){
	QMenu *menu = new QMenu(this);
	menu->addAction(actCut);
	menu->addAction(actCopy);
	menu->addAction(actPaste);
	return menu;
}

void DedicatedSlaveUi::updateModelInstTable()
{
	while (ui_instanceTable->rowCount() > 0)
		ui_instanceTable->removeRow(0);

	QHashIterator<QString, GameInstance*> i = ds_app->listInst();
	i.toFront();
	while (i.hasNext()) {
		i.next();
		if(!i.key().isEmpty()){
			ui_instanceTable->insertRow(ui_instanceTable->rowCount());
			QTableWidgetItem *item0 = new QTableWidgetItem(i.key());
			QTableWidgetItem *item1 = new QTableWidgetItem(i.value()->getGameId());
			QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(i.value()->getStatus()));
			ui_instanceTable->setItem(ui_instanceTable->rowCount()-1, 0, item0);
			ui_instanceTable->setItem(ui_instanceTable->rowCount()-1, 1, item1);
			ui_instanceTable->setItem(ui_instanceTable->rowCount()-1, 2, item2);
		}
	}
}

void DedicatedSlaveUi::updateProgressBar(int value){
	ui_progressBar->setValue(value);
}

void DedicatedSlaveUi::resetProgressBar(){
	ui_progressBar->reset();
}

void DedicatedSlaveUi::updateEdit(){
	ui_textEdit->clear();

	QTextCursor cursor(ui_textEdit->textCursor());
	cursor.movePosition(QTextCursor::Start);
	QTextFrame *topFrame = cursor.currentFrame();
	QTextFrameFormat topFrameFormat = topFrame->frameFormat();
	topFrameFormat.setPadding(16);
	topFrame->setFrameFormat(topFrameFormat);

	QTextCharFormat textFormat;
	QTextCharFormat boldFormat;
	boldFormat.setFontWeight(QFont::Bold);
	QTextCharFormat italicFormat;
	italicFormat.setFontItalic(true);

	QTextTableFormat tableFormat;
	tableFormat.setBorder(1);
	tableFormat.setCellPadding(16);
	tableFormat.setAlignment(Qt::AlignRight);
	cursor.insertTable(1, 1, tableFormat);
	cursor.insertText("The Firm", boldFormat);
	cursor.insertBlock();
	cursor.insertText("321 City Street", textFormat);
	cursor.insertBlock();
	cursor.insertText("Industry Park");
	cursor.insertBlock();
	cursor.insertText("Some Country");
	cursor.setPosition(topFrame->lastPosition());
	cursor.insertText(QDate::currentDate().toString("d MMMM yyyy"), textFormat);
	cursor.insertBlock();
	cursor.insertBlock();
	cursor.insertText("Dear ", textFormat);
	cursor.insertText("NAME", italicFormat);
	cursor.insertText(",", textFormat);
	for (int i = 0; i < 3; ++i)
		cursor.insertBlock();
	cursor.insertText(tr("Yours sincerely,"), textFormat);
	for (int i = 0; i < 3; ++i)
		cursor.insertBlock();
	cursor.insertText("The Boss", textFormat);
	cursor.insertBlock();
	cursor.insertText("ADDRESS", italicFormat);

	updateEdit1("BLABLABLA 1");
	updateEdit2("BLABLABLA 2");
}

void DedicatedSlaveUi::updateEdit1(const QString &customer)
{
	if (customer.isEmpty())
		return;
	QStringList customerList = customer.split(", ");
	QTextDocument *document = ui_textEdit->document();
	QTextCursor cursor = document->find("NAME");
	if (!cursor.isNull()) {
		cursor.beginEditBlock();
		cursor.insertText(customerList.at(0));
		QTextCursor oldcursor = cursor;
		cursor = document->find("ADDRESS");
		if (!cursor.isNull()) {
			for (int i = 1; i < customerList.size(); ++i) {
				cursor.insertBlock();
				cursor.insertText(customerList.at(i));
			}
			cursor.endEditBlock();
		} else {
			oldcursor.endEditBlock();
		}
	}
}

void DedicatedSlaveUi::updateEdit2(const QString &paragraph)
{
	if (paragraph.isEmpty())
		return;
	QTextDocument *document = ui_textEdit->document();
	QTextCursor cursor = document->find(tr("Yours sincerely,"));
	if (cursor.isNull())
		return;
	cursor.beginEditBlock();
	cursor.movePosition(QTextCursor::PreviousBlock, QTextCursor::MoveAnchor, 2);
	cursor.insertBlock();
	cursor.insertText(paragraph);
	cursor.insertBlock();
	cursor.endEditBlock();
}

void DedicatedSlaveUi::initActions()
{
	// https://specifications.freedesktop.org/icon-naming-spec/icon-naming-spec-latest.html
	// New Instance
	const QIcon newIcon = QIcon::fromTheme("list-add", QIcon(":/images/new.png"));
	actNewInst = new QAction(newIcon, tr("&New"), this);
	actNewInst->setShortcuts(QKeySequence::New);
	actNewInst->setStatusTip(tr("Add a new instance"));
	connect(actNewInst, &QAction::triggered, this, &DedicatedSlaveUi::conn_actionNewInstDialog);

	// Remove Instance
	const QIcon removeIcon = QIcon::fromTheme("list-remove", QIcon(":/images/new.png"));
	actRemoveInst = new QAction(removeIcon, tr("&Remove"), this);
	actRemoveInst->setShortcuts(QKeySequence::New);
	actRemoveInst->setStatusTip(tr("Remove a new instance"));
	connect(actRemoveInst, &QAction::triggered, this, &DedicatedSlaveUi::conn_actionRemoveInst);

	// Verify Instance
	const QIcon verifyIcon = QIcon::fromTheme("emblem-downloads", QIcon(":/images/new.png"));
	actVerifyInst = new QAction(verifyIcon, tr("&Verify"), this);
	actVerifyInst->setStatusTip(tr("Verify a instance"));
	connect(actVerifyInst, &QAction::triggered, this, &DedicatedSlaveUi::conn_actionVerifyInst);

	// Run Instance
	const QIcon runIcon = QIcon::fromTheme("go-next", QIcon(":/images/new.png"));
	actRunInst = new QAction(runIcon, tr("&Run"), this);
	actRunInst->setStatusTip(tr("Run a new instance"));
	connect(actRunInst, &QAction::triggered, this, &DedicatedSlaveUi::conn_actionRunInst);

	// Backup
	actBackupInst = new QAction(tr("&Backup"), this);
	actBackupInst->setStatusTip(tr("Backup the selected instance to disk"));
	connect(actBackupInst, &QAction::triggered, this, &DedicatedSlaveUi::conn_actionBackup);

	// Restore
	actRestoreInst = new QAction(tr("&Restore"), this);
	actRestoreInst->setStatusTip(tr("Restore the selected instance to disk"));
	connect(actRestoreInst, &QAction::triggered, this, &DedicatedSlaveUi::conn_actionRestore);

	// Exit/Close
	actExit = new QAction(tr("E&xit"), this);
	actExit->setShortcuts(QKeySequence::Quit);
	actExit->setStatusTip(tr("Exit the application"));
	connect(actExit, &QAction::triggered, this, &QWidget::close);

	// Undo
	const QIcon undoIcon = QIcon::fromTheme("edit-undo", QIcon(":/images/undo.png"));
	actUndo = new QAction(undoIcon, tr("&Undo"), this);
	actUndo->setShortcuts(QKeySequence::Undo);
	actUndo->setStatusTip(tr("Undo the last operation"));
	connect(actUndo, &QAction::triggered, this, &DedicatedSlaveUi::conn_actionUndo);

	// Redo
	actRedo = new QAction(tr("&Redo"), this);
	actRedo->setShortcuts(QKeySequence::Redo);
	actRedo->setStatusTip(tr("Redo the last operation"));
	connect(actRedo, &QAction::triggered, this, &DedicatedSlaveUi::conn_actionRedo);

	// Cut
	actCut = new QAction(tr("Cu&t"), this);
	actCut->setShortcuts(QKeySequence::Cut);
	actCut->setStatusTip(tr("Cut the current selection's contents to the clipboard"));
	connect(actCut, &QAction::triggered, this, &DedicatedSlaveUi::conn_actionCut);

	// Copy
	actCopy = new QAction(tr("&Copy"), this);
	actCopy->setShortcuts(QKeySequence::Copy);
	actCopy->setStatusTip(tr("Copy the current selection's contents to the clipboard"));
	connect(actCopy, &QAction::triggered, this, &DedicatedSlaveUi::conn_actionCopy);

	// Paste
	actPaste = new QAction(tr("&Paste"), this);
	actPaste->setShortcuts(QKeySequence::Paste);
	actPaste->setStatusTip(tr("Paste the clipboard's contents into the current selection"));
	connect(actPaste, &QAction::triggered, this, &DedicatedSlaveUi::conn_actionPaste);

	// Options
	actOptions = new QAction(tr("&Options..."), this);
	QList<QKeySequence> optionsShortcuts;
	optionsShortcuts.append(QKeySequence(Qt::CTRL + Qt::Key_F));
	optionsShortcuts.append(QKeySequence(Qt::CTRL + Qt::Key_P));
	actOptions->setShortcuts(optionsShortcuts);
	actOptions->setStatusTip(tr("Open the config options dialog"));
	connect(actOptions, &QAction::triggered, this, &DedicatedSlaveUi::conn_actionOptions);

	// Help
	actHelp = new QAction(tr("&Help"), this);
	actHelp->setStatusTip(tr("Getting started with DedicatedSlave"));
	connect(actHelp, &QAction::triggered, this, &DedicatedSlaveUi::conn_actionHelp);

	// Check Updates
	actCheckUpdates = new QAction(tr("&Check Updates"), this);
	actCheckUpdates->setStatusTip(tr("Check if exists new updates"));
	connect(actCheckUpdates, &QAction::triggered, this, &DedicatedSlaveUi::conn_actionCheckUpdates);

	// About
	actAbout = new QAction(tr("&About"), this);
	actAbout->setStatusTip(tr("Show the application's About box"));
	connect(actAbout, &QAction::triggered, this, &DedicatedSlaveUi::conn_actionAbout);

	// About Qt
	actAboutQt = new QAction(tr("About &Qt"), this);
	actAboutQt->setStatusTip(tr("Show the Qt library's About box"));
	connect(actAboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);
	connect(actAboutQt, &QAction::triggered, this, &DedicatedSlaveUi::conn_actionAboutQt);
}

/*!
 * \brief Function that initializate menus
 */
void DedicatedSlaveUi::initMenus()
{
	// File Menu
//	if(parentWin != 0) {
    //qDebug() << "\tQ_FUNC_INFO" << Q_FUNC_INFO;
//		qInfo() << "Q_FUNC_INFO:" << Q_FUNC_INFO;
//		QMenuBar *menu = parentWin->menuBar();
	menuFile = parentWin->menuBar()->addMenu(tr("&File"));
	menuFile->addAction(actNewInst);
	menuFile->addAction(actRemoveInst);
	menuFile->addAction(actRunInst);
	menuFile->addAction(actVerifyInst);
	menuFile->addAction(actBackupInst);
	menuFile->addAction(actRestoreInst);
	menuFile->addSeparator();
	menuFile->addAction(actExit);

	// Edit Menu
	menuEdit = parentWin->menuBar()->addMenu(tr("&Edit"));
	menuEdit->addAction(actUndo);
	menuEdit->addAction(actRedo);
	menuEdit->addSeparator();
	menuEdit->addAction(actCut);
	menuEdit->addAction(actCopy);
	menuEdit->addAction(actPaste);
	menuEdit->addSeparator();

	// View Menu
	menuView = parentWin->menuBar()->addMenu(tr("&View"));

	// Tools Menu
	menuTools = parentWin->menuBar()->addMenu(tr("&Tools"));
	menuTools->addSeparator();
	menuTools->addAction(actOptions);

	// Help Menu
	menuHelp = parentWin->menuBar()->addMenu(tr("&Help"));
	menuHelp->addAction(actHelp);
	menuHelp->addAction(actCheckUpdates);
	menuHelp->addSeparator();
	menuHelp->addAction(actAbout);
	menuHelp->addAction(actAboutQt);
}

void DedicatedSlaveUi::conn_actionHelp()
{
	QDesktopServices::openUrl(QUrl("https://enthdev.github.io/dedicatedslave/user-guide/gettingstarted/"));
	ui_infoLabel->setText(tr("Invoked <b>Help|Help</b>"));
}

void DedicatedSlaveUi::conn_actionCheckUpdates()
{
	ui_infoLabel->setText(tr("Invoked <b>Help|CheckUpdates</b>"));
}

void DedicatedSlaveUi::conn_actionAbout()
{
	ui_infoLabel->setText(tr("Invoked <b>Help|About</b>"));
	QMessageBox::about(this, tr("About Dedicated Slave"),
		tr("The <b>Dedicated Slave</b> is a cross platform desktop app "
			"tool to manage steam dedicated game servers with SteamCMD."
			"<p><a href='https://github.com/EnthDev/dedicatedslave'>Github Repository</a>"
			"<p><a href='https://enthdev.github.io/dedicatedslave/'>Website</a>"
			"<p><a href='https://enthdev.github.io/dedicatedslave/user-guide/gettingstarted/'>Website - Getting Started</a>"));
}

void DedicatedSlaveUi::conn_actionAboutQt()
{
	ui_infoLabel->setText(tr("Invoked <b>Help|About Qt</b>"));
}

void DedicatedSlaveUi::conn_actionVerifyInst()
{
	if(app_slcInstPos[0] != -1 && app_slcInstPos[1] != -1){
		QString instName = ui_instanceTable->item(app_slcInstPos[0], 0)->text();
		if(ds_app->hasInst(instName)){
			ds_app->verifyInstProgress(ui_instanceTable->item(app_slcInstPos[0], 0)->text());
			updateModelInstTable();
		}else{
			ui_infoLabel->setText(QString("Error: Instance '%1' does not exist").arg(instName));
		}
	}
}

void DedicatedSlaveUi::conn_actionRunInst()
{
	if(app_slcInstPos[0] != -1 && app_slcInstPos[1] != -1){
		QString instName = ui_instanceTable->item(app_slcInstPos[0], 0)->text();
		if(ds_app->hasInst(instName)){
			if(ds_app->hasReadyInst(instName)){
				ds_app->runInst(instName);
				updateModelInstTable();
			}else{
				ui_infoLabel->setText(QString("Error: Instance '%1' is not ready to run").arg(instName));
			}
		}else{
			ui_infoLabel->setText(QString("Error: Instance '%1' does not exist").arg(instName));
		}
	}
}

void DedicatedSlaveUi::conn_actionNewInstDialog()
{
	ui_newInstGroup = new QGroupBox;
	QLabel *labeltest = new QLabel(tr("Instance Game:"));
//	QRadioButton *radio = new QRadioButton(tr("Add Instance"));
	QVBoxLayout *vbox = new QVBoxLayout;
	QComboBox *comboGamesList = new QComboBox;
	connect(comboGamesList, SIGNAL(activated(int)), this, SLOT(slot_addInstanceCombo(int)));
	QPushButton *addButton = new QPushButton("OK");
	connect(addButton, &QAbstractButton::clicked, this, &DedicatedSlaveUi::conn_actionNewInst);
	QLineEdit *instNameLineEdit = new QLineEdit;
	QLineEdit *instDirLineEdit = new QLineEdit("etcinstances");
	connect(instNameLineEdit, SIGNAL(textEdited(QString)), this, SLOT(slot_addInstNameEdit(QString)));
	connect(instDirLineEdit, SIGNAL(textEdited(QString)), this, SLOT(slot_addInstDirEdit(QString)));
	// Unlike textChanged(), this signal is not emitted when the text is changed programmatically, for example, by calling setText().
	comboGamesList->addItem("-");
	comboGamesList->addItem("Counter-Strike: Global Offensive"); // 1
	comboGamesList->addItem("Rust"); // 2
//	vbox->addWidget(radio);
	vbox->addWidget(labeltest);
	vbox->addWidget(comboGamesList);
	vbox->addWidget(addButton);
	vbox->addWidget(instNameLineEdit);
	vbox->addWidget(instDirLineEdit);
	ui_newInstGroup->setLayout(vbox);
	ui_newInstGroup->show();
	ui_infoLabel->setText(tr("Invoked <b>File|New</b>"));
}

void DedicatedSlaveUi::conn_actionRemoveInst()
{
	if(app_slcInstPos[0] != -1 && app_slcInstPos[1] != -1){
		QMessageBox::StandardButton removeReply;
		removeReply = QMessageBox::question(this,
			"Remove Instace",
			QString("Do you really want to remove instance '%1'").arg(ui_instanceTable->item(app_slcInstPos[0], 0)->text()),
			QMessageBox::Yes|QMessageBox::No);
		if(removeReply == QMessageBox::Yes){
			QMessageBox::StandardButton removeFileReply;
			removeFileReply = QMessageBox::question(this,
				"Remove Instace",
				"Do you want to remove all instance files?",
				QMessageBox::Yes|QMessageBox::No);
            if(removeFileReply == QMessageBox::Yes)
				ds_app->removeInst(ui_instanceTable->item(app_slcInstPos[0], 0)->text(), true);
            else
				ds_app->removeInst(ui_instanceTable->item(app_slcInstPos[0], 0)->text(), false);
			updateModelInstTable();
		}
	}
}

void DedicatedSlaveUi::conn_actionNewInst()
{
	ui_newInstGroup->hide();
	if(!app_newIntsName.isEmpty()){
		if(!ds_app->hasInst(app_newIntsName)){
			ds_app->addInst(app_newIntsName, app_newInstGame);
			updateModelInstTable();
			app_newInstGame = "";
			ui_infoLabel->setText(QString("Invoked New Instance <b>%1</b> (<b>%2</b>) - <b>%3</b>").arg(app_newIntsName).arg(ui_instanceTable->rowCount()-1).arg(app_newInstGame));
		}else{
			ui_infoLabel->setText(QString("Error: New Instance name already exist (<b>%1</b>)").arg(app_newIntsName));
		}
	}else{
		ui_infoLabel->setText("Error: New Instance name cannot be empty.");
	}
}

void DedicatedSlaveUi::conn_actionRestore()
{
	ui_infoLabel->setText(tr("Invoked <b>File|Restore</b>"));
}

void DedicatedSlaveUi::conn_actionBackup()
{
	ui_infoLabel->setText(tr("Invoked <b>File|Save</b>"));
	QMimeDatabase mimeDatabase;
	QString fileName = QFileDialog::getSaveFileName(this,
		tr("Choose a file name"), ".",
		mimeDatabase.mimeTypeForName("text/html").filterString());
	if (fileName.isEmpty())
		return;
	QFile file(fileName);
	if (!file.open(QFile::WriteOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("Dock Widgets"),
			tr("Cannot write file %1:\n%2.")
				.arg(QDir::toNativeSeparators(fileName), file.errorString()));
		return;
	}

	QTextStream out(&file);
	QApplication::setOverrideCursor(Qt::WaitCursor);
	out << ui_textEdit->toHtml();
	QApplication::restoreOverrideCursor();

	parentWin->statusBar()->showMessage(tr("Saved '%1'").arg(fileName), 2000);
}

void DedicatedSlaveUi::conn_actionUndo()
{
	ui_infoLabel->setText(tr("Invoked <b>Edit|Undo</b>"));
	ui_textEdit->document()->undo();
}

void DedicatedSlaveUi::conn_actionRedo()
{
	ui_infoLabel->setText(tr("Invoked <b>Edit|Redo</b>"));
}

void DedicatedSlaveUi::conn_actionCut()
{
	ui_infoLabel->setText(tr("Invoked <b>Edit|Cut</b>"));
}

void DedicatedSlaveUi::conn_actionCopy()
{
	ui_infoLabel->setText(tr("Invoked <b>Edit|Copy</b>"));
}

void DedicatedSlaveUi::conn_actionPaste()
{
	ui_infoLabel->setText(tr("Invoked <b>Edit|Paste</b>"));
}

void DedicatedSlaveUi::conn_actionOptions()
{
	ui_infoLabel->setText(tr("Invoked <b>Tools|Options...</b>"));
	ui_dialogConfig = new ConfigDialog(ds_app);
	ui_dialogConfig->show();
}

void DedicatedSlaveUi::slot_addInstanceCombo(int index)
{
	switch (index) {
		case 1:
			app_newInstGame = "csgo";
			break;
		case 2:
			app_newInstGame = "rust";
			break;
		}
}

void DedicatedSlaveUi::slot_addInstNameEdit(QString instanceName)
{
	app_newIntsName = instanceName;
}

void DedicatedSlaveUi::slot_addInstDirEdit(QString instanceDir)
{
	app_newInstDir = instanceDir;
}

void DedicatedSlaveUi::slot_instanceSelect(int row, int column)
{
	app_slcInstPos[0] = row;
	app_slcInstPos[1] = column;
	QHashIterator<QString, GameInstance*> i = ds_app->listInst();
	while(i.hasNext()){
		i.next();
		if(i.key() == ui_instanceTable->item(app_slcInstPos[0], 0)->text()){
			GameInstance *gi = i.value();
			dockOptions->updateModelInst(i.key(), gi->getServerName(), gi->getNumPlayers());
		}
	}
	ui_infoLabel->setText(QString("Selected Inst <b>%1</b>:<b>%2</b>").arg(row).arg(column));
}
