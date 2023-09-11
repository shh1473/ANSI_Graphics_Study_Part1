#pragma once

#include "core/ansi_core.h"
#include "core/timer/ansi_timer.h"
#include "core/window/ansi_window.h"
#include "core/gui/ansi_gui.h"
#include "core/render/ansi_render.h"
#include "core/render/input_executor/input_param/ansi_input_param.h"
#include "core/render/output_executor/output_param/ansi_output_param.h"
#include "core/render/shader_executor/material/ansi_material.h"

#include "resource/framebuffer/ansi_framebuffer.h"
#include "resource/shader/ansi_shader.h"
#include "resource/texture/ansi_texture.h"
#include "resource/geometry/ansi_geometry.h"
#include "resource/input_elements/ansi_input_elements.h"

#include "scene/ansi_scene.h"
#include "scene/resource_storage/ansi_resource_storage.h"

#include "object/ansi_object.h"
#include "object/component/transform/ansi_transform.h"
#include "object/component/renderer/ansi_renderer.h"
#include "object/component/light/hs_ambient_light/ansi_hs_ambient_light.h"
#include "object/component/light/directional_light/ansi_directional_light.h"
#include "object/component/camera/depth_camera/ansi_depth_camera.h"
#include "object/component/camera/post_effect_camera/ansi_post_effect_camera.h"

#include "utility/orbit_controls/ansi_orbit_controls.h"
