module dedicatedslave.gui.app;

import gio.Application : GioApplication = Application;
import gtk.Application;
import dedicatedslave.gui.splash;
import dedicatedslave.gui.mainwindow;

int main(string[] args)
{
	auto application = new Application("enthdev.dedicatedslave.gui", GApplicationFlags.FLAGS_NONE);
	application.addOnActivate(delegate void(GioApplication app) {
			new SplashWindow(application);
			new MainWindow(application);
		});
	return application.run(args);
}
