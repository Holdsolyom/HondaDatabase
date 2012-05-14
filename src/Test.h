
#include "sqlite3.h"
#include "string"
#include "sstream"
#include "s3e.h"
#include "IwGx.h"
#include "IwUI.h"
#include "s3eWebView.h"
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
class EngineDataMenu : public Menu
{
public:
	EngineDataMenu(int num) : Menu(num)
	{
		EModel=new CIwString<512>[num];
		EDisp_cc=new CIwString<32>[num];
		EDisp_cu=new CIwString<32>[num];
		EBore_mm=new CIwString<32>[num];
		EBore_in=new CIwString<32>[num];
		EStroke_mm=new CIwString<32>[num];
		EStroke_in=new CIwString<32>[num];
		Ecompression=new CIwString<32>[num];
		EPistonCode=new CIwString<32>[num];
		EPistonDome=new CIwString<32>[num];
		ECombChamberVol=new CIwString<32>[num];
		EStrokeBoreRatio=new CIwString<32>[num];
		ERodStrokeRatio=new CIwString<32>[num];
		ERod_lenght_mm=new CIwString<32>[num];
		ERod_lenght_in=new CIwString<32>[num];
		EDeckHeight=new CIwString<32>[num];
		EValvetrain=new CIwString<32>[num];
		ECamgear=new CIwString<32>[num];
		EFuel=new CIwString<128>[num];
		EPower_hp=new CIwString<32>[num];
		EPower_kw=new CIwString<32>[num];
		EPowerRPM=new CIwString<32>[num];
		ETorque_lb=new CIwString<32>[num];
		ETorque_nm=new CIwString<32>[num];
		ETorqueRPM=new CIwString<32>[num];
		EVtec=new CIwString<64>[num];
		ERedline=new CIwString<32>[num];
		ERevlimit=new CIwString<32>[num];
		ETrans=new CIwString<64>[num];
		EEcucode=new CIwString<64>[num];
		EDesc=new CIwString<768>[num];
	}
		CIwString<512>* EModel;
		CIwString<32>* EDisp_cc;
		CIwString<32>* EDisp_cu;
		CIwString<32>* EBore_mm;
		CIwString<32>* EBore_in;
		CIwString<32>* EStroke_mm;
		CIwString<32>* EStroke_in;
		CIwString<32>* Ecompression;
		CIwString<32>* EPistonCode;
		CIwString<32>* EPistonDome;
		CIwString<32>* ECombChamberVol;
		CIwString<32>* EStrokeBoreRatio;
		CIwString<32>* ERodStrokeRatio;
		CIwString<32>* ERod_lenght_mm;
		CIwString<32>* ERod_lenght_in;
		CIwString<32>* EDeckHeight;
		CIwString<32>* EValvetrain;
		CIwString<32>* ECamgear;
		CIwString<128>* EFuel;
		CIwString<32>* EPower_hp;
		CIwString<32>* EPower_kw;
		CIwString<32>* EPowerRPM;
		CIwString<32>* ETorque_lb;
		CIwString<32>* ETorque_nm;
		CIwString<32>* ETorqueRPM;
		CIwString<64>* EVtec;
		CIwString<32>* ERedline;
		CIwString<32>* ERevlimit;
		CIwString<64>* ETrans;
		CIwString<64>* EEcucode;
		CIwString<768>* EDesc;
};
class TransDataMenu : public Menu
{
	public:
		TransDataMenu(int num) : Menu(num)
		{
		Type=new CIwString<32>[num];
		LSD=new CIwString<32>[num];
		_1st=new CIwString<32>[num];
		_2nd=new CIwString<32>[num];
		_3rd=new CIwString<32>[num];
		_4th=new CIwString<32>[num];
		_5th=new CIwString<32>[num];
		_6th=new CIwString<32>[num];
		R=new CIwString<32>[num];
		Final=new CIwString<32>[num];
		}
		CIwString<32>* Type;
		CIwString<32>* LSD;
		CIwString<32>* _1st;
		CIwString<32>* _2nd;
		CIwString<32>* _3rd;
		CIwString<32>* _4th;
		CIwString<32>* _5th;
		CIwString<32>* _6th;
		CIwString<32>* R;
		CIwString<32>* Final;
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
	static int ShowEngineData;
	static int ShowTransData;
	static int SelectedItemRowIndex;
	sqlite3* db;
	std::map<std::string, Menu*> map;
	s3eWebView* WebView;
private:
	



	


};


int main();
int sql_callback(void* none,int argc,char** argv,char** col);
CIwString<1024> result[40];