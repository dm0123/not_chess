#pragma once
#include <core/asset_manager.hpp>
#include <string_view>

namespace not_chess
{
namespace core
{
class IDrawable;
}
using EntityId = uint32_t;
constexpr EntityId INVALID_ENTITY = -1;

class AbstractComponent
{
public:
    AbstractComponent(EntityId parent = INVALID_ENTITY) : m_parent(parent)
    {
    }

    virtual ~AbstractComponent() = default;
    AbstractComponent(AbstractComponent&& rhs) = default;
    AbstractComponent(AbstractComponent const& rhs) = default;
    AbstractComponent& operator=(AbstractComponent const& rhs) = default;
    AbstractComponent& operator=(AbstractComponent&& rhs) = default;
    void SetParent(EntityId parent) noexcept { m_parent = parent; }

    std::vector<core::IDrawable*> const& GetDrawables() const noexcept { return m_drawables; }
    virtual std::string_view Name() = 0;
    virtual void AddAsset(std::string_view asset_name) {}

    virtual void Init() {}
    virtual void Update() {}
    virtual void Destroy() {}
protected:
    EntityId m_parent;
    std::vector<core::IDrawable*> m_drawables;
};
}
