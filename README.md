Getting everything built
========================


Requirements
------------
1. [Android SDK](http://developer.android.com/sdk/index.html)
2. [Android NDK](http://developer.android.com/tools/sdk/ndk/index.html) (revision 8b)
3. [Apache Ant](http://ant.apache.org)
4. [SCons](http://www.scons.org)


Dependencies
------------
SDL (1.2.15), libpng (1.2.50), lua (5.1.5), tolua++ (trunk)


Cloning
-------
Make a directory and clone Stratagus and libs repos to it:

	mkdir _some_dir_
	cd _some_dir_
	git clone https://github.com/drodin/Stratagus.git
	git clone https://github.com/drodin/SDL.git
	git clone https://github.com/drodin/libpng.git
	git clone https://github.com/drodin/lua.git
	git clone https://github.com/drodin/toluapp.git


Building Lua
------------

	cd lua
	make _platform_

You need to specify the _platform_ to build for. Run make without params to see the list of supported platforms.


Building tolua++
----------------

	cd ../toluapp
	scons


Generating tolua.cpp
--------------------

	cd ../Stratagus/src/tolua
	./runtolua.sh


Building Stratagus apk
----------------------

	cd ../../android
	ndk-build
	ant debug

Grab your .apk in the _bin_ directory ;)
