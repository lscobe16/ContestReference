#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag,
                  tree_order_statistics_node_update>;
// T.order_of_key(x): number of elements strictly less than x
// *T.find_by_order(k): k-th element
