#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

#include <aknview.h> /* CAknView */

class CSettingsContainer;

class CSettingsView : public CAknView {
public:
	virtual ~CSettingsView();
	static CSettingsView* NewL();
	static CSettingsView* NewLC();
public: /* from CAknView */ // TODO: why public
	void HandleCommandL(TInt aCommand);
private:
	CSettingsView();
	void ConstructL();
private: /* from CAknView */
	TUid Id() const;
	void DoActivateL(const TVwsViewId& aPrevViewId, TUid aCustomMessageId,
			 const TDesC8& aCustomMessage);
	void DoDeactivate();
private:
	CSettingsContainer* iContainer;
};

#endif /* SETTINGSVIEW_H */
