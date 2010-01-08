#ifndef APPITEM_H
#define APPITEM_H

#include <e32base.h> /* CBase */

class CGulIcon;
class CIniFile;

class CAppItem : public CBase
{
public:
	virtual ~CAppItem();
	static CAppItem* NewL(TUid aUid);
	static CAppItem* NewLC(TUid aUid);
	static CAppItem* NewL(const CIniFile& aIniFile, TInt aIndex);
	static CAppItem* NewLC(const CIniFile& aIniFile, TInt aIndex);
public:
	const TDesC& Caption() const;
	CGulIcon* IconL(TSize aSize) const;
	void OpenL();
	void RemoveLD();
	void SaveIniFileL(CIniFile& aIniFile, TInt aIndex) const;
private:
	CAppItem();
	void ConstructL(TUid aUid);
	void ConstructL(const CIniFile& aIniFile, TInt aIndex);
private:
	TUid iUid;
	HBufC* iCaption;
};

#endif /* APPITEM_H */
