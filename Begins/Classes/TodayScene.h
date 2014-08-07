#pragma once

#include "IncludeForHeader.h"

class TodayScene : public Layer
{
public:
    static Scene* createScene();
    ~TodayScene();
    bool init();
    CREATE_FUNC(TodayScene);
    
    void forwardToNewScene(void *);
    
protected:
    void updateList(Ref *pSender);
    void selectedItemEvent(Ref *pSender, ListViewEventType type);
    // a selector callback
    //void menuCloseCallback(Ref* pSender, TouchEventType type);
    
protected:
    Layer* _uiLayer;
    Layout* _widget;
    ListView* listView;
};

/*

class TodayScene : public CCLayer, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	TodayScene(void);
	~TodayScene(void);

	CREATE_FUNC(TodayScene);

	virtual bool init();  
	static CCScene* scene();

	virtual void scrollViewDidScroll(CCScrollView* view) {};
	virtual void scrollViewDidZoom(CCScrollView* view) {};
	virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);

	virtual Size tableCellSizeForIndex(CCTableView *table, unsigned int idx);
	virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(CCTableView *table);
	void onRemind(Ref* obj);
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void registerWithTouchDispatcher();
	void layout();
	void touchDownAction(Ref *senderz, CCControlEvent controlEvent);
	void onEnter();
	void onExit();

	CCTableView* tableView;

	Size  _obWS;
	Point obTouchBegan;
	Dialog *dialog;

	MissionPool *_pool;
	Shortcut *_s;

	int iScore;

	CCLabelTTF* _pobDiscribe;
};

*/