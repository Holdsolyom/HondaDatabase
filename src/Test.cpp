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
	delete OBD1List;
	delete OBD2List;
	delete Transmissions;
	delete TransData;
	delete CWList;
	delete IwGetUIController();
    delete IwGetUIView();

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
	sqlite3_open("honda.db",&db);

	LoadMenu("MainMenu");
	LoadMenu("EngineList");
	LoadMenu("EngineSeries");
	LoadMenu("EngineData");
	LoadMenu("EcuCodes");
	LoadMenu("OBD1List");
	LoadMenu("OBD2List");
	LoadMenu("Transmissions");
	LoadMenu("TransData");
	LoadMenu("CWList");
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