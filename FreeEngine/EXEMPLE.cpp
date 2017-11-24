/*

**** PARTICLE SYSTEM ****

p = new ParticleSystem();
p->SetSpawnTime(0.02f);
//p->SetPosition(FVector3(100, 700, 0));
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