#include <unordered_map>

#include "product.h"

using namespace std;

// struct ProductHash
// {
//     std::size_t operator()(const IProduct &product) const { return std::hash<Entity>()(product); }
// };
// struct ProductEqualTo
// {
//     bool operator()(const IProduct &first, const IProduct &second) const { return first.operator==(second); }
// };

struct Key
{
    std::string first;
    std::string second;
    int third;

    virtual void dupa() = 0;

    bool operator==(const Key &other) const
    {
        return (first == other.first && second == other.second && third == other.third);
    }
};

namespace std
{

    template <>
    struct hash<Key>
    {
        std::size_t operator()(const Key &k) const
        {
            using std::hash;
            using std::size_t;
            using std::string;

            // Compute individual hash values for first,
            // second and third and combine them using XOR
            // and bit shifting:

            return ((hash<string>()(k.first) ^ (hash<string>()(k.second) << 1)) >> 1) ^ (hash<int>()(k.third) << 1);
        }
    };

}

int main()
{
    unordered_map<const IProduct *, double> m;
}
