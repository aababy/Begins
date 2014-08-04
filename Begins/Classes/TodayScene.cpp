#include "IncludeForCpp.h"
#include "TodayScene.h"


enum UITag {
    kScore = 3,
    kList,
    kMax,
};


Scene* TodayScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TodayScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    GestureLayer *gesture = GestureLayer::create(CC_CALLBACK_1(TodayScene::forwardToNewScene, layer), nullptr);
    scene->addChild(gesture);

    // return the scene
    return scene;
}

bool TodayScene::init()
{
    if (CCLayer::init())
    {
        _uiLayer = Layer::create();
        addChild(_uiLayer);
        
        _widget = dynamic_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("Scenes/TodayScene.ExportJson"));
        _uiLayer->addChild(_widget);
        
        Size screenSize = CCDirector::getInstance()->getWinSize();
        Size rootSize = _widget->getSize();
        _uiLayer->setPosition(Point((screenSize.width - rootSize.width) / 2,
                                    (screenSize.height - rootSize.height) / 2));
        
        Text* score = static_cast<Text*>(_widget->getChildByTag(kScore));
        
        xMissionPool->getMission();
        score->setText(itostr(xMissionPool->getScore()));
        
        //列表
        listView = static_cast<ListView*>(_widget->getChildByTag(kList));
        listView->setDirection(SCROLLVIEW_DIR_VERTICAL);            //如果List设置好了, 应该可以不要这句
        listView->setGravity(LISTVIEW_GRAVITY_CENTER_VERTICAL);     //如果List设置好了, 应该可以不要这句
        listView->addEventListenerListView(this, listvieweventselector(TodayScene::selectedItemEvent));
        
        Layout* default_item = dynamic_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("Scenes/ListCell.ExportJson"));
        default_item->setBackGroundColorType(LAYOUT_COLOR_SOLID);
        // set model
        listView->setItemModel(default_item);
        
        CCLOG("%lu", xMissionPool->_vMissions.size());
        // add default item
        for (int i = 0; i < xMissionPool->_vMissions.size(); ++i)
        {
            listView->pushBackDefaultItem();
        }
        updateList();
        
        return true;
    }
    return false;
}

void TodayScene::updateList()
{
    Vector<Widget*> items = listView->getItems();
    
    for (int i = 0; i < items.size(); i++) {
        Layout * bg = (Layout*)items.at(i);
        
        if (i % 2 == 0) {
            bg->setBackGroundColor(Color3B(39, 10, 34));
        } else {
            bg->setBackGroundColor(Color3B(39, 40, 10));
        }
     
        Text * labName = (Text*)bg->getChildByTag(2);
        Text * labTime = (Text*)bg->getChildByTag(3);
        
        Mission *mission = xMissionPool->_vMissions.at(i);
        labName->setText(mission->sName);
        labTime->setText(getShowTime(mission->_scTime));
    }
}

void TodayScene::selectedItemEvent(Ref *pSender, ListViewEventType type)
{
    switch (type)
    {
        case cocos2d::ui::LISTVIEW_ONSELECTEDITEM_START:
        {
            ListView* listView = static_cast<ListView*>(pSender);
            CC_UNUSED_PARAM(listView);
            CCLOG("select child start index = %ld", listView->getCurSelectedIndex());
            break;
        }
        case cocos2d::ui::LISTVIEW_ONSELECTEDITEM_END:
        {
            ListView* listView = static_cast<ListView*>(pSender);
            CC_UNUSED_PARAM(listView);
            CCLOG("select child end index = %ld", listView->getCurSelectedIndex());
            
            xSM->forward(SCENE_DETAIL, listView->getCurSelectedIndex(), nullptr);
            break;
        }
        default:
            break;
    }
}

void TodayScene::forwardToNewScene(void *)
{
    xSM->forward(SCENE_NEW);
}
