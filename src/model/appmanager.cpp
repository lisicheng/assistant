#include "model/appmanager.h"

#include <aknsutils.h>
#include <apacmdln.h>
#include <apgcli.h>
#include <gulicon.h>

#include "common.h"
#include "framework/document.h"

CAppManager::~CAppManager()
{
	iManager.Close();
	iUids.Close();
	delete iCaption;
	iBlackList.Close();
}

CAppManager* CAppManager::NewL()
{
	CAppManager* self = CAppManager::NewLC();
	CleanupStack::Pop(self);
	return self;
}

CAppManager* CAppManager::NewLC()
{
	CAppManager* self = new(ELeave) CAppManager();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
}

const RArray<TUid>& CAppManager::UidsL()
{
	return iUids;
}

const TDesC& CAppManager::CaptionL(TUid aUid)
{
	TApaAppInfo appInfo;
	User::LeaveIfError(iManager.GetAppInfo(appInfo, aUid));
	delete iCaption;
	iCaption = NULL;
	iCaption = appInfo.iCaption.AllocL();
	return *iCaption;
}

//TODO: dirty
CGulIcon* CAppManager::IconL(TUid aUid, TSize aSize) const
{
#ifndef EKA2
	TVersion version = CDocument::PlatformVersionL();
	if (!(version.iMajor == 2 && version.iMinor == 8))
		return IconL(aUid);
#endif

	MAknsSkinInstance* skin = AknsUtils::SkinInstance();
	CFbsBitmap* bitmap(NULL);
	CFbsBitmap* mask(NULL);
	CGulIcon* icon(NULL);
	TRAPD(error,
		AknsUtils::CreateAppIconLC(skin, aUid, EAknsAppIconTypeList, bitmap, mask);
		icon = CGulIcon::NewL(bitmap, mask);
		CleanupStack::Pop();
		CleanupStack::Pop();
	)
	if (error == KErrNone) {
#ifdef EKA2
		AknIconUtils::SetSize(icon->Bitmap(), aSize);
		AknIconUtils::SetSize(icon->Mask(), aSize);
#endif
		return icon;
	} else {
		return IconL(aUid);
	}
}

TBool CAppManager::StartAppL(TUid aUid)
{
	TApaAppInfo appInfo;
	TInt error = iManager.GetAppInfo(appInfo, aUid);
	if (error == KErrNotFound)
		return EFalse;
	User::LeaveIfError(error);
	CApaCommandLine* cmdLine = CApaCommandLine::NewLC();
#ifdef EKA2
	cmdLine->SetExecutableNameL(appInfo.iFullName);
#else
	cmdLine->SetLibraryNameL(appInfo.iFullName);
#endif
	cmdLine->SetCommandL(EApaCommandOpen);
	User::LeaveIfError(iManager.StartApp(*cmdLine));
	CleanupStack::PopAndDestroy(cmdLine);
	return ETrue;
}

CAppManager::CAppManager()
{
}

void CAppManager::ConstructL()
{
	User::LeaveIfError(iManager.Connect());
	TUid blacklist[] = {1,2,3};
	const TUid KSystemRootFolderAppUid = { 0x101f4cd2 };
	const TUid KSystemHelpAppUid = { 0x10005234 };
	const TUid KTBConfigProxyAppUid = { 0x2001e0d4 };
	iBlackList.AppendL(KSystemRootFolderAppUid);
	iBlackList.AppendL(KSystemHelpAppUid);
	iBlackList.AppendL(KTBConfigProxyAppUid);
	// TODO: keep iBlacList in order
	User::LeaveIfError(iManager.GetAllApps());
	TApaAppInfo appInfo;
	TApaAppCapabilityBuf capability;
	TInt error = iManager.GetNextApp(appInfo);
	while (error == KErrNone) {
		if (iBlackList.FindInUnsignedKeyOrder(appInfo.iUid) ==
		    KErrNotFound) {
			User::LeaveIfError(iManager.GetAppCapability(capability,
					   appInfo.iUid));
			if (!capability().iAppIsHidden)
				iUids.AppendL(appInfo.iUid);
		}
		error = iManager.GetNextApp(appInfo);
	}
	if (error != RApaLsSession::ENoMoreAppsInList)
		User::Leave(error);
}

CGulIcon* CAppManager::IconL(TUid aUid) const
{
	CArrayFixFlat<TSize>* array =
		new(ELeave) CArrayFixFlat<TSize>(KDefaultGranularity);
	CleanupStack::PushL(array);
	User::LeaveIfError(iManager.GetAppIconSizes(aUid, *array));

	CApaMaskedBitmap* maskedBitmap = CApaMaskedBitmap::NewLC();
	User::LeaveIfError(iManager.GetAppIcon(aUid, (*array)[0], *maskedBitmap));
	CFbsBitmap* mask = CDocument::DuplicateBitmapLC(
			*maskedBitmap->Mask());
	CGulIcon* icon = CGulIcon::NewL(maskedBitmap, mask);

	CleanupStack::Pop(mask);
	CleanupStack::Pop(maskedBitmap);
	CleanupStack::PopAndDestroy(array);

	return icon;
}
