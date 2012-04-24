
#include "sqlite3.h"
#include "string"
#include "sstream"
#include "s3e.h"
#include "IwGx.h"
#include "IwUI.h"
#include "cstdlib"
//main class
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
	void Query(const char* field,const char* tablename,const char* column,const char* data);
	void Populate();
	void DePopulate();
	void Refresh();
	CIwList<CIwUIElement*>* pItemList;
	CIwList<CIwTexture*>* pTextures;
	int ItemNum;
	CIwString<IW_STRING_LEN_S> currentmenu;
	CIwString<IW_STRING_LEN_S> previousmenu[50];
	CIwString<IW_STRING_LEN_S> nextmenu[50];
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
CIwString<64> result;
int result_num;