#ifndef _batterymonitor_h_
#define _batterymonitor_h_

#include <edeconf.h>

#include <efltk/Fl_Widget.h>
#include <efltk/Fl_Locale.h>
#include <efltk/Fl_Image.h>
#include <efltk/fl_draw.h>
#include <efltk/Fl.h>

class BatteryMonitor : public Fl_Widget {
public:
	BatteryMonitor();
	virtual ~BatteryMonitor();

	void clear();

	void update_status();
	void battery_check();

	virtual void draw();
	virtual void layout();
	virtual void preferred_size(int &w, int &h) { w=this->w(); }

private:
	int m_bat_percentage, m_bat_time;
	bool m_line_on, m_undefined;
	bool m_show_line_on;
	bool m_blink;
	Fl_Color m_colors[4];
};

#endif