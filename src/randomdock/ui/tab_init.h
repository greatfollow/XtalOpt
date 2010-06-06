/**********************************************************************
  RandomDock -- A tool for analysing a matrix-substrate docking problem

  Copyright (C) 2009 by David Lonie

  This file is part of the Avogadro molecular editor project.
  For more information, see <http://avogadro.openmolecules.net/>

  This library is free software; you can redistribute it and/or modify
  it under the terms of the GNU Library General Public License as
  published by the Free Software Foundation; either version 2.1 of the
  License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public icense for more details.
 ***********************************************************************/

#ifndef TAB_INIT_H
#define TAB_INIT_H

#include "ui_tab_init.h"

namespace RandomDock {
  class RandomDockDialog;
  class RandomDock;

  class TabInit : public QObject
  {
    Q_OBJECT

  public:
    explicit TabInit( RandomDockDialog *dialog, RandomDock *opt );
    virtual ~TabInit();

    enum Columns	{ Num = 0, Stoich, Filename };

    QWidget *getTabWidget() {return m_tab_widget;};

  public slots:
    void lockGUI();
    void readSettings(const QString &filename = "");
    void writeSettings(const QString &filename = "");
    void updateGUI();
    void disconnectGUI();
    void updateParams();
    void substrateBrowse();
    void substrateCurrent();
    void matrixAdd();
    void matrixRemove();
    void matrixCurrent();
    void readFiles();

  signals:

  private:
    Ui::Tab_Init ui;
    QWidget *m_tab_widget;
    RandomDockDialog *m_dialog;
    RandomDock *m_opt;
  };
}

#endif
