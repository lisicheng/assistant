#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <aknview.h> /* CAknView */

class CSymTtkWsEnv;
class MainContainer;

class CMainView : public CAknView
{
public:
	virtual ~CMainView();
	static CMainView* NewL();
	static CMainView* NewLC();
public: /* from CAknView */ // TODO: public?
	void HandleCommandL(TInt aCommand);
private:
	CMainView();
	void ConstructL();
private: /* from MEikMenuObserver */
	void DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane);
private: /* from CAknView */
	TUid Id() const;
	void DoActivateL(const TVwsViewId& aPrevViewId, TUid aCustomMessageId,
			 const TDesC8& aCustomMessage);
	void DoDeactivate();
private:
	CSymTtkWsEnv* iWsEnv;
	MainContainer* iContainer;
};

#endif /* MAINVIEW_H */
