#ifndef MAINCONTAINER_H
#define MAINCONTAINER_H

#include <ttk/widget.h> /* TtkWidget */

class MainContainer : public TtkWidget
{
public:
	virtual ~MainContainer();
	MainContainer(TtkWsEnvInterface& ws_env, const TtkRect& rect);
private: /* from TtkWidget */
	void handle_key_event(TtkKeyEvent& key_event);
	void handle_redraw_event(const TtkRect& redraw_rect);
};

#endif /* MAINCONTAINER_H */
