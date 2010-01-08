#include "model/appitem.h"

#include <aknappui.h>
#include <troodon/inifile.h>

#include "common.h"
#include "framework/document.h"

/*
#include "shortcut.hrh"

#include "framework/shortcutdocument.h"
*/

_LIT(KSectionItem, "item");
_LIT(KKeyUid, "uid");
_LIT(KKeyCaption, "caption");

const TInt KIniItemLength = 7;

CAppItem::~CAppItem()
{
	delete iCaption;
}

CAppItem* CAppItem::NewL(TUid aUid)
{
	CAppItem* self = CAppItem::NewLC(aUid);
	CleanupStack::Pop(self);
	return self;
}

CAppItem* CAppItem::NewLC(TUid aUid)
{
	CAppItem* self = new(ELeave) CAppItem();
	CleanupStack::PushL(self);
	self->ConstructL(aUid);
	return self;
}

CAppItem* CAppItem::NewL(const CIniFile& aIniFile, TInt aIndex)
{
	CAppItem* self = CAppItem::NewLC(aIniFile, aIndex);
	CleanupStack::Pop(self);
	return self;
}

CAppItem* CAppItem::NewLC(const CIniFile& aIniFile, TInt aIndex)
{
	CAppItem* self = new(ELeave) CAppItem();
	CleanupStack::PushL(self);
	self->ConstructL(aIniFile, aIndex);
	return self;
}

const TDesC& CAppItem::Caption() const
{
	return *iCaption;
}

CGulIcon* CAppItem::IconL(TSize aSize) const
{
	return static_cast<CDocument*>(iAvkonAppUi->Document())->AppIconL(
		iUid, aSize);
}

void CAppItem::OpenL()
{
	if (!static_cast<CDocument*>(iAvkonAppUi->Document())->StartAppL(iUid))
		; // TODO iAvkonAppUi->HandleCommandL(ECmdRemoveBadItem);
}

void CAppItem::RemoveLD()
{
	// TODO: iParent->Items().Remove(iParent->Items().FindL(this));
	delete this;
}

void CAppItem::SaveIniFileL(CIniFile& aIniFile, TInt aIndex) const
{
	TBuf<KIniItemLength> section(KSectionItem);
	section.AppendNum(aIndex);
	TBuf<KUidLength> uid;
	uid.AppendNumFixedWidth(iUid.iUid, EHex, KUidLength);
	aIniFile.SetValueL(section, KKeyUid, uid);
	aIniFile.SetValueL(section, KKeyCaption, *iCaption);
}

void CAppItem::ConstructL(TUid aUid)
{
	iUid = aUid;
	CDocument& document = *static_cast<CDocument*>(iAvkonAppUi->Document());
	delete iCaption;
	iCaption = NULL;
	iCaption = document.AppCaptionL(aUid).AllocL(); //TODO: bad
}

void CAppItem::ConstructL(const CIniFile& aIniFile, TInt aIndex)
{
	TBuf<KIniItemLength> section(KSectionItem);
	section.AppendNum(aIndex);
	TLex lex(aIniFile.ValueL(section, KKeyUid));
	TUint uidValue;
	User::LeaveIfError(lex.Val(uidValue, EHex));
	iUid = TUid::Uid(uidValue);
	iCaption = aIniFile.ValueL(section, KKeyCaption).AllocL();
}
