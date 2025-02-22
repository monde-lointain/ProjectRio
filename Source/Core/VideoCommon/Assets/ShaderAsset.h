// Copyright 2023 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <map>
#include <string>

#include <picojson.h>

#include "VideoCommon/Assets/CustomAsset.h"

namespace VideoCommon
{
struct ShaderProperty
{
  enum class Type
  {
    Type_Undefined,
    Type_Sampler2D,
    Type_Max = Type_Sampler2D
  };
  Type m_type;
  std::string m_description;
};
struct PixelShaderData
{
  static bool FromJson(const CustomAssetLibrary::AssetID& asset_id, const picojson::object& json,
                       PixelShaderData* data);

  // These shader properties describe the input that the
  // shader expects to expose.  The key is text
  // expected to be in the shader code and the propery
  // describes various details about the input
  std::map<std::string, ShaderProperty> m_properties;
  std::string m_shader_source;
};

class PixelShaderAsset final : public CustomLoadableAsset<PixelShaderData>
{
public:
  using CustomLoadableAsset::CustomLoadableAsset;

private:
  CustomAssetLibrary::LoadInfo LoadImpl(const CustomAssetLibrary::AssetID& asset_id) override;
};
}  // namespace VideoCommon
