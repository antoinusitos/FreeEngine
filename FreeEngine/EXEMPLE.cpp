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

/*

**** SPRITE ANIMATOR TEXTURES ****

sr3 = new SpriteAnimator();
sr3->AddTexture("Sprites/Background_01/PARALLAX/background.png");
sr3->AddTexture("Sprites/Background_01/PARALLAX/background2.png");
...
background->AddLeaf(sr3);

*/

/*

**** SPRITE ANIMATOR ATLAS ****

sr3 = new SpriteAnimator();
sr3->AddAtlas("Sprites/Background_01/PARALLAX/background.png", 5, 500, 50, 100, 50, 0, 0);
background->AddLeaf(sr3);

*/