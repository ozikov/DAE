#pragma once
#include <vector>
#include "Vector2f.h"
#include "PowerUp.h"

class TextureManager;
class Level;
class Enemy;
class BulletManager;
class Sprite;
class SoundEffect;

class Avatar final
{
public:
	explicit Avatar(TextureManager& TextureManager);
	
	~Avatar( );
	Avatar(const Avatar& avatar) = delete;
	Avatar& operator=(const Avatar& rhs) = delete;
	Avatar(Avatar&& avatar) = delete;
	Avatar& operator=(Avatar&& rhs) = delete;

	void Update(float elapsedSec, const Level& level, std::vector<Enemy*> enemies, BulletManager& BulletManager);
	void Draw( ) const;
	void Hit( );
	void PowerupHit(PowerUp::Type powerUpType);
	void Restart( );
	Rectf GetShape( ) const;
	int GetHealth( ) const;
	int GetAmountOfLives( ) const;

private:
	enum class ActionState
	{
		idle,
		walking,
		sliding,
		jumping,
		shoot,
		shootDown,
		shootUp,
		shootUpDiagonal,
		jumpShoot,
		jumpShootDown,
		jumpShootUp,
		jumpShootUpDiagonal,
		hit,
		dead
	};

	ActionState m_ActionState;
	Rectf m_Shape;
	const float m_HorizontalSpeed;
	const float m_JumpSpeed;
	Vector2f m_Velocity;
	const Vector2f m_Acceleration;
	int m_FacingDirection;
	float m_ShootDelay;
	const float m_BulletVelocity;
	std::vector<Sprite*> m_sprites;
	int m_Health;
	const int m_StartHealth;
	float m_AccuHitSec;
	bool m_BlasterPowerUpActive;
	int m_AmountOfLives;
	const int m_StartAmountOfLives;
	float m_SecondsAfterDeath;
	SoundEffect* m_LostLifeSound;
	SoundEffect* m_ShootSound;

	void InitializeSprites(TextureManager& pTextureManager);
	void UpdateXPos(float elapsedSec);
	void UpdateYPos(float elapsedSec);
	void StayInLevelBoundaries(const Level& level);
	void ChangeShapeDimensions(int nrOfFrames);
	void HandleInput(const Level& level);
	void DrawAvatar( ) const;
	void Shoot(const Vector2f& bulletVelocity, BulletManager& BulletManager);
	Point2f DetermineBulletPos() const;
	void HandleCollision(std::vector<Enemy*> enemies);
	void AddHealth(int amountOfHealth);
};