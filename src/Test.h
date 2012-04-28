
#include "sqlite3.h"
#include "string"
#include "sstream"
#include "s3e.h"
#include "IwGx.h"
#include "IwUI.h"
#include "cstdlib"
#include "map"

class Menu
{
public:
	Menu(int num)
	{
	text=new CIwString<64>[num];
	description= new CIwString<80>[num];
	icon=new CIwString<32>[num];
	previousmenu=new CIwString<32>[num];
	nextmenu=new  CIwString<32>[num];
	listindex= new  CIwString<32>[num];
	listindex2=new  CIwString<32>[num];
	RowNum=0;
	}
	CIwString<32> name;
	CIwString<64>* text;
	CIwString<80>* description;
	CIwString<32>* icon;
	CIwString<32>* previousmenu;
	CIwString<32>* nextmenu;
	CIwString<32>* listindex;
	CIwString<32>* listindex2;
	int RowNum;
};

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
	CIwList<CIwTexture*>* pTextures;
	int selectedItemIndex;
	int CategoryIndex;
	Menu* currentmenu;
	Menu* MainMenu;
	Menu* EngineList;
	Menu* EngineSeries;
	Menu* EngineData;
	Menu* EcuCodes;
	Menu* OBD1List;
	Menu* OBD2List;
	Menu* Transmissions;
	Menu* TransData;
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

	CIwUIElement* pQuit;
	CIwUIButton* pBack;
	CIwUIButton* pOptions;
	CIwUIAlertDialog* pAlertDialog;
	static bool ButtonEvent;
	sqlite3* db;
	std::map<std::string, Menu*> map;
private:
	
	CIwUIElement* pList;
	CIwUIElement* pLabel;
	CIwUIElement* pItemTemplate;
	CIwTexture* pIcon;
	CIwTexture* pBG;
	ClickHandler* handler;

	


};


int main();
int sql_callback(void* none,int argc,char** argv,char** col);
CIwString<1000> result[40];