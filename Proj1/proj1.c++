#include <iostream>
#include <vector>
#include <algorithm>

int main() {
  int X, Y, numCuts;
  scanf("%d %d", &X, &Y);
  scanf("%d", &numCuts);
  std::vector<std::vector<int>> values(X + 1, std::vector<int>(Y + 1, 0));
  int a, b, c;

  for (int i = 0; i < numCuts; i++) {
    scanf("%d %d %d", &a, &b, &c);
    if(a <= X && b <= Y && values[a][b] < c) {values[a][b] = c;}
    if (a <= Y && b <= X && values[b][a] < c) {values[b][a] = c;}
  }

  for (int x = 1; x <= X; x++) {
    for (int y = 1; y <= Y; y++) {
      for (int i = 1; i < x; i++){
        values[x][y] = std::max(values[x][y], values[i][y] + values[x - i][y]);
      }
      for (int i = 1; i < y; i++){
        values[x][y] = std::max(values[x][y], values[x][i] + values[x][y - i]);
      }
    }
  }

  printf("%d\n", values[X][Y]);
  return 0;
}
