#include "ui/maincontainer.h"

#include <ttk/common.h>

MainContainer::~MainContainer()
{
}

MainContainer::MainContainer(TtkWsEnvInterface& ws_env, const TtkRect& rect)
	: TtkWidget(ws_env, rect, NULL)
{
}

void MainContainer::handle_key_event(TtkKeyEvent& key_event)
{
}

void MainContainer::handle_redraw_event(const TtkRect& redraw_rect)
{
}
