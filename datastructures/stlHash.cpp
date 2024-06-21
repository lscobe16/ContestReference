#include <ext/pb_ds/assoc_container.hpp>
template<typename T>
struct chash {
	const uint64_t C = ll(2e18 * acos(-1)) | 199; // random odd
	size_t operator()(T o) const {
		return __builtin_bswap64(hash<T>()(o) * C);
}};
template<typename K, typename V>
using hashMap = gp_hash_table<K, V, chash<K>>;
template<typename T>
using hashSet = gp_hash_table<T, null_type, chash<T>>;
