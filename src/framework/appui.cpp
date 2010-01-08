#include "framework/appui.h"

#include "ui/applistview.h"
#include "ui/mainview.h"
#include "ui/settingsview.h"
#include "ui/splashview.h"

CAppUi::~CAppUi()
{
	delete iAppListView;
	delete iMainView;
	delete iSettingsView;
	delete iSplashView;
}

void CAppUi::ConstructL()
{
	BaseConstructL(EAknEnableSkin);

	iAppListView = CAppListView::NewL();
	AddViewL(iAppListView);

	iMainView = CMainView::NewL();
	AddViewL(iMainView);

	iSettingsView = CSettingsView::NewL();
	AddViewL(iSettingsView);

	iSplashView = CSplashView::NewL();
	AddViewL(iSplashView);
}

void CAppUi::HandleCommandL(TInt aCommand)
{
	switch (aCommand) {
	case EEikCmdExit:
		Exit();
		break;
	default:
		break;
	}
}
