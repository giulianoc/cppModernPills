#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <set>
#include <algorithm>


using namespace std;

int main()
{
    // 1. Random access iterator: vector, deque, array (increment, decrement, add/substruct, compare)

    vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    vector<int>::iterator itr_v1 = vec.begin();
    vector<int>::iterator itr_v2 = vec.begin();

    itr_v1 = itr_v1 + 5;
    itr_v1 = itr_v1 - 4;
    if (itr_v1 > itr_v2)
        --itr_v1;         // faster than itr1++ because ++itr1 does not have to return the value

    ++itr_v2;


    // 2. Bidirectional Iterator: list, set/multiset, map/multimap (increment, decrement, no add/substruct, no compare)

    list<int> l = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    list<int>::iterator itr_l = l.begin();

    ++itr_l;
    --itr_l;



    // 3. Forward Iterator: forward_list (increment, no decrement, no add/substruct, no compare)

    forward_list<int> fl = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    forward_list<int>::iterator itr_fl = fl.begin();

    ++itr_fl;


    // Unordered containers provides at least forward iterator


    // 4. Input iterator: read and process values while iterating forward
    int x = *itr_v1;


    // 5. Output iterator: output values while iterating forward
    *itr_v1 = 100;


    // every container has an iterator and a const_iterator
    set<int> myset = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    set<int>::iterator itr_s;
    set<int>::const_iterator citr_s;  // read only access to container element

    for (citr_s = myset.begin(); citr_s != myset.end(); ++citr_s)
        cout << *citr_s << " ";
    cout << endl;


    // for_each(myset.cbegin(), myset.cend(), myFuntion);
    // advance (itr, 5);    itr += 5
    // distance(itr1, itr2)


    // Iterator adaptor (based on predefined iterator) but more powerful
    //  1. Insert iterator
    //  2. Stream iterator
    //  3. Reverse iterator
    //  4. Move iterator


    //  Non-modifying Algorithms:
    //      counting
    //          count, count_if, min_element, max_element, minmax_element
    //      linear search (to be used only if data is not sorted, otherwise binary search has to be used):
    //          find, find_if, find_if_not, search_n, search, find_end, find_first_of, adjacent_find
    //      comparing:
    //          equal, is_permutation, mismatch, lexicographical_compare
    //      attributes:
    //          is_sorted, is_sorted_until, is_partitioned, is_heap, is_heap_until, all_of, any_of, none_of
    //

    vector<int>::iterator itr = min_element(vec.begin(), vec.end());
    // vector<int>::iterator itr = find_if(vec.begin(), vec.end(), myFunction);

    // Modifying algorithms:
    //      copy:
    //          copy, copy_if, copy_n, copy_backward
    //      move:
    //          move, move_backward
    //      transform:
    //          transform
    //      swap:
    //          swap_ranges
    //      fill
    //          fill, fill_n, generate, generate_n
    //      replace
    //          replace, replace_if, replace_copy
    //      remove
    //          remove, remove_if, remove_copy, unique, unique_copy
    //      reverse
    //          reverse, reverse_copy
    //      rotate
    //          rotate, rotate_copy
    //      permute
    //          next_permutation, prev_permutation
    //      shuffle
    //          random_shuffle, shuffle
    //      sort
    //          sort, partial_sort, nth_element, partition, stable_partition, make_heap, pop_heap, push_heap, sort_heap

    // Algorithms working only on sorted data
    //      binary search
    //          binary_search, includes, lower_bound, upper_bound, equal_range
    //      merge
    //          merge, inplace_merge
    //      set operations
    //          set_union, set_intersection, set_difference, set_symmetric_difference
    //      Numeric algorithms
    //              accumulate
    //      inner product
    //          inner_product
    //      partial sum
    //          partial_sum
    //      adjacent difference
    //          adjacence_difference

    // algorithm always process ranges in a half open way,
    // so next sort element from the begin to itr, element pointed by itr excluded
    sort(vec.begin(), itr);

    reverse(itr, vec.end());

    // copy(itr, vec.end(), vec2.begin());  vec2 needs to have space for the elements to be copied





    return 0;

}
