
#include "sqlite3.h"
#include "string"
#include "sstream"
#include "s3e.h"
#include "IwGx.h"
#include "IwUI.h"
#include "cstdlib"

class Menu
{
public:
	CIwString<32> name;
	CIwString<32> text[500];
	CIwString<80> description[500];
	CIwString<32> icon[500];
	CIwString<32> previousmenu[500];
	CIwString<32> nextmenu[500];
	CIwString<32> listindex[500];
	CIwString<32> listindex2[500];
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
	CIwUIElement* pQuit;
	CIwUIButton* pBack;
	CIwUIButton* pOptions;
	CIwUIAlertDialog* pAlertDialog;
	static bool ButtonEvent;
	sqlite3* db;

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