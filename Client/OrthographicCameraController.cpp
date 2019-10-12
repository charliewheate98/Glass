#include "OrthographicCameraController.h"
#include "Glass/Input.h"

OrthographicCameraController::OrthographicCameraController(float MoveSpeed, float ZoomAmt) :
	m_MoveSpeed(MoveSpeed),
	m_ZoomAmt(ZoomAmt)
{}

OrthographicCameraController::~OrthographicCameraController() {}

void OrthographicCameraController::SimulateControls(Glass::OrthographicCamera& camera, float MoveSpeed, float DeltaTime)
{
	camera.RecalculateViewMatrix();

	if (Glass::Input::IsKeyPressed(GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.GetPosition() += (glm::vec3(1.0f, 0.0f, 0.0f) * MoveSpeed) * DeltaTime;
	}
	else if (Glass::Input::IsKeyPressed(GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.GetPosition() += (glm::vec3(-1.0f, 0.0f, 0.0f) * MoveSpeed) * DeltaTime;
	}
	if (Glass::Input::IsKeyPressed(GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.GetPosition() += (glm::vec3(0.0f, 1.0f, 0.0f) * MoveSpeed) * DeltaTime;
	}
	else if (Glass::Input::IsKeyPressed(GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.GetPosition() += (glm::vec3(0.0f, -1.0f, 0.0f) * MoveSpeed) * DeltaTime;
	}
}
