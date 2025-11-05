#include "GameObject.h"
#include "../Utility/ResourceManager.h"
#include "DxLib.h"

// 全ドーナツの情報設定(変更不可)
DonutInfo const g_DonutInfoTable[MAX_DONUT_NUM] = {
        { DonutType::DONUT_MINI_BASIC,        10.0f, 0, "Resource/Images/donut/donut2.png" ,1},
        { DonutType::DONUT_MINI_VARIANT,      20.0f, 20, "Images/donut/donut1.png",2 },
        { DonutType::DONUT_FRENCH_CRULLER,    30.0f, 50, "Images/donut/donut1.png" ,3},
        { DonutType::DONUT_FRENCH_CRULLER_VAR,40.0f, 70, "Images/donut/donut1.png",4 },
        { DonutType::DONUT_OLD_FASHIONED,     50.0f, 100, "Images/donut/donut1.png" ,5},
        { DonutType::DONUT_OLD_FASHIONED_VAR, 60.0f, 150, "Images/donut/donut1.png",6 },
        { DonutType::DONUT_GOLDEN_CHOCOLATE,  80.0f, 200, "Images/donut/donut1.png" ,7},
        { DonutType::DONUT_COCONUT_CHOCOLATE, 100.0f, 250, "Images/donut/donut1.png" ,8},
        { DonutType::DONUT_HALF_CHOCOLATE,    120.0f, 300, "Images/donut/donut1.png" ,9},
        { DonutType::DONUT_HALF_STRAWBERRY,   140.0f, 350, "Images/donut/donut1.png" ,10},
        { DonutType::DONUT_PON_DE_RING,       160.0f, 400, "Images/donut/donut1.png",11 }
};

// コンストラクタ
GameObject::GameObject() : location(0.0f), r(0.0f), image(NULL), flip_flag(FALSE)
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

