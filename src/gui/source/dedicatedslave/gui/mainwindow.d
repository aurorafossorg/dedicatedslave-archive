module dedicatedslave.gui.mainwindow;

import gtk.ApplicationWindow;
import gtk.Application;
import gtk.Label;

class MainWindow : ApplicationWindow
{
	this(Application application)
	{
		super(application);
		setTitle("DedicatedSlave");
		setBorderWidth(10);
		add(new Label("Hello World"));

		showAll();
	}
}
