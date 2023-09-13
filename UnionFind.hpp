#ifndef _UNION_FIND_HPP_
#define _UNION_FIND_HPP_

// Optional implementation of Union-Find
// Submit blank if you don't implement a
// Union-Find class.

class UnionFind {
    private:
        int *table;
        int capacity;
        
    public:
        UnionFind(int capacity) {
            table = (int*)malloc(sizeof(int)*capacity); // O komvos sth thesh i deixnei ston patera
            
            for(int i = 0; i < capacity; i++) {
                table[i] = i; // Pateras o komvos
                
            }
            this->capacity = capacity;
        }
        
        void Union(int child, int parent) {
            if(table[child] == child)
                table[child] = parent;
            else {
                if(table[parent] == parent)
                    table[parent] = child;
                else
                    table[table[child]] = parent;
            }
            
        }
        
        bool Find(int from, int to) {
            list<int> parents;
            parents.push_back(from);
            
            
            while(true) {
                if(from == table[from])
                    break;
                // Topothethsh olwn twn pateradwn se mia lista
                
                from = table[from];
                parents.push_back(from);
            }
            std::list<int>::iterator it;
            while(true) {
                
                for(std::list<int>::iterator it = parents.begin(); it != parents.end(); ++it) {
                    if(*it == to)
                        return true;
                    
                }
                if(to == table[to])
                    break;
                to = table[to];
            }
            return false;
        }
        
        bool FindVtx(int Vtx) { // Vriskei ean enas komvos anhkei sto grafhma
            
            if(table[Vtx] == Vtx)
                return false;
            
            return true;
        }
        
        int* returnTable() {
            return table;
        }
        
        ~UnionFind() {
            free(table);
        }
};

#endif
