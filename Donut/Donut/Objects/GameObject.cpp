#include "GameObject.h"
#include "../Utility/ResourceManager.h"
#include "DxLib.h"

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
	// メンバの情報を基に画像を描画する
	//DrawCircleAA(location.x, location.y, r, 32, 0xffff00, TRUE);

	// 当たり判定の矩形情報を描画する
	/*Vector2D upper_left = location - (box_size / 2.0f);
	Vector2D lower_right = location + (box_size / 2.0f);
	DrawBoxAA(upper_left.x, upper_left.y, lower_right.x, lower_right.y, GetColor(255, 0, 0), FALSE);*/
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

