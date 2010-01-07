#include "ui/settingscontainer.h"

#include <aknview.h>
#include <aknviewappui.h>

#include "assistant.hrh"
#include "assistant_a1986132.rsg"
#include "framework/document.h"

CSettingsContainer::~CSettingsContainer()
{
}

CSettingsContainer* CSettingsContainer::NewL(const TRect& aRect)
{
	CSettingsContainer* self = CSettingsContainer::NewLC(aRect);
	CleanupStack::Pop(self);
	return self;
}

CSettingsContainer* CSettingsContainer::NewLC(const TRect& aRect)
{
	CSettingsContainer* self = new(ELeave) CSettingsContainer();
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	return self;
}

void CSettingsContainer::EditCurrentItemL()
{
	EditItemL(ListBox()->CurrentItemIndex(), ETrue);
}

CSettingsContainer::CSettingsContainer()
	: iDocument(*static_cast<CDocument*>(iAvkonAppUi->Document()))
{
}

void CSettingsContainer::ConstructL(const TRect& aRect)
{
	CreateWindowL();
	SetRect(aRect);

	ConstructFromResourceL(R_SETTINGSLIST_SYSTEM);

	ActivateL();
}

CAknSettingItem* CSettingsContainer::CreateSettingItemL(TInt aIdentifier)
{
	CAknSettingItem* settingItem(NULL);
	switch (aIdentifier) {
	case ESettingVisibilityHotkey:
		settingItem = new(ELeave) CAknBinaryPopupSettingItem(
			aIdentifier, iDocument.Settings().iVisibilityHotkey);
		break;
	case ESettingRunHotkey:
		settingItem = new(ELeave) CAknBinaryPopupSettingItem(
			aIdentifier, iDocument.Settings().iRunHotkey);
		break;
	case ESettingSaveTo:
		settingItem = new(ELeave) CAknBinaryPopupSettingItem(
			aIdentifier, iDocument.Settings().iSaveTo);
		break;
	default:
		break;
	}
	return settingItem;
}

void CSettingsContainer::EditItemL(TInt aIndex, TBool aCalledFromMenu)
{
	CAknSettingItemList::EditItemL(aIndex, aCalledFromMenu);
	(*SettingItemArray())[aIndex]->StoreL();
	iDocument.ApplySettingL((*SettingItemArray())[aIndex]->Identifier());
}

void CSettingsContainer::SizeChanged()
{
	if (ListBox())
		ListBox()->SetRect(Rect());
}

// TODO: remove this if we don't support dynamic layout
void CSettingsContainer::HandleResourceChange(TInt aType)
{
	CCoeControl::HandleResourceChange(aType);
	if (aType == KEikDynamicLayoutVariantSwitch)
		SetRect(iAvkonViewAppUi->View(TUid::Uid(EViewSettings))
			->ClientRect());
}
