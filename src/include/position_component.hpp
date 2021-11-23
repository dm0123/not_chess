#include <component.hpp>
#include <entity.hpp>
#include <SFML/System/Vector2.hpp>
#include <utility>

namespace not_chess
{
using namespace std::literals;
/// Position here means relative grid position for every pawn
class PositionComponent : public AbstractComponent
{
public:
    void SetPosition(int row, int column) noexcept
    {
        m_row = row;
        m_column = column;
        Entity& e = ECSManager::Instance().Get(m_parent);
        e.SetPosition(sf::Vector2i(m_row*64.f, m_column*64.f));
    }

    std::pair<int, int> const& GetPosition() const noexcept { return { m_row, m_column }; }
    std::string_view Name() override { return "position"sv; }
    void Update() override { SetPosition(m_row, m_column); }
private:
    int m_row;
    int m_column;
};
} // namespace not_chess
