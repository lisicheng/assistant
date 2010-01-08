#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <e32base.h> /* CBase */
#include <apgcli.h> /* RApaLsSession */
class CGulIcon;

class CAppManager : public CBase {
public:
	virtual ~CAppManager();
	static CAppManager* NewL();
	static CAppManager* NewLC();
public:
	const RArray<TUid>& UidsL();
	const TDesC& CaptionL(TUid aUid);
	CGulIcon* IconL(TUid aUid, TSize aSize) const;
	TBool StartAppL(TUid aUid);
private:
	CAppManager();
	void ConstructL();
private:
	CGulIcon* IconL(TUid aUid) const;
private:
	RApaLsSession iManager;
	RArray<TUid> iUids;
	HBufC* iCaption;
	RArray<TUid> iBlackList;
};

#endif /* APPMANAGER_H */
