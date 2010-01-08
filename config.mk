PROJECT = assistant
TARGETTYPE = exe
ifeq ($(TARGETTYPE), exe)
UID1 = 1000007a
UID2 = 00000000
else
UID1 = 10000079
UID2 = 1000008d
endif
UID3 = a1986132
SECUREID = a1986132
VENDORID = 0

CAPABILITY = NONE

RSSFILES = \
	$(PROJECT)_loc.rss \
	$(PROJECT)_reg.rss \
	$(PROJECT).rss

IMGFILES = \
	gfx/selectmark.bmp \
	gfx/nullmark.bmp \
	gfx/default.bmp

SRCFILES = \
	framework/application.cpp \
	framework/document.cpp \
	framework/main.cpp \
	ui/mainview.cpp \
	ui/maincontainer.cpp \
	model/appitem.cpp \
	model/appmanager.cpp \
	framework/appui.cpp \
	ui/settingsview.cpp \
	ui/applistview.cpp \
	ui/applistcontainer.cpp \
	ui/settingscontainer.cpp

LIBRARY = \
	euser.lib \
	apparc.lib \
	avkon.lib \
	charconv.lib \
	cone.lib \
	eikcore.lib \
	fbscli.lib \
	flogger.lib \
	gdi.lib \
	imageconversion.lib \
	ws32.lib \
	ttk_a1986131.lib
