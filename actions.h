#include <unordered_map>
#include <algorithm>

template <class ActionFunc, class KeyHasher = std::hash<ActionFunc>, class KeyEqualTo = std::equal_to<ActionFunc>>
class Actions
{
public:
    Actions(std::mt19937 &gen);
    Actions(std::mt19937 &gen, std::initializer_list<std::pair<ActionFunc, std::size_t>> actions_);

    void SetActionWeight(const ActionFunc &action, std::size_t weight);
    void RemoveAction(const ActionFunc &action);

    ActionFunc Choose();

private:
    std::mt19937 &gen;
    std::unordered_map<ActionFunc, std::size_t, KeyHasher, KeyEqualTo> actions;
};

template <class ActionFunc, class KeyHasher, class KeyEqualTo>
Actions<ActionFunc, KeyHasher, KeyEqualTo>::Actions(std::mt19937 &gen)
    : gen(gen)
{
}

template <class ActionFunc, class KeyHasher, class KeyEqualTo>
Actions<ActionFunc, KeyHasher, KeyEqualTo>::Actions(std::mt19937 &gen, std::initializer_list<std::pair<ActionFunc, std::size_t>> actions_)
    : gen(gen)
{
    for (auto pair : actions_)
    {
        actions[pair.first] = pair.second;
    }
}

template <class ActionFunc, class KeyHasher, class KeyEqualTo>
void Actions<ActionFunc, KeyHasher, KeyEqualTo>::SetActionWeight(const ActionFunc &action, std::size_t weight)
{
    actions[action] = weight;
}

template <class ActionFunc, class KeyHasher, class KeyEqualTo>
void Actions<ActionFunc, KeyHasher, KeyEqualTo>::RemoveAction(const ActionFunc &action)
{
    actions.erase(action);
}

template <class ActionFunc, class KeyHasher, class KeyEqualTo>
ActionFunc Actions<ActionFunc, KeyHasher, KeyEqualTo>::Choose()
{
    std::vector<std::size_t> weights(actions.size());
    std::vector<ActionFunc> actionVector(actions.size());

    static auto GetAction = [](std::pair<ActionFunc, std::size_t> pair)
    { return pair.first; };
    static auto GetWeight = [](std::pair<ActionFunc, std::size_t> pair)
    { return pair.second; };
    std::transform(actions.begin(), actions.end(), std::back_inserter(actionVector), GetAction);
    std::transform(actions.begin(), actions.end(), std::back_inserter(weights), GetWeight);

    std::discrete_distribution<std::size_t> d(weights.begin(), weights.end());
    return actionVector[d(gen)];
}
