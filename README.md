# ANSI_Graphics_Study_Part1

## 개요
* 본 프로젝트는 Visual Studio 2022 환경에서 C++와 OpenGL (GLFW)을 사용하여 제작된 교육용 그래픽스 엔진입니다.
* ANSI는 'Analyse & Solve It'의 약자로, 이름은 아주대학교 소프트웨어학과의 A.N.S.I 소학회 명칭에서 따왔습니다.
* 아주대학교 학생들만이 아닌 누구나 독학 또는 강의용으로 사용할 수 있습니다.
* 본 엔진은 초급-중급 강의 수준의 기능만을 담고 있으며, [완전한 엔진](https://github.com/shh1473/ANSI_Graphics_Engine)은 개발 중에 있습니다.
* 리포지토리의 라이선스는 LGPL-2.1인데, 이유는 Visual Leak Detector 라이브러리의 라이선스 때문입니다.
* 혹시라도 다른 라이선스로 사용하고 싶을 경우, 해당 프로젝트에서 VLD 관련 부분을 완전히 제거하면 MIT 라이선스로 사용할 수 있습니다.

## 만든이
* 아주대학교 소프트웨어학과 18학번 한수현
* 질문 또는 기타 문의: shh1473@ajou.ac.kr

## 사용법
* 다운로드 받은 상태 그대로 빌드하고 실행하면 됩니다.
* 기본 장면은 ExampleManager 장면으로, 다른 모든 예제 장면에 접근할 수 있습니다.

## 기능 및 장면
1. Hello World Scene: ImGui에서 "Hello, World!" 문자열을 띄우는 장면
1. Color Scene: 단색을 적용한 장면
1. Texture Scene: 텍스처를 적용한 장면
1. Hemisphere Ambient Light Scene: 반구형 앰비언트 라이트를 적용한 장면
1. Directional Light Scene: 디렉셔널 라이트를 적용한 장면
1. Cel Shading Scene: 디렉셔널 라이트와 셀 셰이딩을 적용한 장면
1. Normal Mapping Scene: 법선 매핑을 적용한 장면
1. Shadow Scene: 그림자 매핑을 적용한 장면
1. Final Scene: 조명 두 가지와 법선 매핑, 그림자 매핑, 필터 효과, 블룸 효과를 적용한 장면
