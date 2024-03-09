#include "sfnpch.h"
#include "Entity.h"

namespace Sophon {

    Entity::Entity(entt::entity handle, Scene* scene)
        : m_EntityHandle(handle)
        , m_Scene(scene)
    {
    }

}
