#include "ui/mainview.h"

#include <aknviewappui.h>
#include <avkon.hrh>
#include <symttk/wsenv.h>

#include "assistant_a1986132.rsg"
#include "assistant.hrh"
#include "ui/maincontainer.h"

CMainView::~CMainView()
{
	delete iContainer;
	delete iWsEnv;
}

CMainView* CMainView::NewL()
{
	CMainView* self = CMainView::NewLC();
	CleanupStack::Pop(self);
	return self;
}

CMainView* CMainView::NewLC()
{
	CMainView* self = new(ELeave) CMainView();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
}

void CMainView::HandleCommandL(TInt aCommand)
{
	switch (aCommand) {
	case EAknSoftkeyExit:
		AppUi()->HandleCommandL(EEikCmdExit);
		break;
	default:
		break;
	}
}

CMainView::CMainView()
{
}

void CMainView::ConstructL()
{
	BaseConstructL(R_VIEW_MAIN);
	iWsEnv = CSymTtkWsEnv::NewL();
}

void CMainView::DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane)
{
	switch (aResourceId) {
	/*
	case R_MENUPANE_MANAGEMENT:
		aMenuPane->SetItemDimmed(ECmdMove, ETrue);
		break;
	case R_MENUPANE_GRID:
		break;
	*/
	default:
		break;
	}
}

TUid CMainView::Id() const
{
	return TUid::Uid(EViewMain);
}

void CMainView::DoActivateL(const TVwsViewId& /*aPrevViewId*/,
			    TUid aCustomMessageId,
			    const TDesC8& /*aCustomMessage*/)
{
	if (!iContainer) {
		const TRect& sym_rect = ClientRect();
		TtkRect rect(sym_rect.iTl.iX, sym_rect.iTl.iY,
			     sym_rect.iBr.iX, sym_rect.iBr.iY);
		iContainer = new MainContainer(*iWsEnv, rect);
		iWsEnv->SetRootWidgetL(iContainer);
	}
}

void CMainView::DoDeactivate()
{
	// TODO:
}
