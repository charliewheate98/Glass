#pragma once

#include "Glass/OrthographicCamera.h"

class OrthographicCameraController
{
public:
	OrthographicCameraController() = default;
	OrthographicCameraController(float MoveSpeed, float ZoomAmt);
	~OrthographicCameraController();

	void SimulateControls(Glass::OrthographicCamera& camera, float MoveSpeed, float DeltaTime);
	void SimulateZoomControls(GLFWwindow* window, double xOffset, double yOffset) {}
private:
	float m_MoveSpeed;
	float m_ZoomAmt;
};

