/*
 * $Id$
 *
 * Edewm, window manager
 * Part of Equinox Desktop Environment (EDE).
 * Copyright (c) 2000-2006 EDE Authors.
 *
 * This program is licenced under terms of the 
 * GNU General Public Licence version 2 or newer.
 * See COPYING for details.
 */

#include "Cursor.h"
#include "Frame.h"
#include "Tracers.h"

#include <efltk/x.h>
#include <X11/cursorfont.h>

#include <assert.h>

#ifdef _DEBUG
	#include <map>
	std::map<CursorType, const char*> cursors_map;
#endif

/* Windows like cursors (copied from FLTK).
 * These are cursors for some shapes (given in comments). For others, default X are used.
 */
#define CURSORSIZE 16
#define HOTXY 8
static struct TableEntry {
    uchar bits[CURSORSIZE*CURSORSIZE/8];
    uchar mask[CURSORSIZE*CURSORSIZE/8];
    Cursor cursor;
} table[] = {
    {{	// FL_CURSOR_NS
   0x00, 0x00, 0x80, 0x01, 0xc0, 0x03, 0xe0, 0x07, 0x80, 0x01, 0x80, 0x01,
   0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01,
   0xe0, 0x07, 0xc0, 0x03, 0x80, 0x01, 0x00, 0x00},
   {
   0x80, 0x01, 0xc0, 0x03, 0xe0, 0x07, 0xf0, 0x0f, 0xf0, 0x0f, 0xc0, 0x03,
   0xc0, 0x03, 0xc0, 0x03, 0xc0, 0x03, 0xc0, 0x03, 0xc0, 0x03, 0xf0, 0x0f,
   0xf0, 0x0f, 0xe0, 0x07, 0xc0, 0x03, 0x80, 0x01}},
  {{	// FL_CURSOR_EW
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x10,
   0x0c, 0x30, 0xfe, 0x7f, 0xfe, 0x7f, 0x0c, 0x30, 0x08, 0x10, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
   {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x1c, 0x38,
   0xfe, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x7f, 0x1c, 0x38, 0x18, 0x18,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
  {{	// FL_CURSOR_NWSE
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x38, 0x00, 0x78, 0x00,
   0xe8, 0x00, 0xc0, 0x01, 0x80, 0x03, 0x00, 0x17, 0x00, 0x1e, 0x00, 0x1c,
   0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
   {
   0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0xfc, 0x00, 0x7c, 0x00, 0xfc, 0x00,
   0xfc, 0x01, 0xec, 0x03, 0xc0, 0x37, 0x80, 0x3f, 0x00, 0x3f, 0x00, 0x3e,
   0x00, 0x3f, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00}},
  {{	// FL_CURSOR_NESW
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x1c, 0x00, 0x1e,
   0x00, 0x17, 0x80, 0x03, 0xc0, 0x01, 0xe8, 0x00, 0x78, 0x00, 0x38, 0x00,
   0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
   {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x3f, 0x00, 0x3e, 0x00, 0x3f,
   0x80, 0x3f, 0xc0, 0x37, 0xec, 0x03, 0xfc, 0x01, 0xfc, 0x00, 0x7c, 0x00,
   0xfc, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00}},
  {{0}, {0}} // FL_CURSOR_NONE & unknown
};



Cursor CreateFltkCursor(Fl_Cursor c)
{
	Cursor cursor;
	if(!c)
		return None;

	if(c >= FL_CURSOR_NS)
	{
		TableEntry* q = (c > FL_CURSOR_NESW) ? table+4 : table+(c-FL_CURSOR_NS);
		if(!(q->cursor))
		{
			XColor dummy;
			Pixmap p = XCreateBitmapFromData(fl_display, RootWindow(fl_display, fl_screen), (const char*)q->bits,
					CURSORSIZE, CURSORSIZE);
			Pixmap m = XCreateBitmapFromData(fl_display, RootWindow(fl_display, fl_screen), (const char*)q->mask,
					CURSORSIZE, CURSORSIZE);
			q->cursor = XCreatePixmapCursor(fl_display, p, m, &dummy, &dummy, HOTXY, HOTXY);

			XFreePixmap(fl_display, m);
			XFreePixmap(fl_display, p);
		}
		cursor = q->cursor;
	}
	else
		cursor = XCreateFontCursor(fl_display, (c-1)*2);

	// recolor created cursor to usefull colors
	XColor fgc;
	Fl_Color fg = fl_get_color(FL_BLACK);
	fgc.red = (fg>>16)&0xFF00;
	fgc.green = (fg>>8)&0xFF00;
	fgc.blue = fg & 0xFF00;

	XColor bgc;
	Fl_Color bg = fl_get_color(FL_WHITE);
	bgc.red = (bg>>16)&0xFF00;
	bgc.green = (bg>>8)&0xFF00;
	bgc.blue = bg & 0xFF00;
	XRecolorCursor(fl_display, cursor, &fgc, &bgc);

	return cursor;
}

CursorHandler::CursorHandler()
{
	cursors_loaded = false;
	
	/* In some cases curr_cursor_type can't be set
	 * fast enough (mostly for Frame::grab_cursor()) which
	 * will crash whole wm. This will prevent that.
	 */
	curr_cursor_type = CURSOR_DEFAULT;
}

CursorHandler::~CursorHandler()
{
	if(st != X_CURSORS)
		return;

	for(int i = 0; i < CURSOR_LIST_SIZE; i++)
		XFreeCursor(fl_display, cursors[i]);
}

void CursorHandler::load(CursorShapeType s)
{
	TRACE_FUNCTION("void CursorHandler::load(CursorShapeType s)");

	st = s;
	if(st == FLTK_CURSORS)
	{
		cursors[CURSOR_DEFAULT] = CreateFltkCursor(FL_CURSOR_ARROW);
		cursors[CURSOR_MOVE]    = CreateFltkCursor(FL_CURSOR_MOVE);
		cursors[CURSOR_WAIT]    = CreateFltkCursor(FL_CURSOR_WAIT);
		cursors[CURSOR_HELP]    = CreateFltkCursor(FL_CURSOR_HELP);
		cursors[CURSOR_N]       = CreateFltkCursor(FL_CURSOR_NS);
		cursors[CURSOR_NE]      = CreateFltkCursor(FL_CURSOR_NESW);
		cursors[CURSOR_E]       = CreateFltkCursor(FL_CURSOR_WE);
		cursors[CURSOR_SE]      = CreateFltkCursor(FL_CURSOR_NWSE);
		cursors[CURSOR_S]       = CreateFltkCursor(FL_CURSOR_NS);
		cursors[CURSOR_SW]      = CreateFltkCursor(FL_CURSOR_NESW);
		cursors[CURSOR_W]       = CreateFltkCursor(FL_CURSOR_WE);
		cursors[CURSOR_NW]      = CreateFltkCursor(FL_CURSOR_NWSE);
	}
	else
	{
		cursors[CURSOR_DEFAULT] = XCreateFontCursor(fl_display, XC_left_ptr);
		cursors[CURSOR_MOVE]    = XCreateFontCursor(fl_display, XC_fleur);
		cursors[CURSOR_WAIT]    = XCreateFontCursor(fl_display, XC_coffee_mug);
		cursors[CURSOR_HELP]    = XCreateFontCursor(fl_display, XC_question_arrow);
		cursors[CURSOR_N]       = XCreateFontCursor(fl_display, XC_top_side);
		cursors[CURSOR_NE]      = XCreateFontCursor(fl_display, XC_top_right_corner);
		cursors[CURSOR_E]       = XCreateFontCursor(fl_display, XC_right_side);
		cursors[CURSOR_SE]      = XCreateFontCursor(fl_display, XC_bottom_right_corner);
		cursors[CURSOR_S]       = XCreateFontCursor(fl_display, XC_bottom_side);
		cursors[CURSOR_SW]      = XCreateFontCursor(fl_display, XC_bottom_left_corner);
		cursors[CURSOR_W]       = XCreateFontCursor(fl_display, XC_left_side);
		cursors[CURSOR_NW]      = XCreateFontCursor(fl_display, XC_top_left_corner);
	}

#ifdef _DEBUG
	cursors_map[CURSOR_DEFAULT] = "CURSOR_DEFAULT";
	cursors_map[CURSOR_MOVE]    = "CURSOR_MOVE";
	cursors_map[CURSOR_WAIT]    = "CURSOR_WAIT";
	cursors_map[CURSOR_HELP]    = "CURSOR_HELP";
	cursors_map[CURSOR_N]       = "CURSOR_N";
	cursors_map[CURSOR_NE]      = "CURSOR_NE";
	cursors_map[CURSOR_E]       = "CURSOR_E";
	cursors_map[CURSOR_SE]      = "CURSOR_SE";
	cursors_map[CURSOR_S]       = "CURSOR_S";
	cursors_map[CURSOR_SW]      = "CURSOR_SW";
	cursors_map[CURSOR_W]       = "CURSOR_W";
	cursors_map[CURSOR_NW]      = "CURSOR_NW";
#endif

	cursors_loaded = true;
}

void CursorHandler::set_cursor(Frame* f, CursorType t)
{
	TRACE_FUNCTION("void CursorHandler::set_cursor(Frame* f, CursorType t)");
#ifdef _DEBUG
	ELOG("Cursor set to %s", cursors_map[t]);
#endif
	assert(cursors_loaded != false);
	assert(f != NULL);

	// do not set cursor to same type again
	if(t == curr_cursor_type)
		return;

	curr_cursor_type = t;

	XDefineCursor(fl_display, fl_xid(f), cursors[curr_cursor_type]);
}

// only for root window
void CursorHandler::set_root_cursor(void)
{
	TRACE_FUNCTION("void CursorHandler::set_root_cursor(void)");
	assert(cursors_loaded != false);

	root_window_cursor = cursors[CURSOR_DEFAULT];
	XDefineCursor(fl_display, RootWindow(fl_display, fl_screen), root_window_cursor);
}

Cursor CursorHandler::current_cursor(void) const
{
	TRACE_FUNCTION("Cursor CursorHandler::current_cursor(void) const");
	//assert(current_cursor > 0 && current_cursor < CURSOR_LIST_SIZE);	
	return cursors[curr_cursor_type];
}