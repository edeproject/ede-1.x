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

#include "propdialog.h"
#include "edeskicon.h"
#include <edeconf.h>


static Icon *ds_icon;

Fl_Window* i_propertieswindow;

Fl_Group* i_icontab;

Fl_Box* pr_icon;

Fl_Box* pr_name;

Fl_Box* pr_size;

Fl_Box* pr_exec;

Fl_Group* i_settingstab;

Fl_Output* i_link;

Fl_Input* i_name;

Fl_Input* i_location;

static void cb_(Fl_Button*, void*) {
  char *file_types = _("Executables (*.*), *, All files (*.*), *");
  const char *f = fl_select_file(i_location->value(), file_types, _("Open location..."));
  if (f) i_location->value(f);
}

Fl_Input* i_filename;

static void cb_1(Fl_Button*, void*) {
  char *file_types = _("Png images (*.png), *.png, Jpeg Images (*.jpeg), *.{jpeg|jpg}, Bmp Files (*.bmp), *.bmp, Gif Files (*.gif), *.gif, Xpm Files (*.xpm), *.xpm, All files (*.*), *");
  const char *f = fl_select_file(PREFIX"/share/ede/icons/48x48/", file_types, _("Icon file selection"));    	
  if (f) i_filename->value(f);
}

static void cb_Apply(Fl_Button*, void*) {
  save_icon(ds_icon);
}

static void cb_Close(Fl_Button*, void*) {
  i_propertieswindow->hide();
}

void property_dialog(Fl_Widget *, Icon *icon, bool show_settings) {
  Fl_Window* w;
  if(i_propertieswindow) {
  	update_property_dialog(icon);
  	update_iconeditdialog(icon);
  	ds_icon=icon;
  	if(show_settings) { i_icontab->hide(); i_settingstab->show(); }
  	i_propertieswindow->exec();
  	return;
  }
   {Fl_Window* o = i_propertieswindow = new Fl_Window(295, 310, _("Icon properties"));
    w = o;
     {Fl_Tabs* o = new Fl_Tabs(5, 5, 285, 270);
       {Fl_Group* o = i_icontab = new Fl_Group(0, 20, 285, 247, _("Icon"));
         {Fl_Box* o = pr_icon = new Fl_Box(10, 10, 60, 55);
          o->box(FL_THIN_DOWN_BOX);
        }
         {Fl_Box* o = new Fl_Box(10, 75, 65, 38, _("Name:"));
          o->align(133|FL_ALIGN_INSIDE);
        }
         {Fl_Box* o = new Fl_Box(10, 120, 65, 33, _("Size:"));
          o->align(133|FL_ALIGN_INSIDE);
        }
         {Fl_Box* o = new Fl_Box(10, 170, 65, 65, _("Command:"));
          o->align(133|FL_ALIGN_INSIDE);
        }
         {Fl_Box* o = pr_name = new Fl_Box(75, 73, 200, 40);
          o->label_size(20);
          o->align(197|FL_ALIGN_INSIDE);
        }
         {Fl_Box* o = pr_size = new Fl_Box(80, 118, 195, 35);
          o->align(197|FL_ALIGN_INSIDE);
        }
         {Fl_Box* o = pr_exec = new Fl_Box(80, 170, 195, 63);
          o->align(197|FL_ALIGN_INSIDE);
        }
        o->end();
      }
       {Fl_Group* o = i_settingstab = new Fl_Group(0, 20, 285, 250, _("Settings"));
        o->hide();
         {Fl_Output* o = i_link = new Fl_Output(10, 20, 265, 22, _("Link file:"));
          o->color((Fl_Color)0xffffff00);
          o->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
        }
         {Fl_Input* o = i_name = new Fl_Input(10, 77, 265, 22, _("Icon name:"));
          o->align(133);
        }
         {Fl_Input* o = i_location = new Fl_Input(10, 117, 215, 22, _("Location to open:"));
          o->align(133);
        }
         {Fl_Button* o = new Fl_Button(230, 117, 45, 22, _("..."));
          o->label_type(FL_ENGRAVED_LABEL);
          o->callback((Fl_Callback*)cb_);
        }
         {Fl_Input* o = i_filename = new Fl_Input(10, 162, 215, 22, _("Icon filename:"));
          o->align(133);
        }
         {Fl_Button* o = new Fl_Button(230, 162, 45, 22, _("..."));
          o->label_type(FL_ENGRAVED_LABEL);
          o->callback((Fl_Callback*)cb_1);
        }
         {Fl_Button* o = new Fl_Button(210, 215, 65, 25, _("&Apply"));
          o->callback((Fl_Callback*)cb_Apply);
        }
        o->end();
      }
      o->end();
    }
     {Fl_Button* o = new Fl_Button(200, 280, 90, 25, _("&Close"));
      o->callback((Fl_Callback*)cb_Close);
    }
    o->end();
  }
  update_property_dialog(icon);
  update_iconeditdialog(icon);
  ds_icon=icon;
  i_propertieswindow->end();
  if(show_settings) { i_icontab->hide(); i_settingstab->show(); }
  i_propertieswindow->exec();
}
