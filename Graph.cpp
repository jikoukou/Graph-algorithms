
#include "Graph.hpp"

template<typename T>
bool Edge<T>::operator<(const Edge<T>& e) const {
    return(this->dist < e.dist);
    
};

template<typename T>
bool Edge<T>::operator>(const Edge<T>& e) const {
    return(this->dist > e.dist);
};

template<typename T>
Graph<T>::Graph(bool isDirected, int capacity) {
    this->Directed = isDirected;
    this->vrt = NULL;
    this->capacity = 0;
};

template <typename T>
bool Graph<T>::contains(const T& info) {
    
    for(int i = 0; i < capacity; i++) {
        if(this->mapping[i] == info) {
            return true;
        }
    }
    return false;
}

template<typename T>
bool Graph<T>::addVtx(const T& info) {
    
    if(!this->contains(info)) {
        capacity++;
        try {
            if(this->vrt != NULL) {
                this->vrt = (int**) realloc(this->vrt, (capacity)*sizeof(int*));
                this->mapping = (T*) realloc(this->mapping, (capacity)*sizeof(T));
                for(int i = 0; i < capacity; i++) {
                    this->vrt[i] = (int*) realloc(this->vrt[i], sizeof(bool)*capacity);
                }
            }
            
            else {
                this->vrt = (int**) malloc(sizeof(int*));
                this->mapping = (T*) malloc(sizeof(T));
                this->vrt[0] = (int*) malloc(sizeof(int));
                
            }
            
            Edge<T> newEdge(info, info, 0); // Dhmiourgw mia kainourgia akmh pou ksekinaei kai teleiwnei ston idio komvo
            this->mapping[capacity - 1] = info;
            
            // Se afto to shmeio exei oloklhrwthei o diplasiasmos h h dimourgia tou neou pinaka
            // Twra tha valw na mhn yparxei kanenas geitonas tou komvou
            // H kainourgia akmh de geitniazei me kanenan
            
            for(int i = 0; i < capacity - 1; i++) {
                this->vrt[i][capacity - 1] = 0;
            }
            
            for(int i = 0; i < capacity; i++) {
                this->vrt[capacity - 1][i] = 0;
            }
            
            
        } catch(bad_alloc &ex) {
            cout << "Memory allocation problem" << endl;
            exit(1);
        }
        return true;
        
    }
    else
        return false;
};

template<typename T>
bool Graph<T>::rmvVtx(const T& info) {
    int i, j = 0;
    
    for(i = 0; i < capacity; i++) {
        if(this->mapping[i] == info) {
            break;
        }
    }
    
    if(i == capacity)
        return false;
    
    // Exw vrei th thesh tou pros diagrafh komvou
    for(; i < capacity - 1; i++) {
        mapping[i] = mapping[i  +1]; // Metafora twn thesewn mnhmhs mia thesh aristera
        free(*(vrt + j) + i);
//        vrt[j][i] = vrt[j][i + 1];
   }
    free(mapping + capacity - 1);
//   delete mapping[capacity - 1];
   for(i = 0; i < capacity; i++) {
       free(*(vrt + i) + capacity - 1);
       delete vrt[i][capacity - 1];
   }
    
    free(vrt + capacity - 1);
//   delete vrt[capacity - 1];
    
   capacity--;
   
   return true;
};

template<typename T>
bool Graph<T>::addEdg(const T& from, const T& to, int cost) {
    int i;
    int fromPos = -1, toPos = -1; // Vriskw tis theseis twn from kai to sto grafo
    
    for(i = 0; i < capacity; i++) {
        if(this->mapping[i] == from) {
            fromPos = i;
            
            if(toPos != -1)
                break;
        }
        if(this->mapping[i] == to) {
            toPos = i;
            if(fromPos != -1)
                break;
        }
    }
    
    if(i == capacity)
        return false;
    vrt[fromPos][toPos] = cost;
    
    if(!Directed) {
        vrt[toPos][fromPos] = cost;
    }
    
    return true;
};

template <typename T>
bool Graph<T>::rmvEdg(const T& from, const T& to) {
    int i;
    short fromPos = -1, toPos = -1;
    
    for(i = 0; i < capacity; i++) {
        if(this->mapping[i] == from) {
            fromPos = i;
            
            if(toPos != -1)
                break;
        }
        if(this->mapping[i] == to) {
            toPos = i;
            if(fromPos != -1)
                break;
        }
    }
    
    if(i == capacity)
        return false;
    
    vrt[fromPos][toPos] = 0;
    vrt[toPos][fromPos] = 0;
    return true;
    
};

template <typename T>
struct list<T> Graph<T>::dfs(const T& info) const {
    int i; 
    std::list<T> Vtces;
    bool NodeFound = false;
    for(i = 0; i < capacity; i++) {
        if(mapping[i] == info) // Evresh tou komvou me plhroforia info
            break;
    }
    
    if(i == capacity)
        return NULL;
    
    Vtces.push_back(mapping[i]);
    for(int j = 0; j < capacity; j++) { // Skanarw grammh grammh gia na vrw tous geitones
        if(j == i)
            continue;
        
        if(vrt[j][i] != 0) {
            struct std::list<T>::iterator it = Vtces.begin();
                for(; it !=  Vtces.end(); ++it) {
                    if(*it == info)
                        NodeFound = true;
            }
            if(!NodeFound)
                Vtces.push_back(vrt[j][i]);
            if(i == capacity - 1)
                break;
            Vtces.merge(dfs(vrt[j][i + 1]));
        }
    }
    return Vtces;
}

// Anazhthsh se platos
template <typename T>
list<T> Graph<T>::bfs(const T& info) const {
    int i; 
    std::list<T> Vtces;
    bool NodeFound = false; // Elegxos ean exei ektypwthei o komvos
    
    for(i = 0; i < capacity; i++) {
        if(mapping[i] == info) // Evresh tou komvou me plhroforia info
            break;
    }
    
    if(i == capacity)
        return NULL;
    
    Vtces.push_back(mapping[i]);
    
    for(; i < capacity; i++) {
        for(int j = 0; j < capacity; j++) {
            if(vrt[j][i] != 0) {
                struct std::list<T>::iterator it = Vtces.begin();
                for(; it !=  Vtces.end(); ++it) {
                    if(*it == info)
                        NodeFound = true;
                }
                if(!NodeFound && j != i)
                    Vtces.push_back(mapping[j]);
            }
        }
    }
    return Vtces;
};