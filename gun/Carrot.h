#pragma once
#ifndef __Carrot__Carrot__
#define __Carrot__Carrot__

#include "Entity.h"

class Carrot :public Entity
{

public:

	CREATE_FUNC(Carrot);

	virtual Rect GetBoundingBox()const;//��ȡ Carrot�ı߽��

	virtual ~Carrot();

protected:

	virtual bool Init();
	/**
	 * shake or blink action
	 */
	ActionInterval* DoShakeOrBlink(int ImageFirstNumber, int ImageCount);//�ܲ�������գ��
	/**
	 * action update
	 */
	virtual void DoAction(float t);

	virtual void CarrotBeHurt(Ref* pRef);

	virtual void RegisterCarrotTouchEvent();//ע������ܲ���صĴ����¼�

	Sprite* HpSprite;//���ܲ���Ѫ����ʾ

	CC_SYNTHESIZE_PASS_BY_REF(int, myHp, MyHP);

};

#endif 