#include "Game.h"


Game::Game()
{
	totalMaterials = 0;
}

bool Game::Initialize(HINSTANCE hInst, HWND hwnd)
{
	

	m_Graphic = new Renderer();
	if (!m_Graphic->Initialize(hwnd))
		return false;
	if(!m_Graphic->LoadModelList())
		return false;
	if (!GameInput::Initialize(hInst, hwnd))
		return false;
	LoadContent();

	m_timeCounter = new GameTime();
	if (!m_timeCounter->Initialize())
		return false;

	return true;
}

bool Game::LoadContent()
{
	Player = new GameObject;
	Player->Initialize(XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(0.5f, 0.5f, 0.5f));
	Player->modelIndex = 0;
	Player->speed = 0.11f;
	Player2 = new GameObject;
	Player2->Initialize(XMFLOAT3(3.0f, 3.0f, 3.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(1.0f, 1.0f, 1.0f));
	Player2->modelIndex = 0;
	
/*	Player3 = new GameObject();
	Player3->Initialize(XMFLOAT3(6.0f, 3.0f, 5.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(1.0f, 1.0f, 1.0f));
	Player3->modelIndex = 0;

	Player4 = new GameObject();
	Player4->Initialize(XMFLOAT3(0.0f, -5.0f, 0.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(10.0f, 10.0f, 10.0f));
	Player4->modelIndex = 3;

	GameObject* Player5 = new GameObject();
	Player5->Initialize(XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(0.0f, 0.0f, 0.0f),
		XMFLOAT3(10.0f, 10.0f, 10.0f));
	Player5->modelIndex = 4;*/

	cam_1 = new Camera;
	cam_1->cam_mode = Camera::CAM_MODE_ARCBALL;

	m_Graphic->LoadObject(Player);
	//m_Graphic->LoadObject(Player2);
	//m_Graphic->LoadObject(Player3);
	//m_Graphic->LoadObject(Player4);
	//m_Graphic->LoadObject(Player5);
	m_Graphic->LoadCamera(cam_1);

	//cam_1->Follow(Player);

	return true;
}

void Game::Update()
{
	m_timeCounter->Update();
	GameInput::Update();
	if (KEY_DOWN(m_KeyboardState, DIK_W))
	{
		Player->position_.y += (Player->speed)*(m_timeCounter->GetTimeElapsed());
	}
	if (KEY_DOWN(m_KeyboardState, DIK_A))
	{
		Player->position_.x -= (Player->speed)*(m_timeCounter->GetTimeElapsed());
	}
	if (KEY_DOWN(m_KeyboardState, DIK_S))
	{
		Player->position_.y -= (Player->speed)*(m_timeCounter->GetTimeElapsed());
	}
	if (KEY_DOWN(m_KeyboardState, DIK_D))
	{
		Player->position_.x += (Player->speed)*(m_timeCounter->GetTimeElapsed());
	}
	if (KEY_DOWN(m_KeyboardState, DIK_R))
	{
		m_Graphic->SetNormalState();
	}
	if (KEY_DOWN(m_KeyboardState, DIK_F))
	{
		m_Graphic->SetWireFrameState();
	}
	if (KEY_DOWN(m_KeyboardState, DIK_E))
	{
		Player->rotation_.x += (Player->speed)*(m_timeCounter->GetTimeElapsed())*0.1f;
		Player->rotation_.y += (Player->speed)*(m_timeCounter->GetTimeElapsed())*0.1f;
	}
	if (BUTTON_DOWN(m_mouseState, 0))
	{
		Player->position_.x += static_cast<float>(m_mouseState.lX)*0.0176f;
		Player->position_.y -= static_cast<float>(m_mouseState.lY)*0.0176f;
	}
	if (BUTTON_DOWN(m_mouseState, 1))
	{
		XMVECTOR rot = XMLoadFloat4(cam_1->GetPosition());
		rot = XMVector4Transform(rot, XMMatrixRotationX(static_cast<float>(-m_mouseState.lY) / 300.0f));
		rot = XMVector4Transform(rot, XMMatrixRotationY(static_cast<float>(m_mouseState.lX) / 300.0f));
		cam_1->SetPosition(rot.m128_f32[0], rot.m128_f32[1], rot.m128_f32[2]);
	}
	m_Graphic->Update();
}

void Game::Render()
{
	m_Graphic->Render();
}

Game::~Game()
{
	delete cam_1;
	cam_1 = 0;
	delete m_Graphic;
	m_Graphic = 0;
	GameInput::Release();
	delete m_timeCounter;
	m_timeCounter = 0;
	Player = 0;
	Player2 = 0;

}
