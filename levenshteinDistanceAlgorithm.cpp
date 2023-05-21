/// Knuth-Morris-Pratt (KMP) string-searching algorithm

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int findMin(int x, int y, int z){
  if(x <= y && x <= z)
    return x;
  else if(y <=x && y <= z)
    return y;
  else
    return z;
}

void freeMemory(int** arr, int a, int b){
  for(int i = 0; i < a; i++){
    delete[] arr[i];
  }

  delete[] arr;
}

int findDistance(char a[], char b[]){
  // Declaring a 2D array on the heap dynamically:
  int len_a = strlen(a);
  int len_b = strlen(b);
  int** d = new int*[len_a + 1];
  for(int i = 0; i < len_a + 1; i++)
    d[i] = new int[len_b + 1];
  // Initialising first column:
  for(int i = 0; i < len_a + 1; i++)
    d[i][0] = i;
  // Initialising first row:
  for(int j = 0; j < len_b + 1; j++)
    d[0][j] = j;
  // Applying the algorithm:
  int insertion, deletion, replacement;
  for(int i = 1; i < len_a + 1; i++){
    for(int j = 1; j < len_b + 1; j++){
      if(a[i - 1] == b[j - 1]){
        d[i][j] = d[i - 1][j - 1];
      }
      else{
        // Choosing the best option:
        insertion = d[i][j - 1];
        deletion = d[i - 1][j];
        replacement = d[i - 1][j - 1];
        d[i][j] = 1 + findMin(insertion, deletion, replacement);
      }
    }
  }

  int answer = d[len_a][len_b];

  freeMemory(d, len_a + 1, len_b + 1);
  return answer;
}

int main() {
  char a[] = "Kusumito";
  char b[] = "Kamini";
  cout << "Levenshtein Distance: " <<  findDistance(a, b);
  return 0;
}
