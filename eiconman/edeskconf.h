/*
 * $Id$
 *
 * Eiconman, desktop and icon manager
 * Part of Equinox Desktop Environment (EDE).
 * Copyright (c) 2000-2006 EDE Authors.
 *
 * This program is licenced under terms of the 
 * GNU General Public Licence version 2 or newer.
 * See COPYING for details.
 */

#ifndef edeskconf_h
#define edeskconf_h
#include <efltk/Fl.h>
#include <efltk/Fl_Locale.h>
#include <efltk/Fl_Window.h>
extern void bg_prop_cb(Fl_Window*, void*);
extern Fl_Window* bg_prop_window;
#include <efltk/Fl_Group.h>
#include <efltk/Fl_Box.h>
extern Fl_Box* mini_image_box;
#include <efltk/Fl_Light_Button.h>
extern void bg_image_color(Fl_Light_Button*, void*);
extern Fl_Light_Button* color_button;
#include <efltk/Fl_Check_Button.h>
extern void bg_image_use(Fl_Check_Button*, void*);
extern Fl_Check_Button* use_button;
#include <efltk/Fl_Divider.h>
extern Fl_Group* bg_image_group;
#include <efltk/Fl_Input.h>
extern void bg_image_input(Fl_Input*, void*);
extern Fl_Input* image_input;
#include <efltk/Fl_Button.h>
extern void bg_image_browse(Fl_Button*, void*);
#include <efltk/Fl_Value_Slider.h>
extern void bg_image_opacity(Fl_Value_Slider*, void*);
extern Fl_Value_Slider* opacity_slider;
#include <efltk/Fl_Choice.h>
extern void bg_image_mode(Fl_Choice*, void*);
extern Fl_Choice* mode_choice;
#include <efltk/Fl_Item.h>
extern void bg_ok(Fl_Button*, void*);
extern void bg_apply(Fl_Button*, void*);
void make_desktop_properties();
#endif
