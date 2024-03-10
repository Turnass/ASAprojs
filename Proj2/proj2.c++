#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>

template<typename T> 
using Matrix = std::vector<std::vector<T>>;

void iterativeDfs(Matrix<int>& graph, std::stack<int>& stack, std::vector<bool>& visited, int i){
  std::stack<int> tempStack;
  tempStack.push(i);
  visited[i] = true;

  while (!tempStack.empty()){
    int vertice = tempStack.top();
    bool hasUnvisitedAdj = false;

    for (int adj : graph[vertice]){
      if (!visited[adj]){
        tempStack.push(adj);
        visited[adj] = true;
        hasUnvisitedAdj = true;
        break;
      }
    }
    
    if (!hasUnvisitedAdj){
      stack.push(tempStack.top());
      tempStack.pop();
    }
  }
}
void iterativeLongestPathDfs(Matrix<int>& graph, std::vector<int>& dp, std::stack<int>& stack){
  while (!stack.empty()){
    int vertice = stack.top();
    stack.pop();
    for (int adj : graph[vertice]){
      dp[adj] = std::max(dp[adj], dp[vertice] + 1);
    }
  }
}

Matrix<int> getTranspose(Matrix<int>& graph, int numVertices){
  Matrix<int> transpose(numVertices + 1);
  
  for (int i = 1; i <= numVertices; i++){
    std::vector<int> adjacents = graph[i];
    for (int adj : adjacents){
      transpose[adj].push_back(i);
    }
  }
  return transpose;
}


int main(){
  int numIndividuos, numRelacoes;
  scanf("%d %d", &numIndividuos, &numRelacoes);
  Matrix<int> graph(numIndividuos + 1);
  int a, b;
  for (int i = 0; i < numRelacoes; i++){
    scanf("%d %d", &a, &b);
    graph[a].push_back(b);
  }
  
  std::stack<int> stack;
  std::vector<bool> visited(numIndividuos + 1, false);

  
  for (int i = 1; i <= numIndividuos; i++){
    if (!visited[i]){
      iterativeDfs(graph, stack, visited, i);
    }
  }

  Matrix<int> transpose = getTranspose(graph, numIndividuos);
  std::fill(visited.begin(), visited.end(), false);
  int numComponents = 0;
  std::unordered_map<int,int> verticeSCC;

  while (!stack.empty()){
    int vertice = stack.top();
    stack.pop();
    if(!visited[vertice]){
      std::stack<int> component;
      iterativeDfs(transpose, component, visited, vertice);
      while (!component.empty()){
        int v = component.top();
        component.pop();
        verticeSCC[v] = numComponents;
        
      }
      numComponents++;
    }
  }

  Matrix<int> newGraph(numComponents);
  for (int i = 1; i <= numIndividuos; i++){
    for(int j : graph[i]){
      if (verticeSCC[i] == verticeSCC[j]) {continue;}
      newGraph[verticeSCC[i]].push_back(verticeSCC[j]);
    }
  }
  
  std::vector<int> dp(numComponents);
  std::vector<bool> visitedComponents(numComponents, false);
  std::stack<int> stackComponents;
  for (int i = 0; i < numComponents; i++){
    if (!visitedComponents[i]){
      iterativeDfs(newGraph, stackComponents, visitedComponents, i);
    }
  } 
  iterativeLongestPathDfs(newGraph, dp, stackComponents);

  int maxNum = 0;
  for (int i : dp){
    maxNum = std::max(maxNum, i);
  }

  printf("%d\n", maxNum);
}