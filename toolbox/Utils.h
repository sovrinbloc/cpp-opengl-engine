//
// Created by Joseph Alai on 7/4/21.
//

#ifndef ENGINE_UTILS_H
#define ENGINE_UTILS_H
template< class Key,
        class T,
        class Comparator,
        class MapAllocator,
        class SetAllocator>
void make_key_set(const std::map<Key,T,Comparator,MapAllocator>& map,
                  std::set<Key,Comparator,SetAllocator>& set)
{
    set.clear();
    typedef typename std::map<Key,T,Comparator,MapAllocator> map_type;
    typename map_type::const_iterator itr = map.begin();
    while (map.end() != itr)
    {
        set.insert((itr++)->first);
    }
    // implement with
    //        std::set<TexturedModel *> texModelSet;
    //        make_key_set(*entities, texModelSet);
}
#endif //ENGINE_UTILS_H
