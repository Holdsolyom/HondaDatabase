#include "Test.h"

using namespace std;

Test::Test()
{
	WebView=NULL;
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
	pMainui = (CIwUIElement*)IwGetResManager()->GetResNamed("Main", "CIwUIElement");
	pMainuiClone=pMainui->Clone();
	pList = pMainuiClone->GetChildNamed("List");
	pBack=(CIwUIButton*)pMainuiClone->GetChildNamed("Back");
	pOptions=(CIwUIButton*)pMainuiClone->GetChildNamed("Options");
	ClickHandler* handler=new ClickHandler();
	handler->AddParent(this);
	pMainuiClone->AddEventHandler(handler);
	pItemTemplate = (CIwUIElement*)IwGetResManager()->GetResNamed("Item", "CIwUIElement");
	pEngineDataUI = (CIwUIElement*)IwGetResManager()->GetResNamed("EngineDataUI", "CIwUIElement");
	pQuit=(CIwUIElement*)IwGetResManager()->GetResNamed("Quit", "CIwUIElement");
	pAlertDialog=(CIwUIAlertDialog*)pQuit->GetChildNamed("AlertDialog");
	pQuit->SetVisible(false);
	pQuit->AddEventHandler(handler);
	IwGetUIView()->AddElement(pMainuiClone);
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
	delete pEngineDataUI;
	delete pMainui;
	delete pMainuiClone;
	delete pQuit;
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
	if (WebView)
    {
        s3eWebViewDestroy(WebView);
    }

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
	EngineData=new EngineDataMenu(500);
	map["EngineData"] =EngineData;
	EcuCodes=new Menu(20);
	map["EcuCodes"] =EcuCodes;
	Eculist=new Menu(50);
	map["Eculist"] =Eculist;
	OBD1List=new Menu(50);
	map["OBD1List"] =OBD1List;
	OBD2List=new Menu(80);
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
		((EngineDataMenu*)map[name])->listindex2[x]=result[8].c_str();
		((EngineDataMenu*)map[name])->EModel[x]=result[9].c_str();
		((EngineDataMenu*)map[name])->EDisp_cc[x]=result[10].c_str();
		((EngineDataMenu*)map[name])->EDisp_cu[x]=result[11].c_str();
		((EngineDataMenu*)map[name])->EBore_mm[x]=result[12].c_str();
		((EngineDataMenu*)map[name])->EBore_in[x]=result[13].c_str();
		((EngineDataMenu*)map[name])->EStroke_mm[x]=result[14].c_str();
		((EngineDataMenu*)map[name])->EStroke_in[x]=result[15].c_str();
		((EngineDataMenu*)map[name])->Ecompression[x]=result[16].c_str();
		((EngineDataMenu*)map[name])->EPistonCode[x]=result[17].c_str();
		((EngineDataMenu*)map[name])->EPistonDome[x]=result[18].c_str();
		((EngineDataMenu*)map[name])->ECombChamberVol[x]=result[19].c_str();
		((EngineDataMenu*)map[name])->EStrokeBoreRatio[x]=result[20].c_str();
		((EngineDataMenu*)map[name])->ERodStrokeRatio[x]=result[21].c_str();
		((EngineDataMenu*)map[name])->ERod_lenght_mm[x]=result[22].c_str();
		((EngineDataMenu*)map[name])->ERod_lenght_in[x]=result[23].c_str();
		((EngineDataMenu*)map[name])->EDeckHeight[x]=result[24].c_str();
		((EngineDataMenu*)map[name])->EValvetrain[x]=result[25].c_str();
		((EngineDataMenu*)map[name])->ECamgear[x]=result[26].c_str();
		((EngineDataMenu*)map[name])->EFuel[x]=result[27].c_str();
		((EngineDataMenu*)map[name])->EPower_hp[x]=result[28].c_str();
		((EngineDataMenu*)map[name])->EPower_kw[x]=result[29].c_str();
		((EngineDataMenu*)map[name])->EPowerRPM[x]=result[30].c_str();
		((EngineDataMenu*)map[name])->ETorque_lb[x]=result[31].c_str();
		((EngineDataMenu*)map[name])->ETorque_nm[x]=result[32].c_str();
		((EngineDataMenu*)map[name])->ETorqueRPM[x]=result[33].c_str();
		((EngineDataMenu*)map[name])->EVtec[x]=result[34].c_str();
		((EngineDataMenu*)map[name])->ERedline[x]=result[35].c_str();
		((EngineDataMenu*)map[name])->ERevlimit[x]=result[36].c_str();
		((EngineDataMenu*)map[name])->ETrans[x]=result[37].c_str();
		((EngineDataMenu*)map[name])->EEcucode[x]=result[38].c_str();
		((EngineDataMenu*)map[name])->EDesc[x]=result[39].c_str();
		}
	}

}
void Test::AddListItem(int ItemId,const char* iconname,const char* name,const char* desc)
{
	char itemid[5];
	sprintf(itemid,"%d",ItemId);
    CIwUIElement* pItem = pItemTemplate->Clone();
    IwSafeCast<CIwUILabel*>(pItem->GetChildNamed("Name"))->SetCaption(name);
	IwSafeCast<CIwUILabel*>(pItem->GetChildNamed("Desc"))->SetCaption(desc);
	IwSafeCast<CIwUILabel*>(pItem->GetChildNamed("ID"))->SetCaption(itemid);
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

	
	if (ShowEngineData==1)
	{
		pList->AddChild(pEngineDataUI);
		pList->GetLayout()->AddElement(pEngineDataUI);
			((CIwUILabel*)pEngineDataUI->GetChildNamed("name"))->SetCaption(EngineData->text[SelectedItemRowIndex].c_str());
			((CIwUILabel*)pEngineDataUI->GetChildNamed("model"))->SetCaption(EngineData->EModel[SelectedItemRowIndex].c_str());
			((CIwUILabel*)pEngineDataUI->GetChildNamed("disp_cc"))->SetCaption(EngineData->EDisp_cc[SelectedItemRowIndex].c_str());
			((CIwUILabel*)pEngineDataUI->GetChildNamed("disp_cu"))->SetCaption(EngineData->EDisp_cu[SelectedItemRowIndex].c_str());
			((CIwUILabel*)pEngineDataUI->GetChildNamed("bore_mm"))->SetCaption(EngineData->EBore_mm[SelectedItemRowIndex].c_str());
			((CIwUILabel*)pEngineDataUI->GetChildNamed("bore_in"))->SetCaption(EngineData->EBore_in[SelectedItemRowIndex].c_str());
			((CIwUILabel*)pEngineDataUI->GetChildNamed("stroke_mm"))->SetCaption(EngineData->EStroke_mm[SelectedItemRowIndex].c_str());
			((CIwUILabel*)pEngineDataUI->GetChildNamed("stroke_in"))->SetCaption(EngineData->EStroke_in[SelectedItemRowIndex].c_str());
			((CIwUILabel*)pEngineDataUI->GetChildNamed("compression"))->SetCaption(EngineData->Ecompression[SelectedItemRowIndex].c_str());
			((CIwUILabel*)pEngineDataUI->GetChildNamed("pistoncode"))->SetCaption(EngineData->EPistonCode[SelectedItemRowIndex].c_str());
			((CIwUILabel*)pEngineDataUI->GetChildNamed("pistondome"))->SetCaption(EngineData->EPistonDome[SelectedItemRowIndex].c_str());
			((CIwUILabel*)pEngineDataUI->GetChildNamed("cchamber"))->SetCaption(EngineData->ECombChamberVol[SelectedItemRowIndex].c_str());
			((CIwUILabel*)pEngineDataUI->GetChildNamed("strokeboreratio"))->SetCaption(EngineData->EStrokeBoreRatio[SelectedItemRowIndex].c_str());
			((CIwUILabel*)pEngineDataUI->GetChildNamed("rodstrokeratio"))->SetCaption(EngineData->ERodStrokeRatio[SelectedItemRowIndex].c_str());
			((CIwUILabel*)pEngineDataUI->GetChildNamed("rod_mm"))->SetCaption(EngineData->ERod_lenght_mm[SelectedItemRowIndex].c_str());
			((CIwUILabel*)pEngineDataUI->GetChildNamed("rod_in"))->SetCaption(EngineData->ERod_lenght_in[SelectedItemRowIndex].c_str());
			((CIwUILabel*)pEngineDataUI->GetChildNamed("deck_height"))->SetCaption(EngineData->EDeckHeight[SelectedItemRowIndex].c_str());
			((CIwUILabel*)pEngineDataUI->GetChildNamed("valvetrain"))->SetCaption(EngineData->EValvetrain[SelectedItemRowIndex].c_str());
			((CIwUILabel*)pEngineDataUI->GetChildNamed("camgear"))->SetCaption(EngineData->ECamgear[SelectedItemRowIndex].c_str());
			((CIwUILabel*)pEngineDataUI->GetChildNamed("fuel"))->SetCaption(EngineData->EFuel[SelectedItemRowIndex].c_str());
			((CIwUILabel*)pEngineDataUI->GetChildNamed("power_hp"))->SetCaption(EngineData->EPower_hp[SelectedItemRowIndex].c_str());
			((CIwUILabel*)pEngineDataUI->GetChildNamed("power_kw"))->SetCaption(EngineData->EPower_kw[SelectedItemRowIndex].c_str());
			((CIwUILabel*)pEngineDataUI->GetChildNamed("power_rpm"))->SetCaption(EngineData->EPowerRPM[SelectedItemRowIndex].c_str());
			((CIwUILabel*)pEngineDataUI->GetChildNamed("torque_lbft"))->SetCaption(EngineData->ETorque_lb[SelectedItemRowIndex].c_str());
			((CIwUILabel*)pEngineDataUI->GetChildNamed("torque_nm"))->SetCaption(EngineData->ETorque_nm[SelectedItemRowIndex].c_str());
			((CIwUILabel*)pEngineDataUI->GetChildNamed("torque_rpm"))->SetCaption(EngineData->ETorqueRPM[SelectedItemRowIndex].c_str());
			((CIwUILabel*)pEngineDataUI->GetChildNamed("vtec"))->SetCaption(EngineData->EVtec[SelectedItemRowIndex].c_str());
			((CIwUILabel*)pEngineDataUI->GetChildNamed("redline"))->SetCaption(EngineData->ERedline[SelectedItemRowIndex].c_str());
			((CIwUILabel*)pEngineDataUI->GetChildNamed("revlimit"))->SetCaption(EngineData->ERevlimit[SelectedItemRowIndex].c_str());
			((CIwUILabel*)pEngineDataUI->GetChildNamed("trans"))->SetCaption(EngineData->ETrans[SelectedItemRowIndex].c_str());
			((CIwUILabel*)pEngineDataUI->GetChildNamed("ecucode"))->SetCaption(EngineData->EEcucode[SelectedItemRowIndex].c_str());
			((CIwUILabel*)pEngineDataUI->GetChildNamed("note"))->SetCaption(EngineData->EDesc[SelectedItemRowIndex].c_str());
		return;
	} 
	else
	if (ShowEngineData==2)
	{	
		pList->GetLayout()->RemoveElement(pEngineDataUI);
		pList->RemoveChild(pEngineDataUI);
		ShowEngineData=0;
	}
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
bool Test::WebViewShow=false;
int Test::ShowEngineData=0;
int Test::SelectedItemRowIndex=0;
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
					CIwString<32> facebook=((CIwUILabel*)elem->GetChildNamed("Name"))->GetCaption();
					if (facebook=="Facebook")
					{
					  if(test->WebView==NULL)test->WebView = s3eWebViewCreate();
					  s3eWebViewNavigate(test->WebView, "https://www.facebook.com/linszternet");
					  s3eWebViewShow(test->WebView,0,test->pList->GetFrame().y , s3eSurfaceGetInt(S3E_SURFACE_WIDTH), test->pList->GetSize().y);
					  test->WebViewShow=true;
					  return true;
					}
				else
				if (test->currentmenu->name=="EngineData")
				{
						test->ShowEngineData=1;
						test->SelectedItemRowIndex=atoi(((CIwUILabel*)elem->GetChildNamed("ID"))->GetCaption());
				}
				else
				{
					CIwString<32> nextmenu=test->currentmenu->nextmenu[x+1];
					if (test->currentmenu->name=="EngineList")
						{
						test->CategoryIndex=x;
						}
					if(nextmenu=="None") return true;
					
					test->currentmenu=test->map[nextmenu.c_str()];
					
					test->selectedItemIndex=x;
				}

			
				}
			}
			if ((CIwUIButton*)pEvent->GetSender()==test->pBack)
			{
				if (test->WebViewShow==true)
				{
					s3eWebViewHide(test->WebView);
					test->WebViewShow=false;
					return true;
				}
				else
					if (test->ShowEngineData==1)
					{
						
						test->ShowEngineData=2;
					}
					else
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