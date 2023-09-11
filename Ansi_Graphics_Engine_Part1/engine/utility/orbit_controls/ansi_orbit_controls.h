// >========================================================================================<
//  �� ansi_orbit_controls.h ������ �ڵ�� Three.js�� OrbitControls.js ������
//  OpenGL�� C++�� �°� ������ ���Դϴ�. ���콺�θ� �����ϴ� ���� ������ �Ͽ�
//  ��ġ �е�� Ű���� ���� ����� ���������� ��ü �ڵ带 ���� �����ôٸ� ������ �ּҸ� �����ϼ���.
//  https://github.com/mrdoob/three.js/blob/master/examples/jsm/controls/OrbitControls.js
//  (�˸�: �ܺο��� ������ ������ �ڵ�� �ּ��� ���� �ʾҽ��ϴ�.)
// >========================================================================================<

#pragma once

#include "utility/orbit_controls/spherical/ansi_spherical.h"
#include "utility/event_listener/ansi_event_listener.h"

namespace ansi
{

	class Camera;
	class Object;

	class OrbitControls : public EventListener
	{
	public:
		explicit OrbitControls(Camera * camera, float panSpeed = 1.0f, float rotateSpeed = 1.0f, float zoomSpeed = 1.0f);

		void OnMouseDown(int button, const glm::vec2 & position) override;
		void OnMouseUp(int button) override;
		void OnMouseMove(const glm::vec2 & position) override;
		void OnMouseWheel(float deltaY) override;

		void Reset();

	private:
		enum class State { None, Rotate, Pan, Dolly };

		void Update();
		void HandleMouseMoveRotate(const glm::vec2 & position);
		void HandleMouseMovePan(const glm::vec2 & position);
		void HandleMouseWheel(float deltaY);
		void Pan(const glm::vec2 & panDelta);
		void RotateLeft(float angle);
		void RotateUp(float angle);
		void PanLeft(float distance, const glm::mat4 & objectMatrix);
		void PanUp(float distance, const glm::mat4 & objectMatrix);
		void DollyOut(float dollyScale);
		void DollyIn(float dollyScale);

		float GetDistance() const;

		bool m_isEnabled;
		float m_dollyScale;
		float m_zoomSpeed;
		float m_rotateSpeed;
		float m_panSpeed;
		float m_minDistance;
		float m_maxDistance;
		float m_minZoom;
		float m_maxZoom;
		float m_minPolarAngle;
		float m_maxPolarAngle;
		float m_minAzimuthAngle;
		float m_maxAzimuthAngle;
		State m_state;
		Spherical m_spherical;
		Spherical m_sphericalDelta;
		glm::vec3 m_panOffset;
		glm::vec2 m_panStart;
		glm::vec2 m_panEnd;
		glm::vec2 m_panDelta;
		glm::vec2 m_rotateStart;
		glm::vec2 m_rotateEnd;
		glm::vec2 m_rotateDelta;
		glm::vec2 m_dollyStart;
		glm::vec2 m_dollyEnd;
		glm::vec2 m_dollyDelta;
		glm::vec3 m_target;
		glm::vec3 m_resetPosition;
		Camera * m_camera;
		Object * m_object;

	};

}
