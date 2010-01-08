#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <eikdoc.h> /* CEikDocument */

class CAppManager;
class CGulIcon;

class CDocument : public CEikDocument
{
public:
	virtual ~CDocument();
	static CDocument* NewL(CEikApplication& aApp);
	static CDocument* NewLC(CEikApplication& aApp);
public:
	static CFbsBitmap* DuplicateBitmapLC(CFbsBitmap& aBitmap);
public:
	const TDesC& AppCaptionL(TUid aUid);
	CGulIcon* AppIconL(TUid aUid, TSize aSize) const;
	TBool StartAppL(TUid aUid);
private:
	CDocument(CEikApplication& aApp);
private: /* from CEikDocument */
	CEikAppUi* CreateAppUiL();
	void ConstructL();
private:
	CAppManager* iAppManager;
};

#endif /* DOCUMENT_H */
