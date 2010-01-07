#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <eikdoc.h> /* CEikDocument */

class CDocument : public CEikDocument
{
public:
	virtual ~CDocument();
	static CDocument* NewL(CEikApplication& aApp);
private:
	CDocument(CEikApplication& aApp);
private: /* from CEikDocument */
	CEikAppUi* CreateAppUiL();
};

#endif /* DOCUMENT_H */
