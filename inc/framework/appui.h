#ifndef APPUI_H
#define APPUI_H

#include <aknviewappui.h> /* CAknViewAppUi */

class CAppListView;
class CMainView;
class CSettingsView;
class CSplashView;

class CAppUi : public CAknViewAppUi
{
public:
	virtual ~CAppUi();
private:
	void ConstructL();
private: /* from CEikAppUi */
	void HandleCommandL(TInt aCommand);
private:
	CAppListView* iAppListView;
	CMainView* iMainView;
	CSettingsView* iSettingsView;
	CSplashView* iSplashView;
};

#endif /* APPUI_H */
