/*
 * $Id$
 *
 * Ewmconf, window manager configuration tool
 * Part of Equinox Desktop Environment (EDE).
 * Copyright (c) 2000-2006 EDE Authors.
 *
 * This program is licenced under terms of the 
 * GNU General Public Licence version 2 or newer.
 * See COPYING for details.
 */

#include "ewmconf.h"
#include <efltk/Fl_Color_Chooser.h>
#include <efltk/Fl_File_Dialog.h>
#include <efltk/Fl_Config.h>
#include <efltk/Fl_Locale.h>
#include <edeconf.h>
#include "ewm.h"

static void cb_Text(Fl_Choice* o, void*) {
  title_align = (int)o->value();
}

static void cb_Height(Fl_Value_Input* o, void*) {
  title_height = (int)o->value();
}

Fl_Button* titlebarLabelColorButton;

static void cb_titlebarLabelColorButton(Fl_Button*, void*) {
  changeBoxColor(titlebarLabelColorButton);
  title_normal_color_text = (int) titlebarLabelColorButton->color();
}

Fl_Button* titlebarColorButton;

static void cb_titlebarColorButton(Fl_Button*, void*) {
  changeBoxColor(titlebarColorButton);
  title_normal_color = (int) titlebarColorButton->color();
}

Fl_Button* titlebarActiveLabelColorButton;

static void cb_titlebarActiveLabelColorButton(Fl_Button*, void*) {
  changeBoxColor(titlebarActiveLabelColorButton);
  title_active_color_text = (int) titlebarActiveLabelColorButton->color();
}

Fl_Button* titlebarActiveColorButton;

static void cb_titlebarActiveColorButton(Fl_Button*, void*) {
  changeBoxColor(titlebarActiveColorButton);
  title_active_color  = (int) titlebarActiveColorButton->color();
}

Fl_Choice* titlebarDrawGrad;

static void cb_titlebarDrawGrad(Fl_Choice*, void*) {
  title_draw_grad = titlebarDrawGrad->value();
}

Fl_Check_Button* useThemeButton;

static void cb_useThemeButton(Fl_Check_Button*, void*) {
  if (useThemeButton->value()) {
  	themePathInput->activate();
  	browse_btn->activate();
  	titlebarDrawGrad->deactivate();
  	titlebarColorButton->deactivate();
  	titlebarActiveColorButton->deactivate();
  }
  else
  {
  	themePathInput->deactivate();
  	browse_btn->deactivate();
  	titlebarDrawGrad->activate();
  	titlebarColorButton->activate();
  	titlebarActiveColorButton->activate();
  
  }
  
  use_theme = useThemeButton->value();
}

Fl_Input* themePathInput;

static void cb_themePathInput(Fl_Input*, void*) {
  theme_path = themePathInput->value();
}

Fl_Button* browse_btn;

static void cb_browse_btn(Fl_Button*, void*) {
  char *file_types = _("Themes (*.theme), *.theme, All files (*.*), *");
  Fl_String default_path = themePathInput->value();
  if (default_path.empty()) default_path = PREFIX"/share/ede/wm-themes/"; 
  const char *fileName = fl_select_file(default_path, file_types, _("Themes..."));    
  if (fileName) { 
    themePathInput->value(fileName);
    theme_path = fileName;
  }
;}

Fl_Check_Button* animateButton;

static void cb_animateButton(Fl_Check_Button*, void*) {
  if(animateButton->value()) animateSlider->activate();
  else animateSlider->deactivate();
  animate = animateButton->value();
}

Fl_Value_Slider* animateSlider;

static void cb_animateSlider(Fl_Value_Slider*, void*) {
  animate_speed = (int)animateSlider->value();
}

Fl_Check_Button* opaqueResize;

static void cb_opaqueResize(Fl_Check_Button*, void*) {
  opaque_resize = opaqueResize->value()
;}

static void cb_OK(Fl_Button*, void*) {
  writeConfiguration();
  applyConfiguration();
  exit(0);
}

static void cb_Apply(Fl_Button*, void*) {
  writeConfiguration();
  applyConfiguration();
}

static void cb_Cancel(Fl_Button*, void*) {
  exit(0);
}

int main (int argc, char **argv) {

  Fl_Window* w;
  fl_init_locale_support("ewmconf", PREFIX"/share/locale");
  readConfiguration();
   {Fl_Window* o = new Fl_Window(320, 370, _("Window manager settings"));
    w = o;
     {Fl_Tabs* o = new Fl_Tabs(2, 5, 318, 325);
      o->color((Fl_Color)16);
       {Fl_Group* o = new Fl_Group(1, 29, 316, 295, _("&Titlebar"));
        o->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
         {Fl_Choice* o = new Fl_Choice(83, 13, 105, 22, _("Text align:")); o->begin();
          o->callback((Fl_Callback*)cb_Text);
          new Fl_Item(_("Left"));
          new Fl_Item(_("Right"));
          new Fl_Item(_("Center"));
          o->value(title_align);
          o->end();
        }
         {Fl_Value_Input* o = new Fl_Value_Input(243, 13, 60, 22, _("Height:"));
          o->minimum(10);
          o->maximum(50);
          o->step(1);
          o->value(20);
          o->callback((Fl_Callback*)cb_Height);
          o->value(title_height);
        }
         {Fl_Button* o = titlebarLabelColorButton = new Fl_Button(85, 55, 60, 20, _("Titlebar label color: "));
          o->box(FL_DOWN_BOX);
          o->callback((Fl_Callback*)cb_titlebarLabelColorButton);
          o->align(132);
          o->color((Fl_Color)title_normal_color_text);
        }
         {Fl_Button* o = titlebarColorButton = new Fl_Button(85, 120, 60, 20, _("Titlebar color: "));
          o->box(FL_DOWN_BOX);
          o->callback((Fl_Callback*)cb_titlebarColorButton);
          o->align(132);
          o->color((Fl_Color) title_normal_color);
        }
         {Fl_Group* o = new Fl_Group(153, 45, 160, 110);
           {Fl_Button* o = titlebarActiveLabelColorButton = new Fl_Button(90, 10, 60, 20, _("Titlebar active label color: "));
            o->box(FL_DOWN_BOX);
            o->callback((Fl_Callback*)cb_titlebarActiveLabelColorButton);
            o->align(132);
            o->color((Fl_Color) title_active_color_text);
          }
           {Fl_Button* o = titlebarActiveColorButton = new Fl_Button(90, 75, 60, 20, _("Titlebar active color: "));
            o->box(FL_DOWN_BOX);
            o->callback((Fl_Callback*)cb_titlebarActiveColorButton);
            o->align(132);
            o->color((Fl_Color)title_active_color);
          }
          o->end();
        }
         {Fl_Choice* o = titlebarDrawGrad = new Fl_Choice(85, 157, 163, 23, _("Box type:")); o->begin();
          o->callback((Fl_Callback*)cb_titlebarDrawGrad);
          o->align(132);
          new Fl_Item(_("Flat"));
          new Fl_Item(_("Horizontal shade"));
          new Fl_Item(_("Thin down"));
          new Fl_Item(_("Up box"));
          new Fl_Item(_("Down box"));
          new Fl_Item(_("Plastic"));
          o->value(title_draw_grad);
          o->end();
        }
         {Fl_Check_Button* o = useThemeButton = new Fl_Check_Button(8, 220, 300, 20, _("&Use theme"));
          o->callback((Fl_Callback*)cb_useThemeButton);
          o->value(use_theme);
        }
         {Fl_Input* o = themePathInput = new Fl_Input(65, 247, 210, 23, _("Path:"));
          o->callback((Fl_Callback*)cb_themePathInput);
          o->deactivate();
          themePathInput->value(theme_path);
        }
         {Fl_Button* o = browse_btn = new Fl_Button(280, 247, 25, 23, _("..."));
          o->callback((Fl_Callback*)cb_browse_btn);
          o->deactivate();
        }
         {Fl_Divider* o = new Fl_Divider(8, 190, 300, 25, _("label"));
          o->color((Fl_Color)16);
        }
         {Fl_Divider* o = new Fl_Divider(8, 85, 297, 25, _("label"));
          o->color((Fl_Color)16);
        }
        o->end();
      }
       {Fl_Group* o = new Fl_Group(3, 20, 310, 305, _("&Resizing"));
        o->align(FL_ALIGN_TOP | FL_ALIGN_LEFT);
        o->hide();
         {Fl_Check_Button* o = animateButton = new Fl_Check_Button(10, 10, 300, 20, _("Animate size changes"));
          o->value(1);
          o->callback((Fl_Callback*)cb_animateButton);
          o->value(animate);
        }
         {Fl_Value_Slider* o = animateSlider = new Fl_Value_Slider(70, 35, 235, 20, _("Speed:"));
          o->type(Fl_Value_Slider::HORIZONTAL|Fl_Slider::TICK_ABOVE);
          o->box(FL_DOWN_BOX);
          o->text_size(10);
          o->minimum(5);
          o->maximum(20);
          o->step(2);
          o->value(14);
          o->slider_size(8);
          o->callback((Fl_Callback*)cb_animateSlider);
          o->align(FL_ALIGN_LEFT);
          o->value(animate_speed);
          if(animate) o->activate(); else o->deactivate();
        }
        new Fl_Divider(0, 60, 300, 25, _("label"));
         {Fl_Check_Button* o = opaqueResize = new Fl_Check_Button(10, 85, 290, 20, _("Show window content while resizing"));
          o->callback((Fl_Callback*)cb_opaqueResize);
          o->value(opaque_resize);
        }
        o->end();
      }
      o->end();
    }
     {Fl_Button* o = new Fl_Button(67, 337, 80, 25, _("&OK"));
      o->shortcut(0xff0d);
      o->callback((Fl_Callback*)cb_OK);
    }
     {Fl_Button* o = new Fl_Button(152, 337, 80, 25, _("&Apply"));
      o->callback((Fl_Callback*)cb_Apply);
    }
     {Fl_Button* o = new Fl_Button(237, 337, 80, 25, _("&Cancel"));
      o->shortcut(0xff1b);
      o->callback((Fl_Callback*)cb_Cancel);
    }
    o->end();
  }
  useThemeButton->do_callback();
  w->show(argc, argv);
  return  Fl::run();
}

void changeBoxColor(Fl_Button *box) {
  Fl_Button *colorBox = box;
  Fl_Color oldColor = colorBox->color();
  Fl_Color defColor = oldColor;
  fl_color_chooser(_("Choose color"), defColor);
  if ( defColor != oldColor ) {
  	colorBox->color(defColor);
  	colorBox->redraw();
  }
}
