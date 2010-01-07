PROJECT = assistant
TARGETTYPE = app
UID2 = 100039ce
UID3 = 100098e7

RSSFILES = \
	$(PROJECT)_caption.rsc \
	$(PROJECT).rsc

SRCFILES = \
	framework/application.cpp \
	framework/appui.cpp \
	framework/document.cpp \
	framework/main.cpp

LIBRARY = \
	apparc.lib \
	charconv.lib \
	cone.lib \
	eikcore.lib \
	euser.lib \
	flogger.lib \
	gdi.lib \
	ws32.lib \
	ttk.lib
