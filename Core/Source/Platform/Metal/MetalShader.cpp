#include "sfnpch.h"
#include "Platform/Metal/MetalShader.hpp"
#include "Core/Timer.h"

#include <fstream>
#include <glm/gtc/type_ptr.hpp>

namespace Sophon {
    MetalShader::MetalShader(const std::string& filepath)
    {
        SFN_PROFILE_FUNCTION();

        // Extract name from filepath
        auto lastSlash = filepath.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        auto lastDot = filepath.rfind('.');
        auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
        m_Name = filepath.substr(lastSlash, count);
    }

    MetalShader::MetalShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
        : m_Name(name)
    {
        SFN_PROFILE_FUNCTION();
    }

    MetalShader::~MetalShader()
    {
        SFN_PROFILE_FUNCTION();
    }

    std::string MetalShader::ReadFile(const std::string& filepath)
    {
        SFN_PROFILE_FUNCTION();

        std::string result;
        std::ifstream in(filepath, std::ios::in | std::ios::binary); // ifstream closes itself due to RAII
        if (in) {
            in.seekg(0, std::ios::end);
            size_t size = in.tellg();
            if (size != -1) {
                result.resize(size);
                in.seekg(0, std::ios::beg);
                in.read(&result[0], size);
            } else {
                SFN_CORE_ERROR("Could not read from file '{0}'", filepath);
            }
        } else {
            SFN_CORE_ERROR("Could not open file '{0}'", filepath);
        }

        return result;
    }

    void MetalShader::Bind() const
    {
        SFN_PROFILE_FUNCTION();
    }

    void MetalShader::Unbind() const
    {
        SFN_PROFILE_FUNCTION();
    }

    void MetalShader::SetInt(const std::string& name, int value)
    {
        SFN_PROFILE_FUNCTION();
    }

    void MetalShader::SetIntArray(const std::string& name, int* values, uint32_t count)
    {
        SFN_PROFILE_FUNCTION();
    }

    void MetalShader::SetFloat(const std::string& name, float value)
    {
        SFN_PROFILE_FUNCTION();
    }

    void MetalShader::SetFloat2(const std::string& name, const glm::vec2& value)
    {
        SFN_PROFILE_FUNCTION();
    }

    void MetalShader::SetFloat3(const std::string& name, const glm::vec3& value)
    {
        SFN_PROFILE_FUNCTION();
    }

    void MetalShader::SetFloat4(const std::string& name, const glm::vec4& value)
    {
        SFN_PROFILE_FUNCTION();
    }

    void MetalShader::SetMat4(const std::string& name, const glm::mat4& value)
    {
        SFN_PROFILE_FUNCTION();
    }
}
