module dedicatedslave.loader;

import std.zlib;
import std.file : exists, read, rename, mkdir, rmdirRecurse;

class Loader {
	this() {
		if(!exists(".dedicatedslave"))
			installEnvironment();
	}

	void installEnvironment()
	{
		enum {
			tmpPath = "._dedicatedslave/",
			realPath = ".dedicatedslave/"
		}
		_changeLogState("Installing the environment...");
		import std.json : JSONValue, parseJSON;
		immutable JSONValue envconfig = parseJSON(cast(string)read("assets/envconfig.json"));
		if(exists(tmpPath))
			rmdirRecurse(tmpPath);
		mkdir(tmpPath);

		version(Windows) enum os_version = "windows";
		else version(linux) enum os_version = "linux";
		else version(OSX) enum os_version = "macos";
		immutable string url = envconfig[os_version].str;
		_changeLogState("Downloading " ~ url ~ "...");
		import std.net.curl : download;
		import std.path : extension;
		immutable string steamcmd_filename = tmpPath~"steamcmd"~extension(url);
		download(url, steamcmd_filename);
		_changeLogState("Finishing setup...");
		rename(tmpPath, realPath);
	}

protected:
	void _internalLogger(immutable string msg) {}

private:
	void _changeLogState(immutable string msg)
	{
		import std.experimental.logger : info;
		info(msg);
		_internalLogger(msg);
	}
}
