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
	sqlite3_close(db);
	DePopulate();
	pTextures->clear();
	delete pTextures;
	pItemList->clear();
    delete pItemList;
	delete MainMenu;
	delete EngineList;
	delete EngineSeries;
	delete EngineData;
	
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
	MainMenu=new Menu();
	EngineList=new Menu();
	EngineSeries=new Menu();
	EngineData=new Menu();
	EcuCodes=new Menu();
	OBD1List=new Menu();
	OBD2List=new Menu();
	sqlite3_open("honda.db",&db);

	char query[50];
	sprintf(query,"SELECT COUNT(*) FROM MainMenu");
	sqlite3_exec(db,query,sql_callback,NULL,NULL);
	MainMenu->name="MainMenu";
	MainMenu->RowNum=atoi(result[0].c_str());
	for (int x=1;x<=MainMenu->RowNum;x++)
	{
	sprintf(query,"SELECT * FROM MainMenu WHERE _id=%d",x);
	sqlite3_exec(db,query,sql_callback,NULL,NULL);
	MainMenu->text[x]=result[1].c_str();
	MainMenu->description[x]=result[2].c_str();
	MainMenu->icon[x]=result[3].c_str();
	MainMenu->nextmenu[x]=result[4].c_str();
	MainMenu->previousmenu[x]=result[5].c_str();
	MainMenu->listindex[x]=result[7].c_str();
	}

	sprintf(query,"SELECT COUNT(*) FROM EngineList");
	sqlite3_exec(db,query,sql_callback,NULL,NULL);
	EngineList->name="EngineList";
	EngineList->RowNum=atoi(result[0].c_str());
	for (int x=1;x<=EngineList->RowNum;x++)
	{
	sprintf(query,"SELECT * FROM EngineList WHERE _id=%d",x);
	sqlite3_exec(db,query,sql_callback,NULL,NULL);
	EngineList->text[x]=result[1].c_str();
	EngineList->description[x]=result[2].c_str();
	EngineList->icon[x]=result[3].c_str();
	EngineList->nextmenu[x]=result[4].c_str();
	EngineList->previousmenu[x]=result[5].c_str();
	EngineList->listindex[x]=result[7].c_str();
	}

	sprintf(query,"SELECT COUNT(*) FROM EngineSeries");
	sqlite3_exec(db,query,sql_callback,NULL,NULL);
	EngineSeries->name="EngineSeries";
	EngineSeries->RowNum=atoi(result[0].c_str());
	for (int x=1;x<=EngineSeries->RowNum;x++)
	{
	sprintf(query,"SELECT * FROM EngineSeries WHERE _id=%d",x);
	sqlite3_exec(db,query,sql_callback,NULL,NULL);
	EngineSeries->text[x]=result[1].c_str();
	EngineSeries->description[x]=result[2].c_str();
	EngineSeries->icon[x]=result[3].c_str();
	EngineSeries->nextmenu[x]=result[4].c_str();
	EngineSeries->previousmenu[x]=result[5].c_str();
	EngineSeries->listindex[x]=result[7].c_str();
	}

	sprintf(query,"SELECT COUNT(*) FROM EngineData");
	sqlite3_exec(db,query,sql_callback,NULL,NULL);
	EngineData->name="EngineData";
	EngineData->RowNum=atoi(result[0].c_str());
	for (int x=1;x<=EngineData->RowNum;x++)
	{
	sprintf(query,"SELECT * FROM EngineData WHERE _id=%d",x);
	sqlite3_exec(db,query,sql_callback,NULL,NULL);
	EngineData->text[x]=result[1].c_str();
	EngineData->description[x]=result[2].c_str();
	EngineData->icon[x]=result[3].c_str();
	EngineData->nextmenu[x]=result[4].c_str();
	EngineData->previousmenu[x]=result[5].c_str();
	EngineData->listindex[x]=result[7].c_str();
	EngineData->listindex2[x]=result[8].c_str();
	}

	sprintf(query,"SELECT COUNT(*) FROM EcuCodes");
	sqlite3_exec(db,query,sql_callback,NULL,NULL);
	EcuCodes->name="EcuCodes";
	EcuCodes->RowNum=atoi(result[0].c_str());
	for (int x=1;x<=EcuCodes->RowNum;x++)
	{
	sprintf(query,"SELECT * FROM EcuCodes WHERE _id=%d",x);
	sqlite3_exec(db,query,sql_callback,NULL,NULL);
	EcuCodes->text[x]=result[1].c_str();
	EcuCodes->description[x]=result[2].c_str();
	EcuCodes->icon[x]=result[3].c_str();
	EcuCodes->nextmenu[x]=result[4].c_str();
	EcuCodes->previousmenu[x]=result[5].c_str();
	EcuCodes->listindex[x]=result[7].c_str();
	}
	
	sprintf(query,"SELECT COUNT(*) FROM OBD1List");
	sqlite3_exec(db,query,sql_callback,NULL,NULL);
	OBD1List->name="OBD1List";
	OBD1List->RowNum=atoi(result[0].c_str());
	for (int x=1;x<=OBD1List->RowNum;x++)
	{
	sprintf(query,"SELECT * FROM OBD1List WHERE _id=%d",x);
	sqlite3_exec(db,query,sql_callback,NULL,NULL);
	OBD1List->text[x]=result[1].c_str();
	OBD1List->description[x]=result[2].c_str();
	OBD1List->icon[x]=result[3].c_str();
	OBD1List->nextmenu[x]=result[4].c_str();
	OBD1List->previousmenu[x]=result[5].c_str();
	OBD1List->listindex[x]=result[7].c_str();
	}
	
	sprintf(query,"SELECT COUNT(*) FROM OBD2List");
	sqlite3_exec(db,query,sql_callback,NULL,NULL);
	OBD2List->name="OBD2List";
	OBD2List->RowNum=atoi(result[0].c_str());
	for (int x=1;x<=OBD2List->RowNum;x++)
	{
	sprintf(query,"SELECT * FROM OBD2List WHERE _id=%d",x);
	sqlite3_exec(db,query,sql_callback,NULL,NULL);
	OBD2List->text[x]=result[1].c_str();
	OBD2List->description[x]=result[2].c_str();
	OBD2List->icon[x]=result[3].c_str();
	OBD2List->nextmenu[x]=result[4].c_str();
	OBD2List->previousmenu[x]=result[5].c_str();
	OBD2List->listindex[x]=result[7].c_str();
	}
	sqlite3_close(db);
	IwDebugTraceLinePrintf("%d",(IwMemBucketGetUsed(IwMemBucketGetID())));
}

void Test::AddListItem(int ItemId,const char* iconname,const char* name,const char* desc)
{
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
		} else
		if (currentmenu->name=="EngineData")
		{
			if ((atoi(currentmenu->listindex[row].c_str())==selectedItemIndex) && (atoi(currentmenu->listindex2[row].c_str())==CategoryIndex))
			{
			AddListItem(row,currentmenu->icon[row].c_str(),currentmenu->text[row].c_str(),currentmenu->description[row].c_str());
			}
		} else
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
					if (nextmenu=="MainMenu"){test->currentmenu=test->MainMenu;}
					else if (nextmenu=="EngineList"){test->currentmenu=test->EngineList;}
					else if (nextmenu=="EngineSeries"){test->currentmenu=test->EngineSeries;}
					else if (nextmenu=="EngineData"){test->currentmenu=test->EngineData;}
					else if (nextmenu=="EcuCodes"){test->currentmenu=test->EcuCodes;}
					else if (nextmenu=="OBD1List"){test->currentmenu=test->OBD1List;}
					else if (nextmenu=="OBD2List"){test->currentmenu=test->OBD2List;}
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
						if (previousmenu=="MainMenu"){test->currentmenu=test->MainMenu;}
						else if (previousmenu=="EngineList"){test->currentmenu=test->EngineList;}
						else if (previousmenu=="EngineSeries"){test->currentmenu=test->EngineSeries;}
						else if (previousmenu=="EngineData"){test->currentmenu=test->EngineData;}
						else if (previousmenu=="EcuCodes"){test->currentmenu=test->EcuCodes;}
						else if (previousmenu=="OBD1List"){test->currentmenu=test->OBD1List;}
						else if (previousmenu=="OBD2List"){test->currentmenu=test->OBD2List;}
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