#ifndef APPLISTVIEW_H
#define APPLISTVIEW_H

#include <aknview.h> /* CAknView */

class CAppListContainer;

class CAppListView: public CAknView {
public:
	virtual ~CAppListView();
	static CAppListView* NewL();
	static CAppListView* NewLC();
public: /* from CAknView */ // TODO: why public
	void HandleCommandL(TInt aCommand);
private:
	CAppListView();
	void ConstructL();
private: /* from CAknView */
	TUid Id() const;
	void DoActivateL(const TVwsViewId& aPrevViewId, TUid aCustomMessageId,
			 const TDesC8& aCustomMessage);
	void DoDeactivate();
private:
	CAppListContainer* iContainer;
};

#endif /* APPLISTVIEW_H */
