#include "framework/application.h"
#include "common.h"
#include "framework/document.h"

TUid CApplication::AppDllUid() const
{
	return KApplicationUid;
}

CApaDocument* CApplication::CreateDocumentL()
{
	return CDocument::NewL(*this);
}
