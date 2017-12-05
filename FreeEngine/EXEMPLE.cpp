#pragma once

#pragma region PARTICLE SYSTEM
/*

**** PARTICLE SYSTEM ****

p = new ParticleSystem();
p->SetSpawnTime(0.02f);
p->SetPosition(FVector3(100, 400, 0));
p->SpawnRandomSize(0.1f, 0.1f);
//p->SpawnRandomScaleOverTime(0.75f, 1.5f, 0);
p->SpawnRandomLocation(FVector3(-50, 0, 0), FVector3(50, 0, 0));
p->SpawnRandomLifeTime(1.5f, 2.5f);
//p->SetColor(FMath::Random(0, 255), FMath::Random(0, 255), FMath::Random(0, 255), 255);
//p->SpawnRandomColor();
p->SpawnColorOverTime(FVector4(40, 1, 1, 255), FVector4(226, 209, 5, 0));
p->SetUseTexture("Sprites/glow.png");
//p->SetUseGravity(true);
p->SetUseInitialVelocity(FVector3(0.05f, 0, 0));

*/
#pragma endregion

#pragma region CURVE
/*

**** CURVE ****

FCurve* curve = new FCurve();
curve->InsertTiming(0.25f, 100);
curve->InsertTiming(0.5f, 0);
curve->InsertTiming(0.75f, 100);
float timing = 0;

while(true)
{
	curve->GetValue(timing); <-- value to get
	timing += deltaTime;
}

*/
#pragma endregion

#pragma region SPRITE RENDERER
/*

**** SPRITE RENDERER ****

sr3 = new SpriteRenderer();
sr3->Init("Sprites/Background_01/PARALLAX/background.png");
background->AddLeaf(sr3);

sr4 = new SpriteRenderer();
sr4->Init("Sprites/Background_01/PARALLAX/clouds.png");
background->AddLeaf(sr4);
...

*/
#pragma endregion

#pragma region SPRITE ANIMATOR TEXTURES
/*

**** SPRITE ANIMATOR TEXTURES ****

sr3 = new SpriteAnimator();
sr3->AddTexture("Sprites/Background_01/PARALLAX/background.png");
sr3->AddTexture("Sprites/Background_01/PARALLAX/background2.png");
...
background->AddLeaf(sr3);

*/
#pragma endregion

#pragma region SPRITE ANIMATOR ATLAS
/*

**** SPRITE ANIMATOR ATLAS ****

sr3 = new SpriteAnimator();
sr3->AddAtlas("Sprites/Background_01/PARALLAX/background.png", 5, 500, 50, 100, 50, 0, 0);
background->AddLeaf(sr3);

*/
#pragma endregion

#pragma region SHADER
/*

**** SHADER ****

sf::CircleShape circle;
circle.setRadius(100.f);
circle.setOrigin(circle.getRadius(), circle.getRadius());
circle.setPosition(sf::Vector2f(_window->GetWindow()->getSize()) / 2.f);
circle.setFillColor(sf::Color::Transparent);
sf::Shader shader;
_resourcesManager->GetVertexFragmentShader(shader, "VertexShader.vert", "RadialGradient.frag");
shader.setUniform("color", sf::Glsl::Vec4(0, 0, 255, 1.0f));
shader.setUniform("center", circle.getPosition());
shader.setUniform("radius", circle.getRadius());
shader.setUniform("expand", 0.7f);
shader.setUniform("windowHeight", static_cast<float>(_window->GetWindow()->getSize().y));

_window->GetWindow()->draw(circle, &shader);

*/
#pragma endregion

#pragma region SCREEN SHAKE
/*

**** SCREEN SHAKE ****

_screenShakeManager->ShakeForSeconds(2.0f, 0.5f, 0.03f);

*/
#pragma endregion

#pragma region PERLIN NOISE
/*

**** PERLIN NOISE ****

for (int i = 0; i < 10; i++)
{
std::cout << "random:" << FMath::GetRandomPixelColor("perlin-noise.png").x << '\n';
}

std::vector<FVector4> l = FMath::GetPixels("perlin-noise.png");

for (int i = 0; i < l.size(); i++)
{
	std::cout << "pixel:" << l[i].x << '\n';
}

*/
#pragma endregion

#pragma region GET COMPONENT FROM OBJECT
/*

**** GET COMPONENT FROM OBJECT ****

SpriteRenderer* sr = nullptr;

for (std::vector<Leaf*>::iterator it = go->components.begin(); it != go->components.end(); ++it)
{
	sr = static_cast<SpriteRenderer*>(*it);
	if (sr != NULL){ break; }
}

if (sr != NULL)
{
	std::cout << "we got the component !" << '\n';
}

*/
#pragma endregion

#pragma region SHOW UI ON SCREEN
/*

**** SHOW UI ON SCREEN ****

sr7 = new SpriteRenderer();
sr7->Init("Sprites/testSprite2.png");
life->AddLeaf(sr7);
uiTransform = new UITransform();
life->AddLeaf(uiTransform);
UIManager::Instance().AddGameObjectToList(life);

*/
#pragma endregion