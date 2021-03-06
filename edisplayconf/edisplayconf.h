/*
 * $Id$
 *
 * Edisplayconf, utility for display configuration
 * Part of Equinox Desktop Environment (EDE).
 * Copyright (c) 2000-2006 EDE Authors.
 *
 * This program is licenced under terms of the 
 * GNU General Public Licence version 2 or newer.
 * See COPYING for details.
 */


#ifndef edisplayconf_h
#define edisplayconf_h
#include <efltk/Fl.h>
#include <efltk/Fl_Locale.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Tabs.h>
#include <efltk/Fl_Group.h>
#include <efltk/Fl_Value_Slider.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_Check_Button.h>
#include <efltk/Fl_Box.h>
#include <efltk/Fl_Round_Button.h>
#include <efltk/Fl_Return_Button.h>

class edisplayconf  {
public:
  bool _finish;
  edisplayconf();
private:
  Fl_Window *win;
  inline void cb_win_i(Fl_Window*, void*);
  static void cb_win(Fl_Window*, void*);
      Fl_Group *group_mouse;
public:
        Fl_Value_Slider *slider_accel;
        Fl_Value_Slider *slider_thresh;
private:
      Fl_Group *group_bell;
public:
        Fl_Value_Slider *slider_volume;
        Fl_Value_Slider *slider_pitch;
        Fl_Value_Slider *slider_duration;
private:
        inline void cb_Test_i(Fl_Button*, void*);
        static void cb_Test(Fl_Button*, void*);
      Fl_Group *group_keyboard;
public:
        Fl_Check_Button *check_autorepeat;
        Fl_Value_Slider *slider_click;
      Fl_Group *group_screen;
        Fl_Button *but_activate;
private:
        inline void cb_but_activate_i(Fl_Button*, void*);
        static void cb_but_activate(Fl_Button*, void*);
public:
        Fl_Value_Slider *slider_delay;
        Fl_Check_Button *check_blanking;
        Fl_Value_Slider *slider_pattern;
          Fl_Round_Button *radio_blank;
private:
          inline void cb_radio_blank_i(Fl_Round_Button*, void*);
          static void cb_radio_blank(Fl_Round_Button*, void*);
public:
          Fl_Round_Button *radio_pattern;
private:
          inline void cb_radio_pattern_i(Fl_Round_Button*, void*);
          static void cb_radio_pattern(Fl_Round_Button*, void*);
    inline void cb_Cancel_i(Fl_Button*, void*);
    static void cb_Cancel(Fl_Button*, void*);
public:
    Fl_Button *but_kbd_apply;
private:
    inline void cb_but_kbd_apply_i(Fl_Button*, void*);
    static void cb_but_kbd_apply(Fl_Button*, void*);
    inline void cb_OK_i(Fl_Return_Button*, void*);
    static void cb_OK(Fl_Return_Button*, void*);
public:
  ~edisplayconf();
  void Run();
  void make_window();
  void radioCB();
};
int main(int ac,char **av);
extern edisplayconf *app;
#endif
