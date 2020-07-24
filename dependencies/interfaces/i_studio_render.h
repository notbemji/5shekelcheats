#pragma once
#include "i_material_system.hpp"
#include <cstddef>
#include <string_view>

enum class override_type {
    normal = 0,
    build_shadows,
    depth_write,
    custom_material, // weapon skins
    ssao_depth_write
};

class iv_studio_render {
    std::byte pad_0[0x250];
    i_material* material_override;
    std::byte pad_1[0xC];
    override_type override_type;
public:
    bool is_forced() noexcept {
        if (!material_override)
            return override_type == override_type::depth_write || override_type == override_type::ssao_depth_write;
        return std::string_view{ material_override->get_name() }.starts_with("dev/glow");
    }
};