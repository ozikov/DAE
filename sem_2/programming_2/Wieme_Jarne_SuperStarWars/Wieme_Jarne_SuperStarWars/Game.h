#pragma once
#include "Level.h"
#include "Avatar.h"
#include "Vector2f.h"
#include "Camera.h"
#include "EnemyManager.h"
#include "PowerUpManager.h"
#include "TextureManager.h"
#include "BulletManager.h"
#include "HUD.h"
#include "SoundStream.h"
#include "SoundEffect.h"

class Texture;

class Game final
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game(Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	~Game();

	void Update( float elapsedSec );
	void Draw( ) const;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e );
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e );
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e );
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e );
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e );

private:
	// DATA MEMBERS
	const Window m_Window;

	TextureManager m_TextureManager;
	BulletManager m_BulletManager;
	Avatar m_Avatar;
	Camera m_Camera;
	Level m_Level;
	EnemyManager m_EnemyManager;
	PowerUpManager m_PowerupManager;
	HUD m_HUD;
	const SoundStream m_StartScreenMusic;
	const SoundStream m_BackgroundMusic;
	SoundEffect m_GameOverMusic;
	bool m_GameHasStarted;
	bool m_GameOver;

	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( ) const;
	void PrintInfo( ) const;
};