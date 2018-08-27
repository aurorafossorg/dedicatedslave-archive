module dedicatedslave.gui.splash;

import gtk.Image;
import gtk.Application;
import gtk.ApplicationWindow;
import gtk.ProgressBar;
import gtk.Box;
import gtk.Label;
import gdk.RGBA;
import glib.Timeout;
import std.stdio;
import core.time;
import core.thread;
import dedicatedslave.loader;

class SplashWindow : ApplicationWindow {
	this(Application application)
	{
		super(application);

		setTitle("DedicatedSlave");
		overrideBackgroundColor(GtkStateFlags.NORMAL, new RGBA(1.0, 1.0,1.0));
		setBorderWidth(10);
		setDecorated(false);
		setPosition(GtkWindowPosition.CENTER_ALWAYS);
		setResizable(false);

		Box box = new Box(GtkOrientation.VERTICAL, 0);
		box.setCenterWidget(new Image("assets/logo.svg"));
		ProgressBar pb = new ProgressBar();
		Label statusLbl = new Label("Loading...");
		statusLbl.overrideColor(GtkStateFlags.NORMAL, new RGBA(0.0, 0.0, 0.0));
		box.packEnd(statusLbl, true, true, 0);
		box.packEnd(pb, true, true, 10);
		pb.pulse();
		add(box);

		showAll();

		MonoTime timeBefore = MonoTime.currTime;
		new Loader();
		MonoTime timeAfter = MonoTime.currTime;
		Duration timeElapsed = timeAfter - timeBefore;

		if(timeElapsed.total!"msecs" >= 1000)
			destroy();

		new Timeout(
			cast(uint)(1000 - timeElapsed.total!"msecs"),
			{
				destroy();
				return false;
			});
	}
}
