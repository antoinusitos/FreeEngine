#pragma once

#include "Leaf.h"

class Particle;

class ParticleSystem : public Leaf
{
public:
	ParticleSystem();
	~ParticleSystem();

	void Awake();
	void Start();
	void Update(const float deltaTime);
	void Exit();
	void Render(sf::RenderWindow* window);

	void SetSpawnTime(const float newTime);

	void SetLifeTime(const float newTime);

	void SetPosition(const FVector3& newPos);

	void SetColor(const float r, const float b, const float g, const float a);

	void SpawnRandomSize(const float minSize, const float maxSize);

	void SpawnRandomLocation(const FVector3& minPos, const FVector3& maxPos);

	void SpawnRandomLifeTime(const float minlifeTime, const float maxLifeTime);

	void SpawnRandomColor();

	//ADD OVER LIFETIME

private:
	std::vector<Particle*> _allParticles;

	float _spawnTime = 0;
	float _currentSpawnTime = 0;

	bool _randomSize = false;
	float _randomSizeMin = 0;
	float _randomSizeMax = 0;

	bool _randomPosition = false;
	FVector3 _randomPositionMin = FVector3();
	FVector3 _randomPositionMax = FVector3();

	float _particleLifeTime = 2;
	bool _randomLifeTime = false;
	float _randomLifeTimeMin = 0;
	float _randomLifeTimeMax = 0;

	bool _useNewColor = false;
	bool _useRandomColor = false;
	float _colorR = 0;
	float _colorG = 0;
	float _colorB = 0;
	float _colorA = 0;

	Transform _transform;

	void SpawnAParticle();
};

