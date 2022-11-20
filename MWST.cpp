#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

class MSTGraph
{
    private:
        int V;    // vertices
        int E;   // edges
        pair < int, pair < pair < int, int >, int > > *edges;
        int *parent;

    public:
        MSTGraph (int v, int e)
        {
            V = v;
	    E = e;
            edges = new pair < int, pair < pair < int, int >, int > > [E];
            parent = new int[V];
            
            for(int i = 0; i < V; ++i)
              parent[i] = i;
        }

        ~MSTGraph ()
        {
	      delete[] parent;

              delete[] edges;
        }
   
   void addEdge (int wt, int v1, int v2, int label)
   {
        edges[label] = make_pair(wt, make_pair(make_pair(v1, v2), label));
   }

   int getParent(int v)
   {
      while(parent[v] != v)
      {
        parent[v] = parent[parent[v]];
        v = parent[v];
      }
      return v;
   }

   void joinVertices(int v1, int v2)
   {
      int p = getParent(v1);
      int q = getParent(v2);
      parent[p] = parent[q];
   }

   void processMST(string& outfileName)
  {
     ofstream fout (outfileName);
     sort(edges, edges+E+1);

     /*    
     cout << "SORTED BY WEIGHT" << endl;
     for (int i = 1; i <= E; i++)
     {
       //cout << i << endl;
       cout << edges[i].first << " " << edges[i].second.first.first << " " << edges[i].second.first.second << " " << edges[i].second.second <<  endl;
      // cout << edges[i].second.second  << " " << edges[i].second.first.first << " " << edges[i].second.first.second << endl;
     }
     */

    // return;
     int v1, v2;
     int weight, totalWeight = 0;
   
      for(int i = 1; i <= E; i++)
      {
        v1 = edges[i].second.first.first;
        v2 = edges[i].second.first.second;
        weight = edges[i].first;

        //cout << "v1: " << v1 << " v2: " << v2 << " weight: " << weight << endl;        
        if(getParent(v1) != getParent(v2))
        {
           totalWeight += weight;
           joinVertices(v1, v2);
           fout << setw(4) << right << edges[i].second.second  << ": (" << v1 << ", " << v2 << ") " << setprecision(1) << fixed << (float)weight << endl;
        }    
       }
       fout << "Total Weight = " << setprecision(2) << fixed << (float)totalWeight << endl;
       fout.close();
  }     
};

int main (int argc, char** argv)
{
   if (argc < 3)
   { 
       throw std::invalid_argument("Usage: MWST <INPUT FILE> <OUTPUT FILE>");
   }

   // Sets arguments 
   string infileName = argv[1];
   string outfileName = argv[2];

   ifstream fin (infileName);
  
   int vert, edges, v1, v2;
   int label = 0;
   int wt;
   string line;
   stringstream ss;

   fin >> vert >> edges;

   //cout << "vertices: " << vert << " edges: " << edges <<  endl;

   MSTGraph mst(vert, edges);

   while (!fin.eof())
   {
      getline(fin, line);
      if (line.size() == 0)
        continue;
      ss.str(line);
      ss >> v1 >> v2 >> wt;
      label++;
      //cout << "vertices: " << v1 << " " << v2 << " weight: " << wt << " label: " << label << endl;
      mst.addEdge(wt, v1, v2, label);
      ss.clear();
   }

   mst.processMST(outfileName);
   fin.close();
   return 0;
}
