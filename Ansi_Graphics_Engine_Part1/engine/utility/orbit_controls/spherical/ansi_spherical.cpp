// >========================================================================================<
//  본 ansi_spherical.h 파일의 코드는 Three.js의 Spherical.js 파일을
//  OpenGL과 C++에 맞게 변형한 것입니다. 원본 코드를 보고 싶으시다면 다음의 주소를 참고하세요.
//  https://github.com/mrdoob/three.js/blob/master/src/math/Spherical.js
//  (알림: 외부에서 가져와 변형한 코드는 주석을 달지 않았습니다.)
// >========================================================================================<

#include "ansi_spherical.h"

namespace ansi
{

	float Spherical::m_Epsilon{ 0.000001f };

	Spherical::Spherical(float radius, float phi, float theta) :
		m_radius(radius),
		m_phi(phi),
		m_theta(theta)
	{

	}

	void Spherical::MakeSafe()
	{
		m_phi = glm::clamp(m_phi, m_Epsilon, PI - m_Epsilon);
	}

	void Spherical::SetFromCartesianCoords(const glm::vec3 & coords)
	{
		m_radius = glm::length(coords);

		if (m_radius == 0)
		{
			m_theta = 0;
			m_phi = 0;
		}
		else
		{
			m_theta = std::atan2(coords.x, coords.z);
			m_phi = std::acos(glm::clamp(coords.y / m_radius, -1.0f, 1.0f));
		}
	}

	glm::vec3 Spherical::GetFromSphericalCoords() const
	{
		const float sinPhiRadius = std::sin(m_phi) * m_radius;
		return glm::vec3(sinPhiRadius * std::sin(m_theta), std::cos(m_phi) * m_radius, sinPhiRadius * std::cos(m_theta));
	}

}
