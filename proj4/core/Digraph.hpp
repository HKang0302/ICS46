// Digraph.hpp
//
// ICS 46 Winter 2019
// Project #4: Rock and Roll Stops the Traffic
//
// This header file declares a class template called Digraph, which is
// intended to implement a generic directed graph. The implementation
// uses the adjacency lists technique, so each vertex stores a linked
// list of its outgoing edges.
//
// Along with the Digraph class template is a class DigraphException
// and a couple of utility structs that aren't generally useful outside
// of this header file.
//
// In general, directed graphs are all the same, except in the sense
// that they store different kinds of information about each vertex and
// about each edge; these two types are the type parameters to the
// Digraph class template.

#ifndef DIGRAPH_HPP
#define DIGRAPH_HPP

#include <exception>
#include <functional>
#include <list>
#include <map>
#include <utility>
#include <vector>
#include <queue>

#include <iostream>



// DigraphExceptions are thrown from some of the member functions in the
// Digraph class template, so that exception is declared here, so it
// will be available to any code that includes this header file.

class DigraphException : public std::runtime_error
{
public:
    DigraphException(const std::string& reason);
};


inline DigraphException::DigraphException(const std::string& reason)
    : std::runtime_error{reason}
{
}



// A DigraphEdge lists a "from vertex" (the number of the vertex from which
// the edge points), a "to vertex" (the number of the vertex to which the
// edge points), and an EdgeInfo object.  Because different kinds of Digraphs
// store different kinds of edge information, DigraphEdge is a struct template.

template <typename EdgeInfo>
struct DigraphEdge
{
    int fromVertex;
    int toVertex;
    EdgeInfo einfo;
};



// A DigraphVertex includes two things: a VertexInfo object and a list of
// its outgoing edges.  Because different kinds of Digraphs store different
// kinds of vertex and edge information, DigraphVertex is a struct template.

template <typename VertexInfo, typename EdgeInfo>
struct DigraphVertex
{
    VertexInfo vinfo;
    std::list<DigraphEdge<EdgeInfo>> edges;
};



// Digraph is a class template that represents a directed graph implemented
// using adjacency lists.  It takes two type parameters:
//
// * VertexInfo, which specifies the kind of object stored for each vertex
// * EdgeInfo, which specifies the kind of object stored for each edge
//
// You'll need to implement the member functions declared here; each has a
// comment detailing how it is intended to work.
//
// Each vertex in a Digraph is identified uniquely by a "vertex number".
// Vertex numbers are not necessarily sequential and they are not necessarily
// zero- or one-based.

template <typename VertexInfo, typename EdgeInfo>
class Digraph
{
public:
    // The default constructor initializes a new, empty Digraph so that
    // contains no vertices and no edges.
    Digraph();

    // The copy constructor initializes a new Digraph to be a deep copy
    // of another one (i.e., any change to the copy will not affect the
    // original).
    Digraph(const Digraph& d);

    // The move constructor initializes a new Digraph from an expiring one.
    Digraph(Digraph&& d) noexcept;

    // The destructor deallocates any memory associated with the Digraph.
    ~Digraph() noexcept;

    // The assignment operator assigns the contents of the given Digraph
    // into "this" Digraph, with "this" Digraph becoming a separate, deep
    // copy of the contents of the given one (i.e., any change made to
    // "this" Digraph afterward will not affect the other).
    Digraph& operator=(const Digraph& d);

    // The move assignment operator assigns the contents of an expiring
    // Digraph into "this" Digraph.
    Digraph& operator=(Digraph&& d) noexcept;

    // vertices() returns a std::vector containing the vertex numbers of
    // every vertex in this Digraph.
    std::vector<int> vertices() const;

    // edges() returns a std::vector of std::pairs, in which each pair
    // contains the "from" and "to" vertex numbers of an edge in this
    // Digraph.  All edges are included in the std::vector.
    std::vector<std::pair<int, int>> edges() const;

    // This overload of edges() returns a std::vector of std::pairs, in
    // which each pair contains the "from" and "to" vertex numbers of an
    // edge in this Digraph.  Only edges outgoing from the given vertex
    // number are included in the std::vector.  If the given vertex does
    // not exist, a DigraphException is thrown instead.
    std::vector<std::pair<int, int>> edges(int vertex) const;

    // vertexInfo() returns the VertexInfo object belonging to the vertex
    // with the given vertex number.  If that vertex does not exist, a
    // DigraphException is thrown instead.
    VertexInfo vertexInfo(int vertex) const;

    // edgeInfo() returns the EdgeInfo object belonging to the edge
    // with the given "from" and "to" vertex numbers.  If either of those
    // vertices does not exist *or* if the edge does not exist, a
    // DigraphException is thrown instead.
    EdgeInfo edgeInfo(int fromVertex, int toVertex) const;

    // addVertex() adds a vertex to the Digraph with the given vertex
    // number and VertexInfo object.  If there is already a vertex in
    // the graph with the given vertex number, a DigraphException is
    // thrown instead.
    void addVertex(int vertex, const VertexInfo& vinfo);

    // addEdge() adds an edge to the Digraph pointing from the given
    // "from" vertex number to the given "to" vertex number, and
    // associates with the given EdgeInfo object with it.  If one
    // of the vertices does not exist *or* if the same edge is already
    // present in the graph, a DigraphException is thrown instead.
    void addEdge(int fromVertex, int toVertex, const EdgeInfo& einfo);

    // removeVertex() removes the vertex (and all of its incoming
    // and outgoing edges) with the given vertex number from the
    // Digraph.  If the vertex does not exist already, a DigraphException
    // is thrown instead.
    void removeVertex(int vertex);

    // removeEdge() removes the edge pointing from the given "from"
    // vertex number to the given "to" vertex number from the Digraph.
    // If either of these vertices does not exist *or* if the edge
    // is not already present in the graph, a DigraphException is
    // thrown instead.
    void removeEdge(int fromVertex, int toVertex);

    // vertexCount() returns the number of vertices in the graph.
    int vertexCount() const noexcept;

    // edgeCount() returns the total number of edges in the graph,
    // counting edges outgoing from all vertices.
    int edgeCount() const noexcept;

    // This overload of edgeCount() returns the number of edges in
    // the graph that are outgoing from the given vertex number.
    // If the given vertex does not exist, a DigraphException is
    // thrown instead.
    int edgeCount(int vertex) const;

    // isStronglyConnected() returns true if the Digraph is strongly
    // connected (i.e., every vertex is reachable from every other),
    // false otherwise.
    bool isStronglyConnected() const;

    // findShortestPaths() takes a start vertex number and a function
    // that takes an EdgeInfo object and determines an edge weight.
    // It uses Dijkstra's Shortest Path Algorithm to determine the
    // shortest paths from the start vertex to every other vertex
    // in the graph.  The result is returned as a std::map<int, int>
    // where the keys are vertex numbers and the value associated
    // with each key k is the precedessor of that vertex chosen by
    // the algorithm.  For any vertex without a predecessor (e.g.,
    // a vertex that was never reached, or the start vertex itself),
    // the value is simply a copy of the key.
    std::map<int, int> findShortestPaths(
        int startVertex,
        std::function<double(const EdgeInfo&)> edgeWeightFunc) const;


private:
    // Add whatever member variables you think you need here.  One
    // possibility is a std::map where the keys are vertex numbers
    // and the values are DigraphVertex<VertexInfo, EdgeInfo> objects.

    std::map<int, DigraphVertex<VertexInfo, EdgeInfo>> info;

    // You can also feel free to add any additional member functions
    // you'd like (public or private), so long as you don't remove or
    // change the signatures of the ones that already exist.

};



// You'll need to implement the member functions below.  There's enough
// code in place to make them compile, but they'll all need to do the
// correct thing instead.

template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph()
{
    // std::cout << "constructor" << std::endl;

}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph(const Digraph& d)
{
    // std::cout << "copy constructor" << std::endl;
    this->info = d.info;   
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph(Digraph&& d) noexcept
{
    // std::cout << "move constructor" << std::endl;
    this->info.swap(d.info);
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::~Digraph() noexcept
{
    for(auto it=info.begin(); it!=info.end(); it++)
    {
        it->second.edges.clear();
    }
    info.clear();
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>& Digraph<VertexInfo, EdgeInfo>::operator=(const Digraph& d)
{
    // std::cout << "assignment operator" << std::endl;
    this->info = d.info;
    return *this;
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>& Digraph<VertexInfo, EdgeInfo>::operator=(Digraph&& d) noexcept
{
    // std::cout << "move assignment" << std::endl;
    this->info.swap(d.info);
    return *this;
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<int> Digraph<VertexInfo, EdgeInfo>::vertices() const
{
    // std::cout << "vertices()" << std::endl;
    // use iterator
    auto it = info.begin();
    std::vector<int> result;

    while(it != info.end())
    {
        int k = it->first; // access the key
        result.push_back(k);
        it++;
    }
    

    return result;
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<std::pair<int, int>> Digraph<VertexInfo, EdgeInfo>::edges() const
{
    // std::cout << "edges()" << std::endl;
    std::vector<std::pair<int,int>> result;
    auto it1 = info.begin();
    while(it1 != info.end())
    {
        // list of edges of the vertex it1
        auto itsEdges = it1->second.edges;
        for(auto it2=itsEdges.begin(); it2 != itsEdges.end(); it2++)
        {
            DigraphEdge<EdgeInfo> e = *it2;
            int vFrom = e.fromVertex;
            int vTo = e.toVertex;
            std::pair<int, int> p = std::make_pair(vFrom, vTo);
            result.push_back(p);
        }
        it1++;
    }

    return result;
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<std::pair<int, int>> Digraph<VertexInfo, EdgeInfo>::edges(int vertex) const
{
    // std::cout << "edges(int vertex)" << std::endl;
    std::vector<std::pair<int,int>> result;

    auto search = info.find(vertex);
    if(search != info.end())
    {
        auto itsEdges = search->second.edges;
        for(auto it=itsEdges.begin(); it != itsEdges.end(); it++)
        {
            DigraphEdge<EdgeInfo> e = *it;
            int vFrom = e.fromVertex;
            int vTo = e.toVertex;
            std::pair<int, int> p = std::make_pair(vFrom, vTo);
            result.push_back(p);
        }
    }
    else
    {
        throw DigraphException("Vertex doesn't exist");
    }

    return result;
}


template <typename VertexInfo, typename EdgeInfo>
VertexInfo Digraph<VertexInfo, EdgeInfo>::vertexInfo(int vertex) const
{
    // std::cout << "vertexInfo()" << std::endl;
    auto search = info.find(vertex);
    if(search != info.end())
        return search->second.vinfo;
    else
        throw DigraphException("Vertex doesn't exist");
}


template <typename VertexInfo, typename EdgeInfo>
EdgeInfo Digraph<VertexInfo, EdgeInfo>::edgeInfo(int fromVertex, int toVertex) const
{
    // std::cout << "edgeInfo()" << std::endl;
    auto searchFromVertex = info.find(fromVertex);
    if(searchFromVertex != info.end())
    {
        std::vector<std::pair<int,int>> temp = edges(fromVertex);
        std::pair<int, int> check = std::make_pair(fromVertex, toVertex);

        if(std::find(temp.begin(), temp.end(), check) == temp.end())
            throw DigraphException("That TO vertex doesn't exist");

        std::pair<int,int> check2 = std::make_pair(fromVertex,toVertex);
        std::vector<std::pair<int,int>> edgeList = edges(fromVertex);
        if(std::find(edgeList.begin(), edgeList.end(), check2) == edgeList.end())
            throw DigraphException("The edge doesn't exist");

        // both vertices exist
        auto itsEdges = searchFromVertex->second.edges;
        for(auto it = itsEdges.begin(); it!=itsEdges.end(); it++)
        {
            if(it->toVertex == toVertex)
            {
                return it->einfo;
            }
        }

        
    }
    else
    {
        if(info.find(toVertex) == info.end())
            throw DigraphException("BOTH vertices don't exist");
        else
            throw DigraphException("That FROM vertex doesn't exist");
    } 
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::addVertex(int vertex, const VertexInfo& vinfo)
{
    // std::cout << "addVertex()" << std::endl;
    auto search = info.find(vertex);
    if(search == info.end())
    {
        DigraphVertex<VertexInfo, EdgeInfo> newVertex = DigraphVertex<VertexInfo, EdgeInfo>{vinfo};
        std::pair<int, DigraphVertex<VertexInfo,EdgeInfo>> newPair = std::make_pair(vertex, newVertex);
        info.insert(newPair);
    }
    else
        throw DigraphException("Vertex already exists");
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::addEdge(int fromVertex, int toVertex, const EdgeInfo& einfo)
{
    // std::cout << "addEdge()" << std::endl;
    auto searchFromVertex = info.find(fromVertex);
    if(searchFromVertex!= info.end())
    {
        if(info.find(toVertex) == info.end())
            throw DigraphException("The to vertex doesn't exist");

        DigraphEdge<EdgeInfo> newEdge = DigraphEdge<EdgeInfo> {fromVertex, toVertex, einfo};
        searchFromVertex->second.edges.push_back(newEdge);
    }
    else if(info.find(toVertex) == info.end())
        throw DigraphException("Both vertices don't exist");
    else
        throw DigraphException("The from vertex doesn't exist");
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::removeVertex(int vertex)
{
    auto search = info.find(vertex);
    if(search != info.end())
    {
        // erase vertex and edges from this vertex
        info.erase(vertex);
        // erase edges from any vertices to this vertex
        for(auto it=info.begin(); it!=info.end(); it++)
        {
            auto currentEdges = it->second.edges;
            for(auto it2=currentEdges.begin(); it2!=currentEdges.end(); it2++)
            {
                if(it2->toVertex == vertex)
                    it->second.edges.erase(it2);
            }
        }
    }
    else
        throw DigraphException("Vertex doesn't exist already");
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::removeEdge(int fromVertex, int toVertex)
{
    auto searchFromVertex = info.find(fromVertex);
    if(searchFromVertex!= info.end())
    {
        if(info.find(toVertex) == info.end())
            throw DigraphException("The TO vertex doesn't exist");

        std::pair<int,int> check = std::make_pair(fromVertex,toVertex);
        std::vector<std::pair<int,int>> edgeList = edges(fromVertex);
        if(std::find(edgeList.begin(), edgeList.end(), check) == edgeList.end())
            throw DigraphException("The edge doesn't exist");

        for(auto it=info.at(fromVertex).edges.begin(); it!=info.at(fromVertex).edges.end();  it++)
        {
            if(it->toVertex==toVertex)
            {
                info.at(fromVertex).edges.erase(it);
            }
        }
    }
    else if(info.find(toVertex) == info.end())
        throw DigraphException("Both vertices don't exist");
    else
        throw DigraphException("The FROM vertex doesn't exist");
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::vertexCount() const noexcept
{
    return info.size();
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::edgeCount() const noexcept
{
    int count=0;
    for(auto i=info.begin(); i!=info.end(); i++)
    {
        count += i->second.edges.size();
    }
    return count;
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::edgeCount(int vertex) const
{
    return info.find(vertex)->second.edges.size();
}


template <typename VertexInfo, typename EdgeInfo>
bool Digraph<VertexInfo, EdgeInfo>::isStronglyConnected() const
{
    for(auto i=info.begin(); i!=info.end(); i++)
    {
        if(vertexCount() != edgeCount(i->first))
            return false; 
    }
    return true;
}

typedef std::pair<double, int> pi;

template <typename VertexInfo, typename EdgeInfo>
std::map<int, int> Digraph<VertexInfo, EdgeInfo>::findShortestPaths(
    int startVertex,
    std::function<double(const EdgeInfo&)> edgeWeightFunc) const
{
    struct shortPathVertex
    {
        bool k;
        double d;
        int p;
    };

    std::priority_queue<pi, std::vector<pi>, std::greater<pi>> pq;
    std::map<int, int> result;
    std::map<int,shortPathVertex> m;

    for(auto it=info.begin(); it!=info.end(); it++)
    {
        shortPathVertex spv;
        if(it->first == startVertex)
            spv = shortPathVertex{false, 0, -1};
        else
            spv = shortPathVertex{false, 99999999999999, -1};
        std::pair<int,shortPathVertex> path = std::make_pair(it->first,spv);
        m.insert(path);
        // std::cout << spv.d << std::endl;
    }

    pq.push(std::make_pair(m[startVertex].d, startVertex));

    while(!pq.empty())
    {
        int v = pq.top().second;
        pq.pop();

        if(m[v].k == false)
        {
            m[v].k = true;
            std::pair<int,int> resultElement;
            if(m.at(v).p == -1)
                resultElement = std::make_pair(v, v);
            else
                resultElement = std::make_pair(v, m.at(v).p);
            result.insert(resultElement);

            for(auto i=info.at(v).edges.begin(); i!=info.at(v).edges.end(); i++)
            {
                int w = i->toVertex;
                if(m[w].d > m[v].d + edgeWeightFunc(i->einfo))
                {
                    m[w].d = m[v].d + edgeWeightFunc(i->einfo);
                    m[w].p = v;
                    pq.push(std::make_pair(m[w].d, w));
                }
            }
        }
    }



    return result;
}



#endif // DIGRAPH_HPP

