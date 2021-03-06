/*
 * $Id$
 *
 * Einstaller, frontend for package installation
 * Part of Equinox Desktop Environment (EDE).
 * Copyright (c) 2000-2006 EDE Authors.
 *
 * This program is licenced under terms of the 
 * GNU General Public Licence version 2 or newer.
 * See COPYING for details.
 */

#ifndef einstaller_h
#define einstaller_h
#include <efltk/Fl.h>
#include <efltk/Fl_Locale.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Box.h>
#include <efltk/Fl_Group.h>
extern Fl_Group* steps_group;
extern Fl_Group* step1_group;
#include <efltk/Fl_Input.h>
extern Fl_Input* package_name_input;
#include <efltk/Fl_Button.h>
#include <efltk/Fl_File_Dialog.h>
#include <efltk/Fl_Check_Button.h>
extern Fl_Check_Button* nodeps_button;
extern Fl_Group* step2_group;
#include <efltk/Fl_Text_Editor.h>
extern Fl_Text_Editor* result_output;
#include <efltk/Fl_ProgressBar.h>
extern Fl_ProgressBar* install_progress;
extern Fl_Button* prev_button;
extern Fl_Button* next_button;
#endif
