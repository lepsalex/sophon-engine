#pragma once

#include "Renderer/Shader.h"

namespace Sophon {
    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
        virtual ~OpenGLShader();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual const std::string& GetName() const override { return m_Name; }

    private:
        uint32_t m_RendererId;
        std::string m_Name;
    };
}
