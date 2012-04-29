#include "Test.h"

using namespace std;

Test::Test()
{
	MainLoop();
}
void Test::Init()
{
	InitUI();
	LoadDatabase();
	currentmenu=MainMenu;
	Populate();
}
void Test::InitUI()
{
	IwGxInit();
	IwUIInit();
	IwGxSetColClear(0x02, 0x10, 0x02, 0xff);
    IwGxPrintSetColour(255, 255, 255);

	new CIwUIController;
	new CIwUIView;

	pItemList=new CIwList<CIwUIElement*>();
	pTextures=new CIwList<CIwTexture*>();
	IwGetResManager()->LoadGroup("Test.group");
	CIwResource* pResource = IwGetResManager()->GetResNamed("iwui", IW_UI_RESTYPE_STYLESHEET);
    IwGetUIStyleManager()->SetStylesheet(IwSafeCast<CIwUIStylesheet*>(pResource));
	CIwUIElement* pMainui = (CIwUIElement*)IwGetResManager()->GetResNamed("Main", "CIwUIElement");
	CIwUIElement* pMainuiClone=pMainui->Clone();
	pList = pMainuiClone->GetChildNamed("List");
	pBack=(CIwUIButton*)pMainuiClone->GetChildNamed("Back");
	pOptions=(CIwUIButton*)pMainuiClone->GetChildNamed("Options");
	ClickHandler* handler=new ClickHandler();
	handler->AddParent(this);
	pMainuiClone->AddEventHandler(handler);
	pItemTemplate = (CIwUIElement*)IwGetResManager()->GetResNamed("Item", "CIwUIElement");

	pQuit=(CIwUIElement*)IwGetResManager()->GetResNamed("Quit", "CIwUIElement");
	pAlertDialog=(CIwUIAlertDialog*)pQuit->GetChildNamed("AlertDialog");
	pQuit->SetVisible(false);
	pQuit->AddEventHandler(handler);
	IwGetUIView()->AddElementToLayout(pMainuiClone);
	IwGetUIView()->AddElementToLayout(pQuit);

}
void Test::Update()
{
	if (ButtonEvent==true)
	{
		DePopulate();
		Populate();
		ButtonEvent=false;
	}
	IwGetUIController()->Update();
	IwGetUIView()->Update(1000/20);
}
void Test::Render()
{
	IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);
	IwGetUIView()->Render();
	IwGxFlush();
	IwGxSwapBuffers();
	s3eDeviceYield(0);

}
void Test::Terminate()
{
	DePopulate();
	pTextures->clear();
	delete pTextures;
	pItemList->clear();
    delete pItemList;
	delete MainMenu;
	delete EngineList;
	delete EngineSeries;
	delete EngineData;
	delete EcuCodes;
	delete Eculist;
	delete OBD1List;
	delete OBD2List;
	delete Transmissions;
	delete TransData;
	delete CWList;
	delete IwGetUIController();
    delete IwGetUIView();
	delete CW85;
	delete CW86;
	delete CW87;
	delete CW88;
	delete CW89;
	delete CW90;
	delete CW91;
	delete CW92;
	delete CW93;
	delete CW94;
	delete CW95;
	delete CW96;
	delete CW97;
	delete CW98;
	delete CW99;
	delete CW00;
	delete CW01;
	delete CW02;
	delete CW03;
	delete Tech;
	delete Bearing;
	delete ECUPinouts;
	delete obd0dpfipinout;
	delete obd0mpfipinout;
	delete obd1ecupinout;

	IwUITerminate();
	IwGxTerminate();
}
void Test::MainLoop()
{
	Init();
	while (!s3eDeviceCheckQuitRequest())
	{
		Update();
		Render();
	}
	Terminate();

}
void Test::LoadDatabase()
{

	sqlite3_initialize();
	MainMenu=new Menu(10);
	map["MainMenu"] =MainMenu;
	EngineList=new Menu(20);
	map["EngineList"] =EngineList;
	EngineSeries=new Menu(50);
	map["EngineSeries"] =EngineSeries;
	EngineData=new Menu(500);
	map["EngineData"] =EngineData;
	EcuCodes=new Menu(20);
	map["EcuCodes"] =EcuCodes;
	Eculist=new Menu(50);
	map["Eculist"] =Eculist;
	OBD1List=new Menu(50);
	map["OBD1List"] =OBD1List;
	OBD2List=new Menu(50);
	map["OBD2List"] =OBD2List;
	Transmissions=new Menu(10);
	map["Transmissions"] =Transmissions;
	TransData=new Menu(120);
	map["TransData"] =TransData;
	CWList=new Menu(200);
	map["CWList"] =CWList;
	CW85=new Menu(10);
	map["CW85"] =CW85;
	CW86=new Menu(10);
	map["CW86"] =CW86;
	CW87=new Menu(10);
	map["CW87"] =CW87;
	CW88=new Menu(30);
	map["CW88"] =CW88;
	CW89=new Menu(30);
	map["CW89"] =CW89;
	CW90=new Menu(30);
	map["CW90"] =CW90;
	CW91=new Menu(30);
	map["CW91"] =CW91;
	CW92=new Menu(50);
	map["CW92"] =CW92;
	CW93=new Menu(60);
	map["CW93"] =CW93;
	CW94=new Menu(50);
	map["CW94"] =CW94;
	CW95=new Menu(60);
	map["CW95"] =CW95;
	CW96=new Menu(50);
	map["CW96"] =CW96;
	CW97=new Menu(60);
	map["CW97"] =CW97;
	CW98=new Menu(60);
	map["CW98"] =CW98;
	CW99=new Menu(60);
	map["CW99"] =CW99;
	CW00=new Menu(60);
	map["CW00"] =CW00;
	CW01=new Menu(60);
	map["CW01"] =CW01;
	CW02=new Menu(30);
	map["CW02"] =CW02;
	CW03=new Menu(10);
	map["CW03"] =CW03;
	Tech=new Menu(10);
	map["Tech"] = Tech;
	Bearing=new Menu(10);
	map["Bearing"] = Bearing;
	MainBearing=new Menu(10);
	map["MainBearing"] = MainBearing;
	RodBearing=new Menu(10);
	map["RodBearing"] = RodBearing;
	ECUPinouts=new Menu(10);
	map["ECUPinouts"] = ECUPinouts;
	obd0dpfipinout=new Menu(60);
	map["obd0dpfipinout"] =obd0dpfipinout;
	obd0mpfipinout=new Menu(60);
	map["obd0mpfipinout"] =obd0mpfipinout;
	obd1ecupinout=new Menu(70);
	map["obd1ecupinout"] =obd1ecupinout;

	sqlite3_open("honda.db",&db);
	LoadMenu("MainMenu");
	LoadMenu("EngineList");
	LoadMenu("EngineSeries");
	LoadMenu("EngineData");
	LoadMenu("EcuCodes");
	LoadMenu("Eculist");
	LoadMenu("OBD1List");
	LoadMenu("OBD2List");
	LoadMenu("Transmissions");
	LoadMenu("TransData");
	LoadMenu("CWList");
	LoadMenu("CW85");
	LoadMenu("CW86");
	LoadMenu("CW87");
	LoadMenu("CW88");
	LoadMenu("CW89");
	LoadMenu("CW90");
	LoadMenu("CW91");
	LoadMenu("CW92");
	LoadMenu("CW93");
	LoadMenu("CW94");
	LoadMenu("CW95");
	LoadMenu("CW96");
	LoadMenu("CW97");
	LoadMenu("CW98");
	LoadMenu("CW99");
	LoadMenu("CW00");
	LoadMenu("CW01");
	LoadMenu("CW02");
	LoadMenu("CW03");
	LoadMenu("Tech");
	LoadMenu("Bearing");
	LoadMenu("MainBearing");
	LoadMenu("RodBearing");
	LoadMenu("ECUPinouts");
	LoadMenu("obd0dpfipinout");
	LoadMenu("obd0mpfipinout");
	LoadMenu("obd1ecupinout");
	sqlite3_close(db);
}
void Test::LoadMenu(std::string name)
{
	
	char query[50];
	sprintf(query,"SELECT COUNT(*) FROM %s",name.c_str());
	sqlite3_exec(db,query,sql_callback,NULL,NULL);
	map[name]->name=name.c_str();
	map[name]->RowNum=atoi(result[0].c_str());
	for (int x=1;x<=map[name]->RowNum;x++)
	{
	sprintf(query,"SELECT * FROM %s WHERE _id=%d",name.c_str(),x);
	sqlite3_exec(db,query,sql_callback,NULL,NULL);
	map[name]->text[x]=result[1].c_str();
	map[name]->description[x]=result[2].c_str();
	map[name]->icon[x]=result[3].c_str();
	map[name]->nextmenu[x]=result[4].c_str();
	map[name]->previousmenu[x]=result[5].c_str();
	map[name]->listindex[x]=result[7].c_str();
	if (name=="EngineData")
	{
		map[name]->listindex2[x]=result[8].c_str();
	}
	}

}
void Test::AddListItem(int ItemId,const char* iconname,const char* name,const char* desc)
{
	IwDebugTraceLinePrintf("%s",name);
    CIwUIElement* pItem = pItemTemplate->Clone();
    IwSafeCast<CIwUIButton*>(pItem->GetChildNamed("Name"))->SetCaption(name);
	IwSafeCast<CIwUILabel*>(pItem->GetChildNamed("Desc"))->SetCaption(desc);
	char filepath[30];
	sprintf(filepath,"./textures/%s.png",iconname);
	CIwTexture* tex=new CIwTexture;
	tex->LoadFromFile(filepath);
	tex->Upload();
	IwSafeCast<CIwUIImage*>(pItem->GetChildNamed("Icon"))->SetTexture(tex);
	pTextures->push_back(tex);
	char buf[20];
    sprintf(buf, "item_%d", ItemId);
	pItem->SetName(buf);
    pList->GetLayout()->AddElement(pItem);
	pItemList->push_back(pItem);
}
void Test::DeleteListItem()
{
	if (pItemList->size()>0)
	{
	CIwUIElement* pItem=pItemList->element_at(0);
	pList->GetLayout()->RemoveElement(pItem);
	pItemList->find_and_remove(pItem);
	((CIwUIScrollableView*)pItem->GetParent())->RemoveChild(pItem);
	delete pItem;

	CIwTexture* pTexture=pTextures->element_at(0);
	pTextures->find_and_remove(pTexture);
	delete pTexture;
	}

}

void Test::Populate()
{
	int row=1;
	while (row<=currentmenu->RowNum)
	{
		if (currentmenu->listindex[row]=="-1")
		{
		AddListItem(row,currentmenu->icon[row].c_str(),currentmenu->text[row].c_str(),currentmenu->description[row].c_str());
		} 
		else
		if (currentmenu->name=="EngineData")
		{
			IwDebugTraceLinePrintf("itemindex=%d",selectedItemIndex);
			IwDebugTraceLinePrintf("categoryindex=%d",CategoryIndex);
			if ((atoi(currentmenu->listindex[row].c_str())==selectedItemIndex) && (atoi(currentmenu->listindex2[row].c_str())==CategoryIndex))
			{
			AddListItem(row,currentmenu->icon[row].c_str(),currentmenu->text[row].c_str(),currentmenu->description[row].c_str());
			}
		} 
		else
		if (atoi(currentmenu->listindex[row].c_str())==selectedItemIndex)
		{
			AddListItem(row,currentmenu->icon[row].c_str(),currentmenu->text[row].c_str(),currentmenu->description[row].c_str());
		}
		row++;
	}


}

void Test::DePopulate()
{
	int x=pItemList->size();
	for (int i=0;i<=x;i++)
	{	
		DeleteListItem();
	}
	pItemList->clear();
}
bool Test::ButtonEvent=false;
void ClickHandler::AddParent(void* parent)
{
	pParent=parent;
}
bool ClickHandler::HandleEvent(CIwEvent* pEvent)
	{
		Test* test=(Test*)pParent;
		if (pEvent->GetID() == IWUI_EVENT_BUTTON)
		{
			CIwString<IW_STRING_LEN_S> selected;
			CIwUIElement* item=(CIwUIElement*)(((CIwUIButton*)pEvent->GetSender())->GetParent());
			for (int x=0;x<test->pItemList->size();x++)
			{

				CIwUIElement* elem=(CIwUIElement*)test->pItemList->element_at(x);
				if (item==elem)
				{
					CIwString<32> nextmenu=test->currentmenu->nextmenu[x+1];
					test->currentmenu=test->map[nextmenu.c_str()];
					test->selectedItemIndex=x;
					if (test->currentmenu->name=="EngineSeries")
					{
						test->CategoryIndex=x;
					}
					IwDebugTraceLinePrintf("%d",test->CategoryIndex);
				}
			}
			if ((CIwUIButton*)pEvent->GetSender()==test->pBack)
			{
					if (test->currentmenu->name=="MainMenu")
					{
						
						test->pQuit->SetVisible(true);
						IwGetUIView()->SetModal(test->pQuit);
						return true;
					}
					else
					{
						test->selectedItemIndex=test->CategoryIndex;
						CIwString<32> previousmenu=test->currentmenu->previousmenu[1];
						test->currentmenu=test->map[previousmenu.c_str()];
					}
			}

			Test::ButtonEvent=true;
		}


		if (pEvent->GetID() == IWUI_EVENT_ALERT_DIALOG_BUTTON)
		{
			CIwUIEventAlertDialogButton* pEventButton = IwSafeCast<CIwUIEventAlertDialogButton*>(pEvent);
			if (pEventButton->GetButtonIndex()==0)
			{
				s3eDeviceExit();
			}
			else
			{
				IwGetUIView()->SetModal(NULL);
				test->pQuit->SetVisible(false);
			}
		}
	return false;
}
bool ClickHandler::FilterEvent(CIwEvent* pEvent)
{
		return false;
}
int main()
{
	new Test();
	return 0;
}
int sql_callback(void* none,int argc,char** argv,char** col)
{
	for (int x=0;x<argc;x++)
	{
		result[x]=argv[x];
	}
	
	return 0;
}