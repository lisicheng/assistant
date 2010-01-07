#include "ui/settingsview.h"

#include <aknviewappui.h>
#include <avkon.hrh>

#include "assistant.hrh"
#include "assistant_a1986132.rsg"
#include "ui/settingscontainer.h"

CSettingsView::~CSettingsView()
{
	delete iContainer;
}

CSettingsView* CSettingsView::NewL()
{
	CSettingsView* self = CSettingsView::NewLC();
	CleanupStack::Pop(self);
	return self;
}

CSettingsView* CSettingsView::NewLC()
{
	CSettingsView* self = new(ELeave) CSettingsView();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
}

void CSettingsView::HandleCommandL(TInt aCommand)
{
	switch (aCommand) {
	case EAknSoftkeyBack:
		AppUi()->ActivateLocalViewL(TUid::Uid(EViewMain));
		break;
	case ECmdChange:
		iContainer->EditCurrentItemL();
		break;
	default:
		break;
	}
}

CSettingsView::CSettingsView()
{
}

void CSettingsView::ConstructL()
{
	BaseConstructL(R_VIEW_SETTINGS);
}

TUid CSettingsView::Id() const
{
	return TUid::Uid(EViewSettings);
}

void CSettingsView::DoActivateL(const TVwsViewId& /*aPrevViewId*/,
				TUid /*aCustomMessageId*/,
				const TDesC8& /*aCustomMessage*/)
{
	iContainer = CSettingsContainer::NewL(ClientRect());
	iContainer->SetMopParent(this);
	AppUi()->AddToStackL(*this, iContainer);
}

void CSettingsView::DoDeactivate()
{
	AppUi()->RemoveFromStack(iContainer);
	delete iContainer;
	iContainer = NULL;
}
