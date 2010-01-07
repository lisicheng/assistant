#include "ui/applistview.h"

#include <aknviewappui.h>
#include <avkon.hrh>

#include "assistant.hrh"
#include "assistant_a1986132.rsg"
#include "framework/document.h"
#include "ui/applistcontainer.h"

CAppListView::~CAppListView()
{
	delete iContainer;
}

CAppListView* CAppListView::NewL()
{
	CAppListView* self = CAppListView::NewLC();
	CleanupStack::Pop(self);
	return self;
}

CAppListView* CAppListView::NewLC()
{
	CAppListView* self = new(ELeave) CAppListView();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
}

void CAppListView::HandleCommandL(TInt aCommand)
{
	switch (aCommand) {
	case EAknSoftkeyCancel:
		AppUi()->ActivateLocalViewL(TUid::Uid(EViewMain));
		break;
	case EAknSoftkeyOk:
		iContainer->AddSelectedItemsL();
		AppUi()->ActivateLocalViewL(TUid::Uid(EViewMain));
		break;
	default:
		break;
	}
}

CAppListView::CAppListView()
{
}

void CAppListView::ConstructL()
{
	BaseConstructL(R_VIEW_APPLIST);
}

TUid CAppListView::Id() const
{
	return TUid::Uid(EViewAppList);
}

void CAppListView::DoActivateL(const TVwsViewId& /*aPrevViewId*/,
			       TUid /*aCustomMessageId*/,
			       const TDesC8& /*aCustomMessage*/)
{
	// 必须在ConstructL之前调用SetMopParent而不能直接调用NewL，否则无法
	// 显示滚动条 TODO: really?
	iContainer = new(ELeave) CAppListContainer();
	iContainer->SetMopParent(this);
	iContainer->ConstructL(ClientRect());
	AppUi()->AddToStackL(*this, iContainer);
}

void CAppListView::DoDeactivate()
{
	AppUi()->RemoveFromStack(iContainer);
	delete iContainer;
	iContainer = NULL;
}
