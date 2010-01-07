#include "ui/applistcontainer.h"

#include <akniconarray.h>
#include <aknlists.h>
#include <aknsfld.h>
#include <aknview.h>
#include <aknviewappui.h>
#include <eikclbd.h>

#include "assistant.hrh"
#include "assistant.mbg"
#include "common.h"
#include "framework/document.h"

CAppListContainer::~CAppListContainer()
{
	delete iListBox;
	delete iFindBox;
}

CAppListContainer* CAppListContainer::NewL(const TRect& aRect)
{
	CAppListContainer* self = CAppListContainer::NewLC(aRect);
	CleanupStack::Pop(self);
	return self;
}

CAppListContainer* CAppListContainer::NewLC(const TRect& aRect)
{
	CAppListContainer* self = new (ELeave) CAppListContainer();
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	return self;
}

void CAppListContainer::AddSelectedItemsL() const
{
	const RArray<TUid>& appUids = iDocument.AppUidsL();
	CAppItem* item(NULL);
	TInt index(0);
	for (TInt i = 0; i < iListBox->SelectionIndexes()->Count(); i++) {
		index = (*iListBox->SelectionIndexes())[i];
		index = static_cast<CAknFilteredTextListBoxModel*>
			(iListBox->Model())->Filter()->FilteredItemIndex(index);
		// TODO: iDocument.AddAppItem(index);
		item = CAppItem::NewLC(appUids[index]);
		iDocument.AppItems().AppendL(item);
		CleanupStack::Pop(item);
	}
}

CAppListContainer::CAppListContainer()
	: iDocument(*static_cast<CDocument*>(iAvkonAppUi->Document()))
{
}

void CAppListContainer::ConstructL(const TRect& aRect)
{
	CreateWindowL();

	SetupListL();
	SetupFindBoxL();

	SetRect(aRect);
	ActivateL();
}

TKeyResponse CAppListContainer::OfferKeyEventL(const TKeyEvent& aKeyEvent,
					       TEventCode aType)
{
	TBool isFindPopup(EFalse); // TODO: what is this?
	TBool needRefresh(EFalse);
	if (AknFind::HandleFindOfferKeyEventL(aKeyEvent, aType, this, iListBox,
					      iFindBox, isFindPopup,
					      needRefresh) == EKeyWasConsumed) {
		if (needRefresh) {
			SizeChanged();
			DrawDeferred();
		}
		return EKeyWasConsumed;
	}
	return iListBox->OfferKeyEventL(aKeyEvent, aType);
}

void CAppListContainer::Draw(const TRect& aRect) const
{
	SystemGc().Clear(aRect);
}

void CAppListContainer::SizeChanged()
{
	// TODO: use Rect() instead of MinimumSize()?
	iListBox->SetRect(iListBox->MinimumSize());
	// TODO: dynamic_cast ?
	CAknColumnListBox* aknListBox = static_cast<CAknColumnListBox*>
					(iListBox);
	AknFind::HandleFixedFindSizeChanged(this, aknListBox, iFindBox);
}

TInt CAppListContainer::CountComponentControls() const
{
	return 2;
}

CCoeControl* CAppListContainer::ComponentControl(TInt aIndex) const
{
	switch (aIndex) {
	case 0:
		return iListBox;
	case 1:
		return iFindBox;
	default:
		return NULL;
	}
}

// TODO: remove this if we don't support dynamic layout
void CAppListContainer::HandleResourceChange(TInt aType)
{
	CCoeControl::HandleResourceChange(aType);
	if (aType == KEikDynamicLayoutVariantSwitch)
		SetRect(iAvkonViewAppUi->View(TUid::Uid(EViewAppList))
			->ClientRect());
}

void CAppListContainer::HandleListBoxEventL(CEikListBox* /*aListBox*/,
					    TListBoxEvent aEventType)
{
	if (aEventType == EEventEnterKeyPressed) {
		iListBox->View()->ToggleItemL(iListBox->CurrentItemIndex());
	}
}

void CAppListContainer::SetupFindBoxL()
{
	const TInt KFindBoxTextLength = 10;
	CGulIcon* icon(NULL);
	iFindBox = CAknSearchField::NewL(*this, CAknSearchField::ESearch,
					 icon, KFindBoxTextLength);
	static_cast<CAknFilteredTextListBoxModel*>(iListBox->Model())
		->CreateFilterL(iListBox, iFindBox);
}

void CAppListContainer::SetupListL()
{
	iListBox = new(ELeave) CAknSingleGraphicStyleListBox();
	iListBox->SetContainerWindowL(*this);
	iListBox->ConstructL(this, EAknListBoxMultiselectionList);
	iListBox->SetListBoxObserver(this);

	SetupListBoxStyleL();
	SetupListBoxIconL();
	SetupListBoxTextL();

	iListBox->SetCurrentItemIndex(0);
	iListBox->HandleItemAdditionL();
	iListBox->DrawDeferred();
}

void CAppListContainer::SetupListBoxStyleL()
{
	iListBox->CreateScrollBarFrameL();
	iListBox->ScrollBarFrame()->SetScrollBarVisibilityL(
		CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto);
}

void CAppListContainer::SetupListBoxIconL()
{
	TFileName iconFileName(KCacheDir);
	iconFileName.Append(KIconFileName);
	// TODO: put icon file in E:
	
	CArrayPtr<CGulIcon>* icons =
		iListBox->ItemDrawer()->ColumnData()->IconArray();
	delete icons;
	icons = NULL;
	icons = new(ELeave) CAknIconArray(KDefaultGranularity);
	CleanupStack::PushL(icons);

	icons->AppendL(iEikonEnv->CreateIconL(iconFileName,
					      EMbmAssistantSelectmark,
					      EMbmAssistantSelectmark_mask));
	icons->AppendL(iEikonEnv->CreateIconL(iconFileName,
					      EMbmAssistantNullmark,
					      EMbmAssistantNullmark_mask));

	iListBox->ItemDrawer()->ColumnData()->SetIconArray(icons);
	CleanupStack::Pop(icons);
}

void CAppListContainer::SetupListBoxTextL()
{
	CDesCArray* titles =
		static_cast<CDesCArray*>(iListBox->Model()->ItemTextArray());
	titles->Reset();

	const TInt KMaxTitleLength = 1024;
	TBuf<KMaxTitleLength> title;
	const RArray<TUid>& appUids = iDocument.AppUidsL();
	for (TInt i = 0; i < appUids.Count(); i++) {
		title.Num(1); /* EMbmAssistantNullmark */
		title.Append('\t');
		title.Append(iDocument.AppCaptionL(appUids[i]));
		titles->AppendL(title);
	}
}
