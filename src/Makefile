#############################################################################
# Makefile for building: ../bin
# Generated by qmake (2.01a) (Qt 4.5.2) on: Sat May 1 10:12:52 2010
# Project:  bin.pro
# Template: app
# Command: /usr/bin/qmake -unix -o Makefile bin.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -I.
LINK          = g++
LFLAGS        = -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib -lQtGui -lQtCore -lpthread
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -sf
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = config.cpp \
		evolutionManager.cpp \
		evolutionManagerTab.cpp \
		main.cpp \
		tabDialog.cpp \
		taskTab.cpp \
		turtleGraphic.cpp \
		turtleWidget.cpp moc_evolutionManager.cpp \
		moc_evolutionManagerTab.cpp \
		moc_tabDialog.cpp \
		moc_taskTab.cpp \
		moc_turtleWidget.cpp
OBJECTS       = config.o \
		evolutionManager.o \
		evolutionManagerTab.o \
		main.o \
		tabDialog.o \
		taskTab.o \
		turtleGraphic.o \
		turtleWidget.o \
		moc_evolutionManager.o \
		moc_evolutionManagerTab.o \
		moc_tabDialog.o \
		moc_taskTab.o \
		moc_turtleWidget.o
DIST          = /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		bin.pro
QMAKE_TARGET  = bin
DESTDIR       = ../
TARGET        = ../bin

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	@$(CHK_DIR_EXISTS) ../ || $(MKDIR) ../ 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: bin.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -unix -o Makefile bin.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/libQtGui.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -unix -o Makefile bin.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/bin1.0.0 || $(MKDIR) .tmp/bin1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/bin1.0.0/ && $(COPY_FILE) --parents config.h evolutionManager.h evolutionManagerTab.h tabDialog.h taskTab.h turtleGraphic.h turtleWidget.h .tmp/bin1.0.0/ && $(COPY_FILE) --parents config.cpp evolutionManager.cpp evolutionManagerTab.cpp main.cpp tabDialog.cpp taskTab.cpp turtleGraphic.cpp turtleWidget.cpp .tmp/bin1.0.0/ && (cd `dirname .tmp/bin1.0.0` && $(TAR) bin1.0.0.tar bin1.0.0 && $(COMPRESS) bin1.0.0.tar) && $(MOVE) `dirname .tmp/bin1.0.0`/bin1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/bin1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_evolutionManager.cpp moc_evolutionManagerTab.cpp moc_tabDialog.cpp moc_taskTab.cpp moc_turtleWidget.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_evolutionManager.cpp moc_evolutionManagerTab.cpp moc_tabDialog.cpp moc_taskTab.cpp moc_turtleWidget.cpp
moc_evolutionManager.cpp: config.h \
		turtleGraphic.h \
		evolutionManager.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) evolutionManager.h -o moc_evolutionManager.cpp

moc_evolutionManagerTab.cpp: config.h \
		turtleWidget.h \
		evolutionManager.h \
		turtleGraphic.h \
		evolutionManagerTab.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) evolutionManagerTab.h -o moc_evolutionManagerTab.cpp

moc_tabDialog.cpp: evolutionManagerTab.h \
		config.h \
		turtleWidget.h \
		evolutionManager.h \
		turtleGraphic.h \
		taskTab.h \
		tabDialog.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) tabDialog.h -o moc_tabDialog.cpp

moc_taskTab.cpp: config.h \
		turtleWidget.h \
		turtleGraphic.h \
		taskTab.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) taskTab.h -o moc_taskTab.cpp

moc_turtleWidget.cpp: config.h \
		turtleWidget.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) turtleWidget.h -o moc_turtleWidget.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

####### Compile

config.o: config.cpp config.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o config.o config.cpp

evolutionManager.o: evolutionManager.cpp evolutionManager.h \
		config.h \
		turtleGraphic.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o evolutionManager.o evolutionManager.cpp

evolutionManagerTab.o: evolutionManagerTab.cpp evolutionManagerTab.h \
		config.h \
		turtleWidget.h \
		evolutionManager.h \
		turtleGraphic.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o evolutionManagerTab.o evolutionManagerTab.cpp

main.o: main.cpp tabDialog.h \
		evolutionManagerTab.h \
		config.h \
		turtleWidget.h \
		evolutionManager.h \
		turtleGraphic.h \
		taskTab.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

tabDialog.o: tabDialog.cpp tabDialog.h \
		evolutionManagerTab.h \
		config.h \
		turtleWidget.h \
		evolutionManager.h \
		turtleGraphic.h \
		taskTab.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tabDialog.o tabDialog.cpp

taskTab.o: taskTab.cpp taskTab.h \
		config.h \
		turtleWidget.h \
		turtleGraphic.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o taskTab.o taskTab.cpp

turtleGraphic.o: turtleGraphic.cpp turtleGraphic.h \
		config.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o turtleGraphic.o turtleGraphic.cpp

turtleWidget.o: turtleWidget.cpp turtleWidget.h \
		config.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o turtleWidget.o turtleWidget.cpp

moc_evolutionManager.o: moc_evolutionManager.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_evolutionManager.o moc_evolutionManager.cpp

moc_evolutionManagerTab.o: moc_evolutionManagerTab.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_evolutionManagerTab.o moc_evolutionManagerTab.cpp

moc_tabDialog.o: moc_tabDialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_tabDialog.o moc_tabDialog.cpp

moc_taskTab.o: moc_taskTab.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_taskTab.o moc_taskTab.cpp

moc_turtleWidget.o: moc_turtleWidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_turtleWidget.o moc_turtleWidget.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

