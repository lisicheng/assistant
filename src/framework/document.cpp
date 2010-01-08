#include "framework/document.h"

#include <aknsutils.h>
#include <gulicon.h>

#include "assistant.mbg"
#include "common.h"
#include "framework/appui.h"
#include "model/appmanager.h"

CDocument::~CDocument()
{
	delete iAppManager;
}

CDocument* CDocument::NewL(CEikApplication& aApp)
{
	CDocument* self = CDocument::NewLC(aApp);
	CleanupStack::Pop(self);
	return self;
}

CDocument* CDocument::NewLC(CEikApplication& aApp)
{
	CDocument* self = new(ELeave) CDocument(aApp);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
}

CFbsBitmap* CDocument::DuplicateBitmapLC(CFbsBitmap& aBitmap)
{
	CFbsBitmap* bitmap = new(ELeave) CFbsBitmap();
	CleanupStack::PushL(bitmap);

	User::LeaveIfError(bitmap->Create(aBitmap.SizeInPixels(),
			   aBitmap.DisplayMode()));

	CFbsBitmapDevice* bitmapDevice = CFbsBitmapDevice::NewL(bitmap);
	CleanupStack::PushL(bitmapDevice);

	CFbsBitGc* bitmapGc(NULL);
	User::LeaveIfError(bitmapDevice->CreateContext(bitmapGc));
	CleanupStack::PushL(bitmapGc);

	bitmapGc->BitBlt(TPoint(), &aBitmap);

	CleanupStack::PopAndDestroy(bitmapGc);
	CleanupStack::PopAndDestroy(bitmapDevice);

	return bitmap;
}

const TDesC& CDocument::AppCaptionL(TUid aUid)
{
	return iAppManager->CaptionL(aUid);
}

//TODO: dirty
CGulIcon* CDocument::AppIconL(TUid aUid, TSize aSize) const
{
	CGulIcon* icon(NULL);
	TRAPD(error, icon = iAppManager->IconL(aUid, aSize))

	if (error == KErrNone) {
		return icon;
	} else {
		delete icon;
		icon = NULL;
		TFileName fileName(KCacheDir);
		fileName.Append(KIconFileName);
		CGulIcon * icon(NULL);
#ifdef EKA2
		CFbsBitmap* bitmap(NULL);
		CFbsBitmap* mask(NULL);
		AknIconUtils::CreateIconLC(bitmap, mask, fileName,
					   EMbmAssistantDefault,
					   EMbmAssistantDefault_mask);
		AknIconUtils::SetSize(bitmap, aSize);
		AknIconUtils::SetSize(mask, aSize);
		icon = CGulIcon::NewL(bitmap, mask);
		CleanupStack::Pop();
		CleanupStack::Pop();
#else
		icon = CEikonEnv::Static()->CreateIconL(fileName,
							EMbmAssistantDefault,
							EMbmAssistantDefault_mask);
#endif
		return icon;
	}
}

TBool CDocument::StartAppL(TUid aUid)
{
	return iAppManager->StartAppL(aUid);
}

CDocument::CDocument(CEikApplication& aApp) : CEikDocument(aApp)
{
}

void CDocument::ConstructL()
{
	iAppManager = CAppManager::NewL();
}

CEikAppUi* CDocument::CreateAppUiL()
{
	return new(ELeave) CAppUi();
}
