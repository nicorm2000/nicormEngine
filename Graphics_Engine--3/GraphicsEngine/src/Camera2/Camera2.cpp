#include "Camera2.h"

namespace MikkaiEngine
{
	Camera2* Camera2::_mainCamera;
	Camera2::Camera2(Renderer* render, Window* window) : Entity2(render)
	{
		_render = render;
		_window = window;
		Yaw = YAW;
		Pitch = PITCH;
		_moveSpeed = SPEED;
		_sensitivity = SENSITIVITY;
		_offset = OFFSET;
		_fov = ZOOM;
		_near = 0.1f;
		_far = 100.f;
		float width = _window->GetWidth();
		float height = _window->GetHeight();
		SetAspect(width, height);
		UpdateProjection();
		UpdateView();
		_render->SetUniform(_uniformViewPos, "viewPos");
		_mainCamera = this;
		WorldUp = { 0,1,0 };
	}

	void Camera2::SetAspect(float width, float height)
	{
		_aspect = width / height;
	}

	void Camera2::Update()
	{
		if (_target != NULL && _cameraType == CAMERA_TYPE::TPS)
			SetPos(_target->getposition());
		UpdateCameraVectors();
		_render->UseShader();
		_render->UpdateVec3(_uniformViewPos,getPos());
	}
	void Camera2::UpdateCameraVectors()
	{
		if (!_ejes)
			return;
		// calculate the new Front vector
		glm::vec3 direction;
		direction.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		direction.y = sin(glm::radians(Pitch));
		direction.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = (glm::normalize(direction));
		Right = glm::normalize(glm::cross(Front, WorldUp));
		Up    = glm::normalize(glm::cross(Right, Front  ));
		UpdateView();
	}
	void Camera2::UpdateProjection()
	{
		glm::mat4 projection = glm::perspective(glm::radians(_fov), _aspect, _near, _far);
		_render->SetProjection(projection);
	}
	void Camera2::UpdateView()
	{
		switch (_cameraType)
		{
		case CAMERA_TYPE::FPS:
			SetViewMatrix(getPos(), getPos() + Front, Up);
			return;
		case CAMERA_TYPE::TPS:
			if (_target != NULL)
				SetViewMatrix(getPos(), _target->getposition(), Up);
			return;
		case CAMERA_TYPE::FC:
			SetViewMatrix(getPos(), getPos() + Front, Up);
			break;
		}
	}

	void Camera2::UpdateCameraType()
	{
		
		int c = (int)_cameraType;
		c++;
		if (c > (int)CAMERA_TYPE::Max)
		{
			c = 0;
		}
		_cameraType = (CAMERA_TYPE)c;
		switch (_cameraType)
		{
		case CAMERA_TYPE::FC:
			std::cout << "Camera:Free Camera" << std::endl;
			break;
		case CAMERA_TYPE::FPS:
			std::cout << "Camera:First Person" << std::endl;
			break;
		case CAMERA_TYPE::TPS:
			std::cout << "Camera:Third Person" << std::endl;
			break;
		case CAMERA_TYPE::Max:
			std::cout << "Camera:NONE" << std::endl;
			break;
		default:
			break;
		}
	}

	void Camera2::ProcessMouseScroll(float yoffset)
	{
		_fov -= (float)yoffset;
		if (_fov < 1.0f)
			_fov = 1.0f;
		if (_fov > 45.0f)
			_fov = 45.0f;
		UpdateProjection();
		if (_target != NULL && _cameraType == CAMERA_TYPE::TPS)
			SetViewMatrix(getPos(), _target->getposition(), Up);
	}
	void Camera2::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
	{
		xoffset *= _sensitivity;
		yoffset *= _sensitivity;


		Yaw += xoffset;
		Pitch += yoffset;

		// make sure that when pitch is out of bounds, screen doesn't get flipped

		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;

		//std::cout << "x: " << xoffset << " y: " <<yoffset<<std::endl;
		// update Front, Right and Up Vectors using the updated Euler angles
		UpdateCameraVectors();
	}
	void Camera2::SetViewMatrix(glm::vec3 startingPosition, glm::vec3 lookPosition, glm::vec3 upVector)
	{
		targetLook = lookPosition;
		Up = upVector;
		_render->SetView(glm::lookAt(startingPosition, lookPosition, upVector));
	}
	void Camera2::ToogleEjes()
	{
		_ejes = !_ejes;
		
		std::cout << "Camera update set (" << _ejes << ")" << std::endl;
	}
	void Camera2::Move(vec3 v)
	{
		if (GetCameraType() != CAMERA_TYPE::FC)
			return;
		SetPos(getPos() + v * _moveSpeed);
	}

	glm::vec3 Camera2::GetFront()
	{
		return Front;
	}
	glm::vec3 Camera2::GetRight()
	{
		return Right;
	}
	glm::vec3 Camera2::GetUp()
	{
		return Up;
	}
	glm::vec3 Camera2::getPos()
	{
		return  Entity2::getPos();
	}

	float Camera2::GetYaw()
	{
		return Yaw;
	}

	float Camera2::GetPitch()
	{
		return Pitch;
	}

	void Camera2::SetYaw(float yaw)
	{
		this->Yaw = yaw;
	}
	void Camera2::SetPitch(float pitch)
	{
		this->Pitch = pitch;
	}
}
