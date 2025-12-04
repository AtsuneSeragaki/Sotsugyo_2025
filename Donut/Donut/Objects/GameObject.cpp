#include "GameObject.h"
#include "../Utility/ResourceManager.h"
#include "DxLib.h"

// 全ドーナツの情報設定(変更不可)
DonutInfo const g_DonutInfoTable[MAX_DONUT_NUM] = {
        { DonutType::DONUT_MINI_BASIC,        15.0f, 0, "Resource/Images/donut2/donut1.png",1},
        { DonutType::DONUT_MINI_VARIANT,      20.0f, 20, "Resource/Images/donut2/donut2.png",2 },
        { DonutType::DONUT_FRENCH_CRULLER,    25.0f, 50, "Resource/Images/donut2/donut3.png",3},
        { DonutType::DONUT_FRENCH_CRULLER_VAR,30.0f, 70, "Resource/Images/donut2/donut4.png",4 },
        { DonutType::DONUT_OLD_FASHIONED,     35.0f, 100, "Resource/Images/donut2/donut5.png",5},
        { DonutType::DONUT_OLD_FASHIONED_VAR, 45.0f, 150, "Resource/Images/donut2/donut6.png",6 },
        { DonutType::DONUT_GOLDEN_CHOCOLATE,  55.0f, 200, "Resource/Images/donut2/donut7.png",7},
        { DonutType::DONUT_COCONUT_CHOCOLATE, 65.0f, 250, "Resource/Images/donut2/donut8.png",8},
        { DonutType::DONUT_HALF_CHOCOLATE,    75.0f, 300, "Resource/Images/donut2/donut9.png",9},
        { DonutType::DONUT_HALF_STRAWBERRY,   85.0f, 350, "Resource/Images/donut2/donut10.png",10},
        { DonutType::DONUT_PON_DE_RING,       95.0f, 400, "Resource/Images/donut2/donut11.png",11 }
};

// コンストラクタ
GameObject::GameObject() : location(0.0f), r(0.0f), image(NULL), flip_flag(FALSE),rotation(0.0)
{

}

// デストラクタ
GameObject::~GameObject()
{

}

// 初期化処理
void GameObject::Initialize()
{
	image = NULL;
}

// 更新処理
void GameObject::Update()
{

}

// 描画処理
void GameObject::Draw() const
{

}

// 終了時処理
void GameObject::Finalize()
{

}

// 位置座標取得処理
Vector2D GameObject::GetLocation() const
{
	return this->location;
}

// 半径の大きさ取得処理
float GameObject::GetRadiusSize() const
{
	return r;
}

// 位置座標設定処理
void GameObject::SetLocation(const Vector2D& location)
{
	this->location = location;
}

