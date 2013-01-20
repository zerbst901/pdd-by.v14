#include "AmPrngRandom.h"

#include <algorithm>
#include <cstring>

namespace PddBy
{

namespace Magic
{

std::size_t const BoxSize = 256;

uint8_t const NlBox[BoxSize] =
{
    0x96, 0x62, 0x29, 0xe5, 0x0c, 0xb7, 0xbb, 0x1e, 0x7c, 0x1b, 0x80, 0xcd, 0x8d, 0x3b, 0x83, 0x3c,
    0x17, 0xcb, 0x11, 0x87, 0x16, 0x1d, 0xc0, 0xa1, 0xe9, 0xdd, 0x2f, 0x8f, 0x89, 0xfa, 0x58, 0x28,
    0x8b, 0xf2, 0x3a, 0xf4, 0x73, 0xca, 0x55, 0xe7, 0x94, 0x9b, 0xbf, 0xaf, 0x1c, 0xc9, 0x2b, 0x74,
    0xba, 0x53, 0x98, 0x75, 0xbc, 0xaa, 0x6c, 0xec, 0xb1, 0xc4, 0x08, 0x01, 0xc6, 0x59, 0xa4, 0x4a,
    0xfe, 0xc2, 0x86, 0xdf, 0xff, 0x56, 0x6a, 0x79, 0xd8, 0xb8, 0xb3, 0xc5, 0x72, 0xdc, 0x6d, 0x32,
    0x69, 0x4f, 0x7a, 0xf9, 0x7d, 0xdb, 0xb4, 0x92, 0x9c, 0xa9, 0x64, 0xe1, 0x12, 0xd6, 0xfc, 0x15,
    0x9a, 0x02, 0x06, 0xcf, 0x19, 0xd0, 0xd2, 0xbe, 0xb9, 0x50, 0x47, 0x23, 0x5f, 0x7f, 0xe6, 0x5d,
    0xb5, 0x3e, 0x48, 0x33, 0xea, 0xa6, 0x30, 0x43, 0xe0, 0x52, 0x67, 0x34, 0x31, 0xfd, 0x00, 0xae,
    0xc1, 0xf6, 0x18, 0x27, 0x97, 0xf8, 0xe4, 0x7b, 0x8c, 0x2c, 0xb2, 0x22, 0x9f, 0x10, 0xab, 0xf7,
    0xe2, 0x5c, 0x4d, 0x5b, 0x05, 0x1a, 0x39, 0x03, 0x0f, 0x38, 0x04, 0xd1, 0xee, 0x60, 0x99, 0x41,
    0xe8, 0xa7, 0x70, 0xde, 0xed, 0x81, 0x7e, 0x57, 0xd5, 0x82, 0x85, 0x88, 0x6b, 0x0d, 0xd4, 0xa3,
    0xa8, 0xef, 0x84, 0xad, 0x20, 0x21, 0x4c, 0x35, 0x66, 0x42, 0x91, 0x0a, 0x6f, 0x8e, 0x90, 0x0b,
    0xf5, 0x4b, 0x2d, 0xd7, 0xd3, 0x71, 0x44, 0x07, 0x9d, 0xfb, 0x40, 0x68, 0xbd, 0x14, 0x2e, 0x09,
    0xcc, 0x1f, 0xa5, 0x93, 0xc8, 0xc3, 0x54, 0x65, 0x76, 0xa0, 0x77, 0x95, 0xa2, 0x49, 0xd9, 0xac,
    0x8a, 0x3f, 0x24, 0x36, 0x45, 0xf1, 0x13, 0x9e, 0x3d, 0x46, 0xf0, 0xb6, 0x5e, 0x37, 0xc7, 0x6e,
    0x2a, 0xce, 0x63, 0x26, 0xe3, 0x0e, 0x78, 0xb0, 0x4e, 0x5a, 0xf3, 0xeb, 0x51, 0x61, 0x25, 0xda
};

uint8_t const TkBox[BoxSize] =
{
    0x90, 0x16, 0x7c, 0xa3, 0x44, 0x8c, 0xed, 0x83, 0xfc, 0x65, 0xc2, 0x05, 0x46, 0x19, 0x1d, 0x51,
    0x41, 0xaa, 0x4f, 0xbb, 0x02, 0x61, 0x94, 0xf5, 0xac, 0xc8, 0x11, 0x07, 0x1f, 0x34, 0xde, 0xd7,
    0x92, 0xc4, 0x39, 0xfb, 0xfa, 0xe8, 0x62, 0x9c, 0x17, 0x04, 0xb6, 0xdb, 0x01, 0x06, 0xfe, 0xf2,
    0xb3, 0x0c, 0xf9, 0x03, 0xe3, 0xef, 0xb5, 0x31, 0x2c, 0xb2, 0x5e, 0x15, 0x00, 0x23, 0xee, 0x53,
    0x09, 0xd6, 0x3c, 0x5d, 0x36, 0x14, 0xcf, 0x72, 0x6a, 0xae, 0x71, 0xa6, 0x56, 0x84, 0xb7, 0xaf,
    0x5a, 0x79, 0x73, 0x7d, 0x2f, 0x18, 0xe4, 0x49, 0x38, 0xe1, 0x08, 0x47, 0x7a, 0x3a, 0xdf, 0x6c,
    0x91, 0x66, 0x8a, 0x99, 0x86, 0x58, 0x1c, 0xb4, 0x43, 0x8d, 0xbd, 0x4e, 0x24, 0x75, 0xf8, 0xe7,
    0x9f, 0x6b, 0xa5, 0xce, 0xcb, 0xcc, 0x6f, 0x8e, 0xc6, 0x80, 0x54, 0x9e, 0x3f, 0x4a, 0x0a, 0x29,
    0xe0, 0x7e, 0x45, 0xbc, 0x0b, 0x89, 0xd4, 0xd9, 0x95, 0xd8, 0x55, 0xa9, 0x3d, 0x5b, 0xff, 0x32,
    0xb8, 0x8b, 0x0f, 0x37, 0xcd, 0x2b, 0x57, 0x69, 0x78, 0xa8, 0x74, 0x50, 0xd0, 0x85, 0x81, 0x97,
    0xea, 0x4c, 0x6d, 0x13, 0xd2, 0xe2, 0x70, 0x10, 0xf6, 0x2d, 0xc1, 0xd1, 0x7b, 0x96, 0x1b, 0x26,
    0x68, 0xba, 0xb1, 0x12, 0x9d, 0xf0, 0xab, 0xe9, 0x1e, 0xbe, 0x30, 0xa7, 0xc3, 0x8f, 0xf4, 0x33,
    0xa1, 0xf1, 0x20, 0xf7, 0x3e, 0xda, 0x0e, 0xd3, 0xb0, 0x42, 0x64, 0x67, 0x98, 0xe5, 0xd5, 0x6e,
    0xad, 0xe6, 0x9b, 0x2e, 0x88, 0xca, 0x25, 0x2a, 0x0d, 0x4b, 0x52, 0x93, 0x1a, 0xa2, 0xc7, 0xc0,
    0x77, 0x35, 0x27, 0xf3, 0x87, 0x21, 0x48, 0x82, 0xbf, 0xdc, 0xb9, 0x76, 0xdd, 0x5c, 0x60, 0x59,
    0x40, 0x22, 0xec, 0xa0, 0x4d, 0x28, 0x7f, 0xeb, 0x3b, 0xc9, 0x9a, 0x5f, 0xfd, 0x63, 0xc5, 0xa4
};

uint8_t const MkBox[BoxSize] =
{
    0xcd, 0xb1, 0xf3, 0x3a, 0x99, 0x38, 0xf4, 0x97, 0xa0, 0x1a, 0x62, 0xc1, 0x12, 0x52, 0xea, 0xe8,
    0xf5, 0xec, 0x2c, 0x09, 0x7f, 0x6e, 0x79, 0xd1, 0xdf, 0x88, 0x75, 0xba, 0x87, 0x9f, 0xee, 0x53,
    0xaa, 0x3f, 0x56, 0xc2, 0xb5, 0x48, 0xd7, 0x4e, 0xe4, 0x03, 0x33, 0xf9, 0x4f, 0x08, 0x91, 0xd6,
    0x1d, 0xb9, 0xc3, 0x54, 0x72, 0x06, 0x8b, 0x0d, 0xb8, 0xd8, 0x9c, 0xf8, 0x83, 0xc8, 0x4a, 0x77,
    0xfe, 0x44, 0x32, 0xd2, 0x89, 0xcc, 0x20, 0x43, 0x9e, 0x46, 0xe5, 0x27, 0x17, 0x63, 0xa3, 0x96,
    0x30, 0x3d, 0xde, 0xe1, 0x4c, 0x29, 0xc7, 0x95, 0x57, 0x05, 0x04, 0x37, 0xac, 0x64, 0x94, 0x7d,
    0xb7, 0x59, 0x82, 0xd4, 0x7c, 0xf6, 0xce, 0x81, 0xe7, 0xdc, 0x4b, 0x8e, 0xad, 0x60, 0x73, 0x14,
    0x61, 0xcb, 0x66, 0xa6, 0x2f, 0x31, 0x78, 0x5c, 0x5b, 0x41, 0xc0, 0x4d, 0x34, 0xc4, 0xf0, 0x16,
    0x6b, 0x76, 0x15, 0x36, 0xa9, 0x71, 0x26, 0xa4, 0xe0, 0x9a, 0x85, 0x47, 0x13, 0x3c, 0x11, 0x58,
    0x2d, 0x1f, 0x0c, 0x7a, 0xd3, 0x7e, 0x6f, 0x6c, 0xbe, 0x02, 0xfd, 0x3b, 0xcf, 0x0f, 0xa8, 0xb0,
    0x90, 0xfa, 0x5d, 0xda, 0x28, 0x23, 0xbf, 0x42, 0xf1, 0x6a, 0xab, 0xc9, 0xae, 0xc6, 0xe6, 0xd9,
    0x1e, 0x8f, 0xbd, 0x50, 0x86, 0xe2, 0xe3, 0x40, 0x67, 0xdd, 0xaf, 0x10, 0xb4, 0x9b, 0x51, 0x22,
    0x0b, 0x5e, 0xf7, 0x21, 0x25, 0xd5, 0x2b, 0xca, 0x3e, 0x65, 0x1b, 0xbc, 0xc5, 0xa7, 0xff, 0x8d,
    0x74, 0x1c, 0x49, 0x92, 0xb6, 0x45, 0xa5, 0xfc, 0x98, 0x00, 0x68, 0xef, 0xd0, 0x70, 0xb2, 0x39,
    0x01, 0xb3, 0x2a, 0x5f, 0xeb, 0x5a, 0x8c, 0x8a, 0x07, 0x0e, 0xf2, 0x19, 0x7b, 0xbb, 0x18, 0x80,
    0x84, 0x24, 0xa2, 0x0a, 0x69, 0x93, 0xa1, 0xed, 0x9d, 0x55, 0xdb, 0x6d, 0x2e, 0xe9, 0x35, 0xfb
};

uint8_t const MgBox[BoxSize] =
{
    0xf2, 0x94, 0x5a, 0x4b, 0x0f, 0x73, 0xda, 0xdb, 0x83, 0x1d, 0xb3, 0x09, 0xfc, 0x36, 0xb8, 0x46,
    0x41, 0xd4, 0xd0, 0x55, 0xf3, 0x87, 0x76, 0x9a, 0x28, 0x35, 0x71, 0xfb, 0xf7, 0x1c, 0x03, 0x7d,
    0x15, 0x84, 0x0a, 0x43, 0xfa, 0x9e, 0x60, 0x97, 0x98, 0x7e, 0xa3, 0x52, 0xd1, 0x29, 0xa5, 0x59,
    0xc5, 0x7a, 0x2f, 0x25, 0xe1, 0x3b, 0x38, 0x0c, 0x90, 0xc6, 0xd9, 0xf6, 0xd8, 0xcf, 0x16, 0x95,
    0x21, 0xa7, 0x6d, 0x1f, 0x58, 0x51, 0x48, 0x2a, 0xbe, 0xab, 0xf1, 0x5d, 0x9b, 0xf9, 0x80, 0xed,
    0xe5, 0xa6, 0xf5, 0x6f, 0x31, 0xba, 0x79, 0x4f, 0x85, 0x81, 0xb1, 0x23, 0xe4, 0x72, 0xea, 0x2c,
    0xca, 0x6b, 0x6a, 0x1e, 0x5c, 0x04, 0xd5, 0xae, 0xb2, 0xe6, 0xc3, 0x39, 0x4d, 0x5f, 0x3a, 0x45,
    0xb4, 0x67, 0xc8, 0x4e, 0x1a, 0xa4, 0x30, 0xe0, 0xcc, 0x10, 0xbd, 0x33, 0xce, 0xb7, 0xe3, 0x34,
    0xc4, 0x8a, 0xff, 0xb0, 0x3f, 0x02, 0x7c, 0xdc, 0xbf, 0x08, 0xdf, 0x8d, 0xfd, 0x6c, 0xeb, 0x12,
    0x6e, 0x24, 0xcd, 0x2e, 0x99, 0x5e, 0x14, 0x8e, 0x50, 0x7f, 0xaa, 0x13, 0x89, 0x8f, 0x44, 0xe7,
    0x88, 0xb9, 0x20, 0x26, 0xa1, 0xc7, 0x05, 0x07, 0x69, 0xef, 0xde, 0xaf, 0x18, 0xb6, 0xdd, 0x64,
    0x01, 0xd2, 0xa2, 0x2b, 0x0d, 0x11, 0xa9, 0x0b, 0xbb, 0xc2, 0x82, 0xc1, 0xc0, 0xe9, 0x9f, 0x1b,
    0xee, 0xcb, 0x54, 0x00, 0x96, 0xad, 0x27, 0x74, 0x5b, 0x68, 0x0e, 0xe8, 0xd6, 0x22, 0xa8, 0xac,
    0x3e, 0x3d, 0xfe, 0x70, 0x17, 0x77, 0x49, 0x06, 0x86, 0x37, 0x9d, 0xd7, 0x53, 0x63, 0x3c, 0x57,
    0x2d, 0x78, 0xc9, 0x75, 0x8b, 0x62, 0x7b, 0xf8, 0x4c, 0xf0, 0xe2, 0x40, 0xa0, 0x93, 0xb5, 0x19,
    0x65, 0x92, 0x56, 0x32, 0x47, 0xf4, 0x4a, 0x9c, 0x8c, 0xbc, 0x42, 0xec, 0xd3, 0x66, 0x91, 0x61
};

} // namespace Magic

class AmPrngRandom::Impl
{
    typedef uint8_t BoxBuffer[Magic::BoxSize];

public:
    Impl(Buffer const& key, Buffer const& iv, std::size_t dropLength);

    uint8_t GetNext();

private:
    void Setup(Buffer const& key, bool useIv);

    void Morph(Buffer& seed);
    void Cycle(uint8_t& a, BoxBuffer& b, BoxBuffer const& nl, BoxBuffer const& tk, Buffer const& seed);
    void SwapCycle(BoxBuffer& a, BoxBuffer& b);

private:
    std::size_t m_dropLength;
    uint8_t m_m;
    BoxBuffer m_p;
    uint8_t m_z;
    BoxBuffer m_mg;
    std::size_t m_pos;
};

AmPrngRandom::Impl::Impl(Buffer const& key, Buffer const& iv, std::size_t dropLength) :
    m_dropLength(dropLength)
{
    Setup(key, false);

    if (iv.size() > 0)
    {
        Setup(iv, true);
        Setup(key, true);
    }
}

uint8_t AmPrngRandom::Impl::GetNext()
{
    if (!m_dropLength)
    {
        m_dropLength = 1;
    }

    uint8_t result;

    do
    {
        m_m = m_p[m_mg[(m_m + m_p[m_pos]) % Magic::BoxSize]];
        m_z = m_mg[m_p[(m_z + m_mg[m_pos]) % Magic::BoxSize]];
        result = m_p[m_p[(m_p[m_m] + 1) % Magic::BoxSize]];
        std::swap(m_p[m_pos], m_p[m_m]);
        std::swap(m_mg[m_pos], m_mg[m_z]);
        m_pos = (m_pos + 1) % Magic::BoxSize;
    }
    while (--m_dropLength);

    return result;
}

void AmPrngRandom::Impl::Setup(Buffer const& key, bool useIv)
{
    Buffer seed = key;

    if (!useIv)
    {
        for (std::size_t i = 0; i < Magic::BoxSize; i++)
        {
            m_p[i] = i;
        }
    }

    BoxBuffer nl;
    std::memcpy(nl, Magic::NlBox, Magic::BoxSize);

    BoxBuffer tk;
    std::memcpy(tk, Magic::TkBox, Magic::BoxSize);

    m_m = 0;

    Morph(seed);
    Cycle(m_m, m_p, nl, tk, seed);
    SwapCycle(m_p, nl);
    Morph(seed);
    Cycle(m_m, m_p, nl, tk, seed);
    SwapCycle(m_p, tk);
    Morph(seed);
    Cycle(m_m, m_p, nl, tk, seed);
    SwapCycle(m_p, nl);
    Morph(seed);
    Cycle(m_m, m_p, nl, tk, seed);
    Morph(seed);
    SwapCycle(tk, nl);
    Morph(seed);

    if (!useIv)
    {
        std::memcpy(m_mg, Magic::MgBox, Magic::BoxSize);
    }

    m_z = 0;
    Cycle(m_z, m_mg, nl, tk, seed);
    m_pos = 0;
}

void AmPrngRandom::Impl::Morph(Buffer& seed)
{
    for (std::size_t i = 0; i < seed.size(); i++)
    {
        seed[i] = Magic::MkBox[seed[i]];
    }
}

void AmPrngRandom::Impl::Cycle(uint8_t& a, BoxBuffer& b, BoxBuffer const& nl, BoxBuffer const& tk,
    Buffer const& seed)
{
    for (std::size_t i = 0; i < 2048; i++)
    {
        std::size_t const idx = i % Magic::BoxSize;
        a = b[(b[idx] + nl[(a + tk[(seed[i % seed.size()] + idx) % Magic::BoxSize]) % Magic::BoxSize]) % Magic::BoxSize];
        std::swap(b[idx], b[a]);
    }
}

void AmPrngRandom::Impl::SwapCycle(BoxBuffer& a, BoxBuffer& b)
{
    std::swap_ranges(a, a + (sizeof(a) / sizeof(*a)), b);
}

AmPrngRandom::AmPrngRandom(Buffer const& key, Buffer const& iv, std::size_t dropLength) :
    m_impl(new Impl(key, iv, dropLength))
{
    //
}

AmPrngRandom::~AmPrngRandom()
{
    //
}

uint8_t AmPrngRandom::GetNext()
{
    return m_impl->GetNext();
}

} // namespace PddBy
