
#include "sqlite3.h"
#include "string"
#include "sstream"
#include "s3e.h"
#include "IwGx.h"
#include "IwUI.h"
#include "s3eWebView.h"
#include "cstdlib"
#include "map"
#include "Menu.h"
#include "EngineDataMenu.h"
#include "TransDataMenu.h"

enum MenuState{OFF,SHOW,HIDE};
class ClickHandler : public CIwUIElementEventHandler
{
public:
	virtual	bool HandleEvent(CIwEvent* pEvent);
	virtual bool FilterEvent(CIwEvent* pEvent);
	void AddParent(void* parent);
private:
	void* pParent;
};
class Test
{

public:
	Test();
	~Test();
	void MainLoop();
	void Init();
	void Update();
	void Render();
	void Terminate();
	void AddListItem(int ItemId ,const char* iconname,const char* name,const char* desc);
	void DeleteListItem();
	void Populate();
	void DePopulate();
	void LoadDatabase();
	void InitUI();
	void LoadMenu(std::string name);
	CIwList<CIwUIElement*>* pItemList;
	CIwUIElement* pLabel;
	CIwUIElement* pItemTemplate;
	CIwUIElement* pEngineDataUI;
	CIwUIElement* pTransDataUI;
	CIwUIElement* pMainui;
	CIwUIElement* pMainuiClone;
	CIwTexture* pIcon;
	CIwTexture* pBG;
	ClickHandler* handler;
	CIwList<CIwTexture*>* pTextures;
	CIwUIElement* pList;
	int selectedItemIndex;
	int CategoryIndex;
	Menu* currentmenu;
	Menu* MainMenu;
	Menu* EngineList;
	Menu* EngineSeries;
	EngineDataMenu* EngineData;
	Menu* EcuCodes;
	Menu* Eculist;
	Menu* OBD1List;
	Menu* OBD2List;
	Menu* Transmissions;
	TransDataMenu* TransData;
	Menu* CWList;
	Menu* CW85;
	Menu* CW86;
	Menu* CW87;
	Menu* CW88;
	Menu* CW89;
	Menu* CW90;
	Menu* CW91;
	Menu* CW92;
	Menu* CW93;
	Menu* CW94;
	Menu* CW95;
	Menu* CW96;
	Menu* CW97;
	Menu* CW98;
	Menu* CW99;
	Menu* CW00;
	Menu* CW01;
	Menu* CW02;
	Menu* CW03;
	Menu* Tech;
	Menu* Bearing;
	Menu* MainBearing;
	Menu* RodBearing;
	Menu* ECUPinouts;
	Menu* obd0dpfipinout;
	Menu* obd0mpfipinout;
	Menu* obd1ecupinout;

	CIwUIElement* pQuit;
	CIwUIButton* pBack;
	CIwUIButton* pOptions;
	CIwUIAlertDialog* pAlertDialog;
	static bool ButtonEvent;
	static bool WebViewShow;
	static MenuState ShowEngineData;
	static MenuState ShowTransData;
	static int SelectedItemRowIndex;
	sqlite3* db;
	std::map<std::string, Menu*> map;
	s3eWebView* WebView;
private:
};


int main();
int sql_callback(void* none,int argc,char** argv,char** col);
CIwString<1024> result[40];