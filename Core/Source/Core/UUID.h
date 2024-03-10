#pragma once

namespace Sophon {
    class UUID {
    public:
        UUID();
        UUID(uint64_t uuid);
        UUID(const UUID&) = default;

        operator uint64_t() const { return m_UUID; }

    private:
        uint64_t m_UUID;
    };
}

template <>
struct std::hash<Sophon::UUID> {
    std::size_t operator()(const Sophon::UUID& uuid) const
    {
        return (uint64_t)uuid;
    }
};
