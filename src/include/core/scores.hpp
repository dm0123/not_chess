#pragma once

#include <string>
#include <unordered_map>
#include <core/asset_manager.hpp>

namespace not_chess::core
{
class ScoresAsset : public AbstractAsset
{
public:
    void Load() override;
    std::unordered_map<std::string, int> GetScores() const;
};

class Scores
{
public:
    Scores() = default;
    ~Scores() = default;

    void Save(AssetHandle asset_h);
    void Load(AssetHandle assert_h) const;

    void SetScore(std::string player_name, int number)
    {
        m_scores[player_name] = number;
    }

    std::unordered_map<std::string, int> const& GetScores() const
    {
        return m_scores;
    }

private:
    std::unordered_map<std::string, int> m_scores;
};
} // namespace not_chess::core
