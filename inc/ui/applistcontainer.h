#ifndef APPLISTCONTAINER_H
#define APPLISTCONTAINER_H

#include <coecntrl.h> /* CCoeControl */
#include <eiklbo.h> /* MEikListBoxObserver */

class CAknColumnListBox;
class CAknSearchField;
class CDocument;

class CAppListContainer : public CCoeControl, public MEikListBoxObserver {
public:
	virtual ~CAppListContainer();
	static CAppListContainer* NewL(const TRect& aRect);
	static CAppListContainer* NewLC(const TRect& aRect);
public:
	void AddSelectedItemsL() const;
public: // TODO: private
	CAppListContainer();
	void ConstructL(const TRect& aRect);
private: /* from CCoeControl */
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,
				    TEventCode aType);
	void Draw(const TRect& aRect) const;
	void SizeChanged();
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;
	void HandleResourceChange(TInt aType);
private: /* from MEikListBoxObserver */
	void HandleListBoxEventL(CEikListBox* aListBox,
				 TListBoxEvent aEventType);
private:
	void SetupFindBoxL();
	void SetupListL();
	void SetupListBoxStyleL();
	void SetupListBoxIconL();
	void SetupListBoxTextL();
private:
	CAknColumnListBox* iListBox;
	CAknSearchField* iFindBox;
	CDocument& iDocument;
};

#endif /* APPLISTCONTAINER_H */
