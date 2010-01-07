#ifndef SETTINGSCONTAINER_H
#define SETTINGSCONTAINER_H

#include <aknsettingitemlist.h> /* CAknSettingItemList */

class CDocument;

class CSettingsContainer : public CAknSettingItemList {
public:
	virtual ~CSettingsContainer();
	static CSettingsContainer* NewL(const TRect& aRect);
	static CSettingsContainer* NewLC(const TRect& aRect);
public:
	void EditCurrentItemL();
private:
	CSettingsContainer();
	void ConstructL(const TRect& aRect);
private: /* from CAknSettingItemList */
	CAknSettingItem* CreateSettingItemL(TInt aIdentifier);
	void EditItemL(TInt aIndex, TBool aCalledFromMenu);
private: /* from CCoeControl */
	void SizeChanged();
	void HandleResourceChange(TInt aType);
private:
	CDocument& iDocument;
};

#endif /* SETTINGSCONTAINER_H */
