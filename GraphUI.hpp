
#ifndef _GRAPH_UI_
#define _GRAPH_UI_


#include "Graph.hpp"
#include "UnionFind.hpp"

#include <fstream>
#include <cstring>
#include <climits>
#include <queue>
#include <stack>

template<typename T>
bool Edge<T>::operator<(const Edge<T>& e) const {
    return(this->dist < e.dist);
    
};

template<typename T>
bool Edge<T>::operator>(const Edge<T>& e) const {
    return(this->dist > e.dist);
};

template<typename T>
Graph<T>::Graph(bool isDirectedGraph) {
    this->Directed = isDirectedGraph;
    this->vrt = NULL;
    this->mapping.clear();
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
};

template<typename T>
bool Graph<T>::addVtx(const T& info) {
    
        
    if(this->capacity != 0) {
        this->capacity++;
        this->vrt = (int**) realloc(this->vrt, (capacity)*sizeof(int*));
        
        for(int i = 0; i < capacity - 1; i++) { // Ftanw mexri to capacity - 2. H thesh capacity - 1 prepei na ginei malloc kathws den exei prohghthei
            this->vrt[i] = (int*) realloc(this->vrt[i], sizeof(int)*(capacity));
            if(this->vrt[i] == NULL) {
                cout << "Mem allocation problem @ realloc\n";
                for(int j = 0; j < capacity; j++) { // Apeleftherwsh ths mnhmhs se periptwsh mh swsths desmefshs
                    if(vrt[j] != NULL)
                        free(vrt[j]);
                    
                }
                free(vrt);
                exit(1);
            }
        }
        this->vrt[capacity - 1] = (int*) malloc(sizeof(int)*(capacity));
        
        if(this->vrt[capacity - 1] == NULL) {
            cout << "Mem allocation problem @ malloc\n";
            exit(1);
        }
    }
    
    else {
        this->capacity++;
        this->vrt = (int**) malloc(sizeof(int*));
        
        if(this->vrt == NULL) {
            cout << "Mem allocation problem @ malloc\n";
            exit(1);
        }
        this->vrt[0] = (int*) malloc(sizeof(int));
        if(this->vrt[0] == NULL) {
            cout << "Mem allocation problem @ malloc\n";
            free(this->vrt);
            exit(1);
        }
        
    }
    
    
    this->mapping.insert(make_pair(capacity - 1, info));
    // Se afto to shmeio exei oloklhrwthei o diplasiasmos h h dimourgia tou neou pinaka
    // Twra tha valw na mhn yparxei kanenas geitonas tou komvou
    // H kainourgia akmh de geitniazei me kanenan
    
    for(int i = 0; i < capacity; i++) {
        this->vrt[i][capacity - 1] = 0;
    }
    
    for(int i = 0; i < capacity - 1; i++) {
        this->vrt[capacity - 1][i] = 0;
    }
        
        
    
        
    return true;
        
};

template<typename T>

Graph<T>::~Graph() {
    for(int i = 0; i < capacity; i++)
        free(vrt[i]);
    
    free(vrt);
}

template<typename T>
bool Graph<T>::rmvVtx(const T& info) {
    int i = capacity;
    map<const int, T> newMap;
    
    
    for(struct map<int, T>::iterator it = mapping.begin(); it != mapping.end(); ++it) {
        if((*it).second == info) {
            i = (*it).first;
            break;
        }
    }
    
    if(i == capacity)
        return false;
    
   int newOld = i;

   for(int j = 0; j < i; j++)
       newMap.insert(make_pair(j, mapping[j]));
   
   for(int j = i; j < capacity - 1; j++)
       newMap.insert(make_pair(j, mapping[j + 1]));
   
   mapping.swap(newMap);
   
   
   for(; i < capacity - 1; i++) {
       for(int j = 0; j <= capacity - 1; j++) {
            vrt[j][i] = vrt[j][i + 1];
       }
   }
   
   
   
   for(int i = 0; i < capacity - 1; i++) {
       vrt[i] = (int*)realloc(vrt[i], sizeof(int)*(capacity - 1));
       
       if(vrt[i] == NULL) {
           cout << "Mem allocation problem @ realloc\n";
           for(int j = 0; j < capacity; j++) {
               if(vrt[j] != NULL)
                   free(vrt[j]);
           }
           free(vrt);
           exit(1);
       }
       for(int j = newOld; j < capacity - 1; j++) {
           vrt[j][i] = vrt[j + 1][i];
       }
   }
   
   free(vrt[capacity - 1]);
   capacity--;
   vrt = (int**) realloc(vrt, sizeof(int*)*(capacity));
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
    
    
    
    if(!Directed) {
        if(vrt[fromPos][toPos] != 0)
            return false;
        
        vrt[fromPos][toPos] = cost;
        vrt[toPos][fromPos] = cost;
    }
    else {
        if(vrt[toPos][fromPos] != 0)
            return false;
        
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
    std::list<T> Vtces, newVtces;
    struct stack<int> next;
    bool NodeFound = false;
    
    for(i = 0; i < capacity; i++) {
        if(mapping.at(i) == info) // Evresh tou komvou me plhroforia info
            break;
    }
    
    if(i == capacity)
        return Vtces;
    
    Vtces.push_back(mapping.at(i));
    
    int iterations = 0;
    stack<int> lastFound;
    lastFound.push(i);
    
    while(true) {
        int j = 0;
        if( lastFound.empty())
            break;
    
        for(j = 0; j < capacity; j++) {
            if(vrt[j][i] != 0) {
                struct std::list<T>::iterator it = Vtces.begin();
                for(; it !=  Vtces.end(); ++it) {
                    if(*it == mapping.at(j)) {
                        NodeFound = true;
                    }
                    
                }
                
                if(!NodeFound) {
                    Vtces.push_back(mapping.at(j));
                    lastFound.push(i);
                    i = j;
                    iterations++;
                    NodeFound = false;
                    break;
                }
            }
            NodeFound = false;
                
        }
        if(j == capacity) {
            
            i = lastFound.top();
            lastFound.pop();
            
        }
    }
    
    return Vtces;
};

// Anazhthsh se platos
template <typename T>
list<T> Graph<T>::bfs(const T& info) const {
    int i; 
    std::list<T> Vtces;
    bool NodeFound = false; // Elegxos ean exei ektypwthei o komvos
    int size = 0;
    struct queue<int> next;

    for(i = 0; i < capacity; i++) {
        
        if(mapping.at(i) == info) // Evresh tou komvou me plhroforia info
            break;
    }
    
    if(i == capacity)
        return Vtces;
    
    Vtces.push_back(mapping.at(i));
    // Arxika pername tis korifes pou synorevoun
    for(int j = 0; j < capacity; j++) {
        if(vrt[j][i] != 0) {
            
            struct std::list<T>::iterator it = Vtces.begin();
            for(; it !=  Vtces.end(); ++it) {
                if(*it == mapping.at(j))
                    NodeFound = true;
                
            }
            if(!NodeFound) {
                Vtces.push_back(mapping.at(j));
                next.push(j);
                size++;
            }
            NodeFound = false;
        }
    }
    
    NodeFound = false;
    while(true) {
        if(size == capacity - 1 || next.empty())
            break;
        
        for(int j = 0; j < capacity; j++) {
            if(vrt[j][next.front()] != 0) {
                struct std::list<T>::iterator it = Vtces.begin();
                for(; it !=  Vtces.end(); ++it) {
                    if(*it == mapping.at(j))
                        NodeFound = true;
                    
                }
                if(!NodeFound) {
                    Vtces.push_back(mapping.at(j));
                    next.push(j);
                    size++;
                }
                NodeFound = false;
            }
        }
        next.pop();
    }

    return Vtces;
    
    
};

template <typename T>
list<T> Graph<T>::dijkstra(const T& from, const T& to) {
    int i, fromPos = -1, toPos = -1, toPos_buff = -1;
    list<T> Vtces;
    pair<int, short> distances[capacity]; // Apostaseis apo tous komvous kai h seira eisagwghs tous
    int iterations = 0;
    list<Edge<T>> addedEdges;
    
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
    
    if(i == capacity) // Epistrofh kenhs listas
        return Vtces;
    
    
    
    distances[fromPos] = make_pair(0, 0);
    
    for(int i = 0; i < capacity; i++) {
        if(i == fromPos)
            continue;
        
        distances[i] = make_pair(INT_MAX, SHRT_MAX);
    }
    Edge<T> minEdge(mapping[0], mapping[0], INT_MAX);
    
    while(true) {        
        
        if(toPos_buff == toPos)
            break;
        
        if(iterations == capacity )
            return Vtces;
        
        
        int fromPos_buff = INT_MAX;
        
        for(int i = 0; i < capacity; i++) {
            for(int j = 0; j < capacity; j++) {
                if(vrt[i][j] != 0 && distances[j].first != INT_MAX && distances[i].first == INT_MAX) {
                    if(vrt[i][j] + distances[j].first < minEdge.dist) {
                        fromPos_buff = j;
                        toPos_buff = i;
                        minEdge.from = mapping[j];
                        minEdge.to = mapping[i];
                        minEdge.dist = vrt[i][j] + distances[j].first;
                        continue;
                        
                    }
                    
                    if(vrt[i][j] + distances[j].first ==  minEdge.dist && distances[fromPos_buff].second >= distances[j].second) {
                        fromPos_buff = j;
                        toPos_buff = i;
                        minEdge.from = mapping[j];
                        minEdge.to = mapping[i];
                        minEdge.dist = vrt[i][j] + distances[j].first;
                    }
                    
                }
            }
        }
        
        distances[toPos_buff].first = minEdge.dist;
        addedEdges.push_front(minEdge);
        iterations++;
        minEdge.dist = INT_MAX;
        distances[toPos_buff].second = iterations; // Ws deftero orisma tou zevgous orizetai h seira eisagwghs 
    }
    
    if(addedEdges.empty())
        return Vtces;
    
    T fromVtx = addedEdges.front().to;
    T toVtx;
    
    
    while(!addedEdges.empty()) {
        
        if(addedEdges.front().to == fromVtx) {
            fromVtx = addedEdges.front().from;
            toVtx = addedEdges.front().to;
            Vtces.push_front(fromVtx);
        }
        
        addedEdges.pop_front();
    }
    Vtces.push_back(to);

    return Vtces;
    
};

template <typename T>

list<Edge<T>> Graph<T>::mst() {
    list <Edge<T>> tree;
    int fromPos = 0, toPos = 0;
    
    if(this->Directed)
        return tree;
    
    int iterations = 0; // Tha xrhsimefsei ston termatismo ths epanalhpshs (infinite loop)
    
    UnionFind edges(capacity);
    Edge<T> minEdge(mapping[0], mapping[0], INT_MAX);
    
    while(true) {
        if(iterations == capacity - 1)
            break;
        
        
        
        for(int j = 0; j < capacity; j++) {
            for(int i = 0; i <= j; i++) { // Skanarw to katw miso tou pinaka
                if(vrt[j][i] < minEdge.dist && vrt[j][i] != 0) {
                    
                    if(!edges.Find(j, i)) {
                        fromPos = j;
                        toPos = i;
                        minEdge.from = mapping[i];
                        minEdge.to = mapping[j];
                        minEdge.dist = vrt[j][i];
                    }
                }
            }
        }
        
        edges.Union(toPos, fromPos);
        tree.push_back(minEdge);
        minEdge.dist = INT_MAX;
        iterations++;
    }
    
    return(tree);
};

template <typename T>
void Graph<T>::print2DotFile(const char* filename) const{
    std::ofstream file;
    file.open(filename);
        
    if(!this->Directed)
        file << "graph G {\n";
    else
        file << "digraph G{\n";
    if(!this->Directed)
        for(int fromPos = 0; fromPos < capacity; fromPos++) {
            for(int i = capacity - 1; i > fromPos; i--) {

                if(vrt[i][fromPos] != 0) 
                    file << this->mapping.at(fromPos) << "--" << this->mapping.at(i)<< "[label = \"" << vrt[i][fromPos] << "\"];" << endl;
            }
        }
    
    else {
        for(int fromPos = 0; fromPos < capacity; fromPos++) {
            for(int i = capacity - 1; i >= 0; i--) {
                if(vrt[i][fromPos] != 0) 
                    file << this->mapping.at(fromPos) << "->" << this->mapping.at(i) << "[label = \"" << vrt[i][fromPos] << "\"];" << endl;
            }
        }
    }
    
    file << "}";
};

template <typename T>
int graphUI() {
  
  string option, line;
  bool digraph = false;
  
  cin >> option;
  if(!option.compare("digraph"))
    digraph = true;
  Graph<T> g(digraph);
  
  while(true) {
    
    std::stringstream stream;
    cin >> option;
    
    if(!option.compare("av")) {
      getline(std::cin, line);
      stream << line;
      T vtx(stream);
      
      if(g.addVtx(vtx))
        cout << "av " << vtx << " OK\n";
      else
        cout << "av " << vtx << " NOK\n";
    }
    
    else if(!option.compare("rv")) {
        getline(std::cin, line);
        stream << line;
        T vtx(stream);
        
        if(g.rmvVtx(vtx))
            cout << "rv " << vtx << " OK\n";
        else
            cout << "rv " << vtx << " NOK\n";
    }
    else if(!option.compare("ae")) {
        getline(std::cin, line);
        stream << line;
        string theline = stream.str();
        
        T from(stream);
        int dist;
        T to(stream);
        getline(stream, theline); // Lamvanw to ypoloipo stream (xwris ta from kai to). Sthn arxh periexei keno
        
        dist = stoi(theline.substr(1, theline.size()));
        
        if(g.addEdg(from, to, dist))
            cout << "ae" << " "<< from << " " << to << " OK\n";
        else
            cout << "ae" << " " << from << " " << to << " NOK\n";
    }
    else if(!option.compare("re")) {
        getline(std::cin, line);
        stream << line;
        
        T from(stream);
        T to(stream);
        
        if(g.rmvEdg(from, to))
            cout << "re" << " " << from << " " << to << " OK\n";
        else
            cout << "re" << " " << from << " " << to << " NOK\n";
    }
    else if(!option.compare("dot")) {
      char f[1] = {'a'};
      g.print2DotFile(f);
    }
    else if(!option.compare("bfs")) {
      getline(std::cin, line);
      stream << line;
      T vtx(stream);
      
      list<T> bfs = g.bfs(vtx);
      cout << "\n----- BFS Traversal -----\n";
      size_t size = 0;
       for(struct list<T>::iterator it = bfs.begin(); it != bfs.end(); ++it) {
           cout << *it ;
           
           if(size != bfs.size() - 1)
               cout << " -> ";
            size++;
       }
      
      cout << "\n-------------------------\n";
    }
    else if(!option.compare("dfs")) {
      getline(std::cin, line);
      stream << line;
      T vtx(stream);
      
      list<T> dfs = g.dfs(vtx);
      size_t size = 0;
      cout << "\n----- DFS Traversal -----\n";
      for(struct list<T>::iterator it = dfs.begin(); it != dfs.end(); ++it) {
           cout << *it ;
           
           if(size != dfs.size() - 1)
               cout << " -> ";
            size++;
       }
      cout << "\n-------------------------\n";
    }
    else if(!option.compare("dijkstra")) {
        
      getline(std::cin, line);
      stream << line;
      T from(stream);
      T to(stream);
      list<T> dijkstra = g.dijkstra(from, to);
      size_t size = 0;
      
      cout << "Dijkstra (" << from << " - " << to <<"): ";
      
      for(struct std::list<T>::iterator it = dijkstra.begin(); it != dijkstra.end(); ++it) {
          cout << *it;
          
          if(size != dijkstra.size() - 1)
              cout << ", ";
          
          size++;
      }
      cout << endl;
    }
    else if(!option.compare("mst")) {
    int sum = 0;
    list<Edge<T>> edges = g.mst();
      cout << "\n--- Min Spanning Tree ---\n";
      for(struct list<Edge<T>>::iterator it = edges.begin(); it != edges.end(); ++it) {
          cout << *it << endl;
          sum += (*it).dist;
      }
      
      cout << "MST Cost: " << sum << endl;
    }
    else if(!option.compare("q")) {
      cerr << "bye bye...\n";
      return 0;
    }
    else if(!option.compare("#")) {
      string line;
      getline(cin,line);
      cerr << "Skipping line: " << line << endl;
    }
    else {
      cout << "INPUT ERROR\n";
      return -1;
    }
  }
  return -1;  
};

#endif
