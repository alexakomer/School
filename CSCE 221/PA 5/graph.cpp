#include <vector>
#include <iostream>
#include "Queue.h"

using namespace std;


class adjMatrix
{
  private:
    int vertices;
    vector<vector<bool>> graph;

  public:
    // constructor
    adjMatrix()
    {
      this -> vertices = 0;
      this -> graph = vector<vector<bool>>(0, vector<bool>(0,0));
    }

    // another constructor
    adjMatrix(int vertices)
    {
      this -> vertices = vertices;
      this -> graph = vector<vector<bool>>(vertices, vector<bool>(vertices,0));
    }

    int size()
    {
      return vertices;
    }

    void displayMatrix() // helper function
    {
      for (int i = 0; i < vertices; ++i)
      {
          for (int j = 0; j < vertices; ++j)
          {
              cout << graph[i][j] << " ";
          }
          cout << endl;
      }
      cout << endl;
    }

    void addVertex()
    {
      vertices++; // increase number of vertices
      // resize both bounds of matrix (increasing by 1)
      graph.resize(vertices);
      for (int i = 0; i < vertices; i++)
      {
        graph[i].resize(vertices); // add vertex
      }
    }

    void addEdge(int u, int v)
    {
      if (u >= vertices || v >= vertices) // check bounds
      {
        cout << "Vertex does not exist!" << endl;
        return;
      }
      graph[u][v] = 1; // add edge
    }

    void removeVertex(int index)
    {
      if (index >= vertices) // check bounds
      {
          cout << "Vertex does not exist!" << endl;
          return;
      }

      int i;

        // removing the vertex
        while (index < vertices - 1)
        {
            // shifting rows left
            for (i = 0; i < vertices; ++i)
            {
                graph[i][index] = graph[i][index + 1];
            }

            // shifting columns upwards
            for (i = 0; i < vertices; ++i)
            {
                graph[index][i] = graph[index + 1][i];
            }
            index++;
        }

        // decreasing the number of vertices
        vertices--;
    }

    void removeEdge(int u, int v)
    {
      if (u >= vertices || v >= vertices) // check bounds
      {
        cout << "Vertex does not exist!" << endl;
        return;
      }
      graph[u][v] = 0; // remove edge
    }

    bool testEdge(int u, int v)
    {
      if (u >= vertices || v >= vertices) // check bounds
      {
        cout << "Vertex does not exist!" << endl;
        return false;
      }
      return graph[u][v]; // return edge
    }

    vector<int> outgoingNeighbors(int index)
    {
      if (index >= vertices) // check bounds
      {
          cout << "Vertex does not exist!" << endl;
          return vector<int>{};
      }
      vector<int> neighbors;
      for (int i = 0; i < vertices; i++)
      {
        if (graph[index][i])
          neighbors.push_back(i);
      }
      return neighbors; // returns list of outgoing edges
    }

    void bfs(int source)
    {
      vector<int> dist(vertices, -1);
      vector<int> parent(vertices);
      for (int i = 0; i < parent.size(); i++) // set parent values to themselves for now
        parent[i] = i;
      Queue q; // create queue from previously created class
      dist[source] = 0;
      q.push(source);
      while(!q.empty()) // while queue has elements in it
      {
        int v = q.front();
        q.pop();
        // cout << v << " ";
        vector<int> neighbors = outgoingNeighbors(v);
        for (int i = 0; i < neighbors.size(); i++) // iterate through adjacent vertices
        {
          if (dist[neighbors[i]] < 0) // notational uncreached distance -1 implies the node is unvisited
          {
            dist[neighbors[i]] = dist[v] + 1; // calculates path length
            parent[neighbors[i]] = v;
            q.push(neighbors[i]);
          }
        }
      }
    }

    void dfs(int source)
    {
      vector<bool> visited(vertices, false);
      vector<int> parent(vertices, -1);
      dfs(source, visited, parent);
    }

    void dfs(int source, vector<bool>& visited, vector<int>& parent)
    {
      visited[source] = true;
      // cout << source << " ";
      vector<int> neighbors = outgoingNeighbors(source);
      for (int i = 0; i < neighbors.size(); i++) // iterate through adjacent vertices
      {
        if (!visited[neighbors[i]]) // notation implies the node is unvisited
        {
          parent[neighbors[i]] = neighbors[i];
          dfs(neighbors[i], visited, parent);
        }
      }
    }
};

class adjList
{
  private:
    struct VertexNode
    {
      int v;
      VertexNode* next;
      VertexNode(int v)
      {
        this -> v = v;
        this -> next = nullptr;
      }
    };

    int vertices;
    vector<VertexNode*> graph;

  public:
    // constructor
    adjList()
    {
      this -> vertices = 0;
      this -> graph = vector<VertexNode*>(vertices, nullptr);
    }

    // another constructor
    adjList(int vertices)
    {
      this -> vertices = vertices;
      this -> graph = vector<VertexNode*>(vertices, nullptr);
    }

    int size()
    {
      return vertices;
    }

    void displayMatrix() // helper function
    {
      for (int i = 0; i < vertices; ++i)
      {
        VertexNode* node = graph[i];
        cout << i << ": ";
          while (node != nullptr)
          {
              cout << node -> v << "->";
              node = node -> next;
          }
          cout << "n" << endl;
      }
      cout << endl;
    }

    void addVertex()
    {
      vertices++; // increase number of vertices
      // resize both bounds of matrix (increasing by 1)
      graph.resize(vertices, nullptr);
    }

    void addEdge(int u, int v)
    {
      VertexNode* node = new VertexNode(v);
      VertexNode* prev = graph[u];
      node -> next = prev;
      graph[u] = node;
    }

    void removeVertex(int index)
    {
      for (int i = 0; i < vertices; i++)
        removeEdge(i,index);
      for (int i = index; i < vertices - 1; i++)
      {
        graph[i] = graph[i + 1];
        VertexNode* node = graph[i];
        while (node != nullptr)
        {
          if (node -> v >= index)
            node -> v = node -> v - 1;
          node = node -> next;
        }
      }
      vertices--;
      graph.resize(vertices);
    }

    void removeEdge(int u, int w)
    {
      VertexNode* curr = graph[u];

      if (curr == nullptr)
        return;

      VertexNode* fast = curr -> next;

      if (curr -> v == w)
      {
        delete curr;
        curr = fast;
        graph[u] = curr;
        return;
      }
      while (fast != nullptr)
      {
        if (fast -> v == w)
        {
          curr -> next = fast -> next;
          delete fast;
          return;
        }
          fast = fast -> next;
          curr = curr -> next;
      }
    }

    bool testEdge(int u, int w)
    {
      VertexNode* curr = graph[u];
      while (curr != nullptr)
      {
        if (curr -> v == w)
        {
          return true;
        }
          curr = curr -> next;
      }
      return false;
    }

    vector<int> outgoingNeighbors(int index)
    {
      vector<int> neighbors;
      VertexNode* curr = graph[index];
      while (curr != nullptr)
      {
          neighbors.push_back(curr -> v);
          curr = curr -> next;
      }
      return neighbors;
    }

    void bfs(int source)
    {
      vector<int> dist(vertices, -1);
      vector<int> parent(vertices);
      for (int i = 0; i < parent.size(); i++) // set parent values to themselves for now
        parent[i] = i;
      Queue q; // create queue from previously created class
      dist[source] = 0;
      q.push(source);
      while(!q.empty()) // while queue has elements in it
      {
        int v = q.front();
        q.pop();
        // cout << v << " ";
        vector<int> neighbors = outgoingNeighbors(v);
        for (int i = 0; i < neighbors.size(); i++) // iterate through adjacent vertices
        {
          if (dist[neighbors[i]] < 0) // notational uncreached distance -1 implies the node is unvisited
          {
            dist[neighbors[i]] = dist[v] + 1; // calculates path length
            parent[neighbors[i]] = v;
            q.push(neighbors[i]);
          }
        }
      }
    }

    void dfs(int source)
    {
      vector<bool> visited(vertices, false);
      vector<int> parent(vertices, -1);
      dfs(source, visited, parent);
    }

    void dfs(int source, vector<bool>& visited, vector<int>& parent)
    {
      visited[source] = true;
      // cout << source << " ";
      vector<int> neighbors = outgoingNeighbors(source);
      for (int i = 0; i < neighbors.size(); i++) // iterate through adjacent vertices
      {
        if (!visited[neighbors[i]]) // notation implies the node is unvisited
        {
          parent[neighbors[i]] = neighbors[i];
          dfs(neighbors[i], visited, parent);
        }
      }
    }
    };

#include <chrono>
#include <cstdlib>

int main()
{

  // testing adjMatrix
  //
  // adjMatrix adj(6);
  // adj.displayMatrix();
  // adj.addVertex();
  // adj.displayMatrix();
  // adj.addEdge(1, 0);
  // adj.addEdge(2, 4);
  // adj.addEdge(1, 2);
  // adj.addEdge(3, 3);
  // adj.addEdge(4, 4);
  // adj.addEdge(1, 4);
  // adj.addEdge(4, 5);
  // adj.displayMatrix();
  // adj.addVertex();
  // adj.displayMatrix();
  // adj.removeVertex(1);
  // adj.displayMatrix();
  // adj.removeVertex(2);
  // adj.displayMatrix();
  //
  // cout << "Edge at (1, 2)? " << adj.testEdge(1, 2) << endl;
  // cout << "Edge at (1, 3)? " << adj.testEdge(1, 3) << endl;
  //
  // int n = 1;
  //
  // adj.addEdge(1, 3);
  // adj.addEdge(1, 6);
  //
  // vector<int> neightborsExample = adj.outgoingNeighbors(n);
  // cout << n << ": ";
  // for (int i = 0; i < neightborsExample.size(); i++)
  //   cout << neightborsExample[i] << " ";
  // cout << endl << endl;
  //
  // adj.displayMatrix();
  //
  // adj.removeEdge(1,2);
  // adj.removeEdge(1,3);
  // adj.removeEdge(2,2);
  // adj.removeEdge(2,3);
  //
  // adj.addVertex();
  // adj.addEdge(0,1);
  // adj.addEdge(1,4);
  // adj.addEdge(4,6);
  // adj.addEdge(6,5);
  // adj.addEdge(2,5);
  // adj.addEdge(2,0);
  // adj.addEdge(0,3);
  // adj.addEdge(1,3);
  // adj.addEdge(3,5);
  // adj.addEdge(3,6);
  // adj.addEdge(3,2);
  // adj.addEdge(3,4);
  //
  // adj.displayMatrix();
  //
  // vector<int> neighbors3 = adj.outgoingNeighbors(3);
  // cout << 3 << ": ";
  // for (int i = 0; i < neighbors3.size(); i++)
  //   cout << neighbors3[i] << " ";
  // cout << endl << endl;

  // Adjacency list Testing

  adjList adj(6);
  // adj.displayMatrix();
  // adj.addVertex();
  // adj.displayMatrix();
  adj.addEdge(1, 0);
  adj.addEdge(2, 4);
  adj.addEdge(1, 2);
  adj.addEdge(3, 3);
  adj.addEdge(4, 4);
  adj.addEdge(1, 4);
  adj.addEdge(4, 5);
  adj.displayMatrix();
  // adj.removeVertex(0);
  adj.removeVertex(2);
  adj.displayMatrix();

  cout << "Edge at (1, 0)? " << adj.testEdge(1, 0) << endl;
  cout << "Edge at (1, 3)? " << adj.testEdge(1, 3) << endl;

  cout << endl;

  cout << "Outgoing neighbors of Vertex 3: ";
  vector<int> neighbors_3 = adj.outgoingNeighbors(3);
  for (int i = 0; i < neighbors_3.size(); i++)
    cout << neighbors_3[i] << " ";
  cout << endl;

  cout << endl;

  // adjList adj(6);
  adj.displayMatrix();
  adj.addVertex();
  adj.displayMatrix();
  adj.addEdge(1, 0);
  adj.addEdge(2, 4);
  adj.addEdge(1, 2);
  adj.addEdge(3, 3);
  adj.addEdge(4, 4);
  adj.addEdge(1, 4);
  adj.addEdge(4, 5);
  adj.displayMatrix();
  adj.addVertex();
  adj.displayMatrix();
  adj.removeVertex(1);
  adj.displayMatrix();
  adj.removeVertex(2);
  adj.displayMatrix();

  cout << "Edge at (1, 2)? " << adj.testEdge(1, 2) << endl;
  cout << "Edge at (1, 3)? " << adj.testEdge(1, 3) << endl;

  int n = 1;

  adj.addEdge(1, 3);
  adj.addEdge(1, 6);

  vector<int> neightborsExample = adj.outgoingNeighbors(n);
  cout << n << ": ";
  for (int i = 0; i < neightborsExample.size(); i++)
    cout << neightborsExample[i] << " ";
  cout << endl << endl;

  adj.displayMatrix();

  adj.removeEdge(1,2);
  adj.removeEdge(1,3);
  adj.removeEdge(2,2);
  adj.removeEdge(2,3);

  adj.addVertex();
  adj.addEdge(0,1);
  adj.addEdge(1,4);
  adj.addEdge(4,6);
  adj.addEdge(6,5);
  adj.addEdge(2,5);
  adj.addEdge(2,0);
  adj.addEdge(0,3);
  adj.addEdge(1,3);
  adj.addEdge(3,5);
  adj.addEdge(3,6);
  adj.addEdge(3,2);
  adj.addEdge(3,4);

  adj.displayMatrix();

  vector<int> neighbors3 = adj.outgoingNeighbors(3);
  cout << 3 << ": ";
  for (int i = 0; i < neighbors3.size(); i++)
    cout << neighbors3[i] << " ";
  cout << endl;

  // cycle

  // int n = 100000;
  //
  // adjList adj(n);
  // for (int i = 0; i < n; i++)
  // {
  //   adj.addEdge(i, (i + 1) % n);
  // }
  //
  // chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
  // adj.bfs(0);
  // chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now(); //end clock
  // cout << "bfs adjList time elapsed: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " µs" <<  endl; //take delta time in microseconds
  //
  // chrono::high_resolution_clock::time_point start2 = chrono::high_resolution_clock::now();
  // adj.dfs(0);
  // chrono::high_resolution_clock::time_point end2 = chrono::high_resolution_clock::now(); //end clock
  // cout << "dfs adjList time elapsed: " << chrono::duration_cast<chrono::microseconds>(end2-start2).count() << " µs" <<  endl; //take delta time in microseconds


  // clique

  // int n = 100000;
  //
  // adjList adj(n);
  // for (int i = 0; i < n; i++)
  // {
  //   for (int j = 0; j < n; j++)
  //   {
  //     adj.addEdge(i, j);
  //     adj.addEdge(j, i);
  //   }
  // }
  //
  // // adj.displayMatrix();
  //
  // chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
  // adj.bfs(0);
  // chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now(); //end clock
  // cout << "bfs adjList time elapsed: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " µs" <<  endl; //take delta time in microseconds
  //
  // chrono::high_resolution_clock::time_point start2 = chrono::high_resolution_clock::now();
  // adj.dfs(0);
  // chrono::high_resolution_clock::time_point end2 = chrono::high_resolution_clock::now(); //end clock
  // cout << "dfs adjList time elapsed: " << chrono::duration_cast<chrono::microseconds>(end2-start2).count() << " µs" <<  endl; //take delta time in microseconds

  // random 0.25

  // int n = 100000;
  //
  // adjMatrix adj(n);
  // for (int i = 0; i < n; i++)
  // {
  //   for (int j = 0; j < n; j++)
  //   {
  //     int rand1 = rand() % 4;
  //     int rand2 = rand() % 4;
  //     if (rand1)
  //       adj.addEdge(i, j);
  //     if (rand2)
  //       adj.addEdge(j, i);
  //   }
  // }
  //
  // // adj.displayMatrix();
  //
  // chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
  // adj.bfs(0);
  // chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now(); //end clock
  // cout << "bfs adjList time elapsed: " << chrono::duration_cast<chrono::microseconds>(end-start).count() << " µs" <<  endl; //take delta time in microseconds
  //
  // chrono::high_resolution_clock::time_point start2 = chrono::high_resolution_clock::now();
  // adj.dfs(0);
  // chrono::high_resolution_clock::time_point end2 = chrono::high_resolution_clock::now(); //end clock
  // cout << "dfs adjList time elapsed: " << chrono::duration_cast<chrono::microseconds>(end2-start2).count() << " µs" <<  endl; //take delta time in microseconds


  return 0;
}
