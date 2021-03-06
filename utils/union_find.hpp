#ifndef UNION_FIND_HPP
#define UNION_FIND_HPP


#include <algorithm>
#include <vector>
#include <cmath>


#define Point std::pair<float,float>
#define Edge std::pair<Point,Point>
#define Abstract_edge std::pair<int,int>
#define Weighted_Edge std::pair<float,Abstract_edge>


class Union_find
{
    public:
        std::vector<int> id;

        Union_find(int size) :
            id(size)
        {
            for(int i=0;i<size;i++)
                id[i] = i;
        }

        int root(int index)
        {
            while(index!=id[index])
            {
                id[index] = id[id[index]];
                index = id[index];
            }
            return index;
        }

        int find(int a, int b)
    	{
    		return root(a)==root(b);
    	}

    	void unite(int a, int b)
    	{
            id[root(a)] = b;
    	}
};

float square_dist(const Point& a, const Point& b)
{
    return ((a.first-b.first)*(a.first-b.first)+(a.second-b.second)*(a.second-b.second));
}

std::vector<Edge> minimum_spanning_tree(const std::vector<Point>& all, bool cycle = false)
{
    std::vector<Weighted_Edge> all_edges(all.size()*(all.size()-1)/2);
    int cur = 0;
    for(unsigned int i=0;i<all.size();i++)
        for(unsigned int j=i+1;j<all.size();j++)
        {
            all_edges[cur] = Weighted_Edge(square_dist(all[i],all[j]),Abstract_edge(i,j));
            cur++;
        }
    std::sort(all_edges.begin(),all_edges.end());

    std::vector<Edge> ret(all.size()-1);
    Union_find union_find(all.size());
    unsigned int i = 0, n = 0;
    for(;i<all_edges.size()&&n<ret.size();i++)
    {
        if(!union_find.find(all_edges[i].second.first,all_edges[i].second.second))
        {
            union_find.unite(all_edges[i].second.first,all_edges[i].second.second);
            ret[n] = Edge(all[all_edges[i].second.first],all[all_edges[i].second.second]);
            n++;
        }
    }

    if(cycle&&i<all_edges.size())
        ret.push_back(Edge(all[all_edges[i].second.first],all[all_edges[i].second.second]));

    return ret;
}

#endif
