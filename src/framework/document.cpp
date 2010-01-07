#include "framework/document.h"
#include "framework/appui.h"

CDocument::~CDocument()
{
}

CDocument* CDocument::NewL(CEikApplication& aApp)
{
	CDocument* self = new(ELeave) CDocument(aApp);
	return self;
}

CDocument::CDocument(CEikApplication& aApp) : CEikDocument(aApp)
{
}

CEikAppUi* CDocument::CreateAppUiL()
{
	return new(ELeave) CAppUi();
}
