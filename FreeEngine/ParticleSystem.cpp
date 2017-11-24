#include "Particle.h"
#include "ParticleSystem.h"
#include "Composite.h"
#include "FMath.h"
#include "ResourcesManager.h"

ParticleSystem::ParticleSystem()
{
	_transform = Transform();
}

ParticleSystem::~ParticleSystem()
{
	for (std::vector<Particle*>::iterator it = _allParticles.begin(); it != _allParticles.end(); ++it)
	{
		delete (*it);
	}
	_allParticles.clear();
}

void ParticleSystem::Awake()
{

}

void ParticleSystem::Start()
{

}

void ParticleSystem::Update(const float deltaTime)
{
	if (_parent != nullptr)
	{
		_transform.position = _parent->transform.position;
		_transform.rotation = _parent->transform.rotation;
		_transform.scale = _parent->transform.scale;
	}

	_currentSpawnTime += deltaTime;
	if (_currentSpawnTime >= _spawnTime)
	{
		_currentSpawnTime = 0;
		SpawnAParticle();
	}

	for (std::vector<Particle*>::iterator it = _allParticles.begin(); it != _allParticles.end();)
	{
		if (_overrideMass) { (*it)->SetUseGravity(_newMass); }
		if (_useGravity) { (*it)->ApplyForce(FVector3(0, 0.01f, 0)); }
		if(_useInitialVelocity) { (*it)->ApplyForce(_initialVelocity); }

		(*it)->Update(deltaTime);
		if ((*it)->GetIsDead())
		{
			delete (*it);
			it = _allParticles.erase(it);
		}
		else
			it++;
	}
}

void ParticleSystem::Exit()
{

}

void ParticleSystem::Render(sf::RenderWindow* window)
{
	for (std::vector<Particle*>::iterator it = _allParticles.begin(); it < _allParticles.end(); it++)
	{
		(*it)->Render(window);
	}
}

void ParticleSystem::SpawnAParticle()
{
	Particle* p = new Particle();
	p->Init();
	
	p->SetAcceleration(FVector3(0, -0.05f, 0));
	
	if (_randomPosition) { p->SetPosition(FVector3(
		_transform.position.x + FMath::Random(_randomPositionMin.x, _randomPositionMax.x),
		_transform.position.y + FMath::Random(_randomPositionMin.y, _randomPositionMax.y),
		_transform.position.z + FMath::Random(_randomPositionMin.z, _randomPositionMax.z))); }
	else p->SetPosition(_transform.position);

	if (_randomSize) { p->SetScale(FVector3(FMath::Random(_randomSizeMin, _randomSizeMax))); }
	else p->SetScale(_transform.scale);

	if (_randomLifeTime) { p->SetLifeTime(FMath::Random(_randomLifeTimeMin, _randomLifeTimeMax)); }
	else p->SetLifeTime(_particleLifeTime);

	if (_useNewColor) { p->SetColor(_randomColor.x, _randomColor.y, _randomColor.z, _randomColor.w); }
	if (_useRandomColor) { p->SetColor(FMath::Random(0, 255), FMath::Random(0, 255), FMath::Random(0, 255), 255); }

	if (_useColorOverTime) { p->SetColorOverTime(_beginColor, _endColor); }

	if (_useScaleOverTime) { p->SetScaleOverTime(_beginScale, _endScale); }
	else if (_useRandomScaleOverTime) { p->SetScaleOverTime(FMath::Random(_beginScale, _beginScaleB), _endScale); }

	if (_useTexture) { p->SetTexture(_texture); }

	_allParticles.push_back(p);
}

void ParticleSystem::SetSpawnTime(const float newTime)
{
	_spawnTime = newTime;
}

void ParticleSystem::SetLifeTime(const float newTime)
{
	_particleLifeTime = newTime;
}

void ParticleSystem::SetPosition(const FVector3& newPos)
{
	_transform.position = newPos;
}

void ParticleSystem::SpawnRandomSize(const float minSize, const float maxSize)
{
	_randomSize = true;
	_randomSizeMin = minSize;
	_randomSizeMax = maxSize;
}

void ParticleSystem::SpawnRandomLocation(const FVector3& minPos, const FVector3& maxPos)
{
	_randomPosition = true;
	_randomPositionMin = minPos;
	_randomPositionMax = maxPos;
}

void ParticleSystem::SpawnRandomLifeTime(const float minlifeTime, const float maxLifeTime)
{
	_randomLifeTime = true;
	_randomLifeTimeMin = minlifeTime;
	_randomLifeTimeMax = maxLifeTime;
}

void ParticleSystem::SetColor(const float r, const float g, const float b, const float a)
{
	_useNewColor = true;
	_randomColor.x = r;
	_randomColor.y = g;
	_randomColor.z = b;
	_randomColor.w = a;
}

void ParticleSystem::SpawnRandomColor()
{
	_useRandomColor = true;
}

void ParticleSystem::SpawnColorOverTime(const FVector4& beginColor, const FVector4& endColor)
{
	_useColorOverTime = true;
	_beginColor = beginColor;
	_endColor = endColor;
}

void ParticleSystem::SpawnScaleOverTime(const float beginScale, const float endScale)
{
	_useScaleOverTime = true;
	_beginScale = beginScale;
	_endScale = endScale;
}

void ParticleSystem::SpawnRandomScaleOverTime(const float beginScaleA, const float beginScaleB, const float endScale)
{
	_useRandomScaleOverTime = true;
	_beginScale = beginScaleA;
	_beginScaleB = beginScaleB;
	_endScale = endScale;
}

void ParticleSystem::SetUseTexture(const std::string name)
{
	_useTexture = true;
	_texture = ResourcesManager::Instance().GetTexture(name);
}

void ParticleSystem::SetUseGravity(const bool newState)
{
	_useGravity = newState;
}

void ParticleSystem::SetUseGravity(const bool newState, float newMass)
{
	_useGravity = newState;
	_overrideMass = true;
	_newMass = newMass;
}

void ParticleSystem::ApplyForce(const FVector3& f)
{
	for (std::vector<Particle*>::iterator it = _allParticles.begin(); it < _allParticles.end(); it++)
	{
		(*it)->ApplyForce(f);
	}
}

void ParticleSystem::SetUseInitialVelocity(const FVector3& velocity)
{
	_useInitialVelocity = true;
	_initialVelocity = velocity;
}