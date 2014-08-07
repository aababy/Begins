#include "IncludeForCpp.h"
#include "DetailScene.h"


enum UITag {
    OK = 33,
    FREQUENCY = 34,
    CANCEL = 36,
    MISSION_DETAIL = 111,
    MISSION_NAME = 120,
};


Scene* DetailScene::createScene(int iTodayIdx)
{
    xMissionPool->_iTodayIdx = iTodayIdx;
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = DetailScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    GestureLayer *gesture = GestureLayer::create(nullptr, CC_CALLBACK_1(DetailScene::back, layer));
    scene->addChild(gesture);
    
    // return the scene
    return scene;
}

bool DetailScene::init()
{
    if (CCLayer::init())
    {
        _uiLayer = Layer::create();
        addChild(_uiLayer);
        
        _widget = dynamic_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("Scenes/DetailScene.ExportJson"));
        _uiLayer->addChild(_widget);
        
        auto screenSize = CCDirector::getInstance()->getWinSize();
        auto rootSize = _widget->getSize();
        _uiLayer->setPosition(Point((screenSize.width - rootSize.width) / 2,
                                    (screenSize.height - rootSize.height) / 2));
        
        btnOK = initUIButton(OK, toucheventselector(DetailScene::onButton), _widget, this);
        btnCancel = initUIButton(CANCEL, toucheventselector(DetailScene::onButton), _widget, this);
        btnFrequency = initUIButton(FREQUENCY, toucheventselector(DetailScene::onButton), _widget, this);
        txtMissionDetail = static_cast<TextField*>(_widget->getChildByTag(MISSION_DETAIL));
        txtMissionName = static_cast<Text*>(_widget->getChildByTag(MISSION_NAME));
        
        Mission *mission = xMissionPool->_vMissions.at(xMissionPool->_iTodayIdx);
        txtMissionName->setText(mission->sName);
        
        return true;
    }
    return false;
}

void DetailScene::onButton(Ref *pSender, TouchEventType type)
{
    if(type != TOUCH_EVENT_ENDED)
    {
        return;
    }
    
    Widget *widget = (Widget*)pSender;
    int iTag = widget->getTag();
    
    switch (iTag) {
        case OK:
        {
            xMissionPool->endMission(xMissionPool->_iTodayIdx, BY_MANUAL);
        }
            break;
        case CANCEL:
        {
            Mission *mission = xMissionPool->_vMissions.at(xMissionPool->_iTodayIdx);
            xMissionPool->removeMission(mission);
        }
            break;
        case FREQUENCY:
        {
            xSM->forward(SCENE_FREQUENCY);
        }
            break;
        default:
            break;
    }
    
}

void DetailScene::back(void*)
{
    xSM->back();
}
