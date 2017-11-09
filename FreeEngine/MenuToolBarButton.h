#pragma once

#include "ToolBarButton.h"

class SaveToolBarButton;
class NewSceneToolBarButton;
class ExitToolBarButton;

class MenuToolBarButton : public ToolBarButton
{
public:
	MenuToolBarButton();
	~MenuToolBarButton();

	void Execute();

private:
	SaveToolBarButton* save;
	NewSceneToolBarButton* newScene;
	ExitToolBarButton* exit;

	float _sizeX;
};

