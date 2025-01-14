#pragma once
#include <vector>
#include "Vector2f.h"

class Level;
class Enemy;
class Bullet;
class ExplosionManager;
class TextureManager;

class BulletManager
{
public:
	explicit BulletManager(TextureManager* pTextureManager);
	BulletManager(const BulletManager& bullet) = delete;
	BulletManager(BulletManager&& bullet) = delete;
	virtual ~BulletManager( );

	BulletManager& operator=(const BulletManager& rhs) = delete;
	BulletManager& operator=(BulletManager&& rhs) = delete;

	void Update(float elapsedSec, const Level& level);
	virtual void Draw( ) const;
	void AddBullet(const Point2f& bulletPos, const Vector2f& bulletVelocity, float scale, bool BlasterPowerUpActive);
	void HandleCollisionWithEnemies(std::vector<Enemy*> enemies);
	
protected:
	std::vector<Bullet*> m_pBullets;
	ExplosionManager* m_pExplosionManager;
	TextureManager* m_pTextureManager;

	virtual void DeleteBullet(int index);
	
private:
	float DetermineExplosionSize(int bulletIndex) const;
};