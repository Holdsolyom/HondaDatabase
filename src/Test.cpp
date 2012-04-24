#include "Test.h"

using namespace std;

Test::Test()
{
	MainLoop();
}
void Test::Init()
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

	pAlertDialog=new CIwUIAlertDialog;
	pAlertDialog->AddEventHandler(handler);
	pAlertDialog->SetLabelStyle("<font_title>");
	pAlertDialog->SetLabelCaption("Do You Want To Quit?");
	pAlertDialog->SetButtonStyle(0,"<font_title>");
	pAlertDialog->SetButtonCaption(0,"OK");
	pAlertDialog->SetButtonStyle(1,"<font_title>");
	pAlertDialog->SetButtonCaption(1,"Cancel");
	pAlertDialog->SetVisible(false);
	IwGetUIView()->AddElementToLayout(pMainuiClone);
	IwGetUIView()->AddElementToLayout(pAlertDialog);
	sqlite3_initialize();
	sqlite3_open("honda.db",&db);

	currentmenu="MainMenu";
	Refresh();
	Populate();

}
void Test::Update()
{
	if (ButtonEvent==true)
	{
		s3eDebugOutputString(currentmenu.c_str());
		DePopulate();
		Refresh();
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

	IwGetUIView()->RemoveElement(pAlertDialog);
	delete pAlertDialog;
	sqlite3_close(db);

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
void Test::Query(const char* field,const char* tablename,const char* column,const char* data)
{
	char qr[50];
	sprintf(qr,"SELECT %s FROM %s WHERE %s=%s",field,tablename,column,data);
	char* error=NULL;
	sqlite3_exec(db,qr,sql_callback,NULL,&error);
	if (error!=NULL)
	{
	s3eDebugOutputString(error);
	sqlite3_free(error);
	}
	delete error;
}
void Test::Refresh()
{
	char query[50];
	sprintf(query,"SELECT COUNT(*) FROM %s",currentmenu.c_str());
	sqlite3_exec(db,query,sql_callback,NULL,NULL);
	ItemNum=atoi(result.c_str());
	for (int x=1;x<=ItemNum;x++)
	{
	sprintf(query,"SELECT Return FROM %s where _id=%d",currentmenu.c_str(),x);
	sqlite3_exec(db,query,sql_callback,NULL,NULL);
	previousmenu[x]=result.c_str();
	sprintf(query,"SELECT Link FROM %s where _id=%d",currentmenu.c_str(),x);
	sqlite3_exec(db,query,sql_callback,NULL,NULL);
	nextmenu[x]=result.c_str();
	}
}
void Test::Populate()
{
	int row=1;
	while (row<=ItemNum)
	{
		char row_s[5];
		sprintf(row_s,"%d",row);
		Query("Text",currentmenu.c_str(),"_id",row_s);
		CIwString<64> name=result;
		Query("Desc",currentmenu.c_str(),"_id",row_s);
		CIwString<64> desc=result;
		Query("Icon",currentmenu.c_str(),"_id",row_s);
		CIwString<64> iconname=result;
		AddListItem(row,iconname.c_str(),name.c_str(),desc.c_str());
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
			for (int x=0;x<test->ItemNum;x++)
			{

				CIwUIElement* elem=(CIwUIElement*)test->pItemList->element_at(x);
				if (item==elem)
				{
					test->currentmenu=test->nextmenu[x+1];
				}
			}
			if ((CIwUIButton*)pEvent->GetSender()==test->pBack)
				{
					if (test->currentmenu=="MainMenu")
					{
						test->pAlertDialog->SetVisible(true);
						IwGetUIView()->SetModal(test->pAlertDialog);
						return true;
					}
					else
					{
					test->currentmenu=test->previousmenu[1];
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
				test->pAlertDialog->SetVisible(false);
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
	result="";
	result_num=argc;
	if (argv[0])
	result=argv[0];
	return 0;
}