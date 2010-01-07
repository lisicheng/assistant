#ifdef EKA2
#include <eikstart.h>
#endif
#include "framework/application.h"

EXPORT_C CApaApplication* NewApplication()
{
	return new CApplication();
}

#ifdef EKA2
GLDEF_C TInt E32Main()
{
	return EikStart::RunApplication(NewApplication);
}
#else
GLDEF_C TInt E32Dll(TDllReason /*aReason*/)
{
	return KErrNone;
}
#endif
