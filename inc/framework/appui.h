#ifndef APPUI_H
#define APPUI_H

#include <eikappui.h> /* CEikAppUi */

class CSymTtkWsEnv;
class TtkWidget;

class CAppUi : public CEikAppUi
{
public:
	virtual ~CAppUi();
private:
	void ConstructL();
private: /* from CEikAppUi */
	void HandleCommandL(TInt aCommand);
private:
	CSymTtkWsEnv* iWsEnv;
};

#endif /* APPUI_H */
