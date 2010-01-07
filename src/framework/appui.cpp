#include "framework/appui.h"
#include <uikon.hrh>
#include "symttk/wsenv.h"
#include "example/mainwidget.h"

#include "assistant_a1986132.rsg"

CAppUi::~CAppUi()
{
	delete iWsEnv;
}

void CAppUi::ConstructL()
{
	BaseConstructL();
	iWsEnv = CSymTtkWsEnv::NewL(ApplicationRect());
}

void CAppUi::HandleCommandL(TInt aCommand)
{
	switch (aCommand) {
	case EEikCmdExit:
		Exit();
		break;
	}
}
