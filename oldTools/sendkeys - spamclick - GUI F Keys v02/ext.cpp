template<class T>
constexpr const T& clamp(const T& v, const T& lo, const T& hi) {
    assert( !(hi < lo) );
    return (v < lo) ? lo : (hi < v) ? hi : v;
}