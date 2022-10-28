#include<bits/stdc++.h>
using namespace std;

//<------------------------------FOR USING PBDS------------------------------->
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp>
#include <functional> // for less
#include <iostream>
using namespace __gnu_pbds;

template <typename T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
//ordered_multiset<int> s;

//Declaring ordered_set
typedef tree<int, null_type, less<int>, rb_tree_tag,
      tree_order_statistics_node_update>
  ordered_set;

ordered_set s;

//<-------------------------------PBDS ENDS HERE----------------------------->


//#pragma GCC optimize "trapv"
#define loop(i,j,k,in)              for(int i=j; i<k; i+=in)
#define rloop(i,j,k,in)             for(int i=j; i>=k; i-=in)
#define mem(a,b)                    memset(a, b, sizeof(a))
#define mod                         1000000007
#define pub                         push_back
#define pob                         pop_back
#define endl                        "\n"

typedef pair<int,int>               pii;
typedef vector<int>                 vi;
typedef vector<char>                vc;
typedef vector<string>              vs;
typedef vector<pii>                 vii;
typedef map<int,int>                mii;
typedef set<int>                    si;
typedef long long int               ll;
typedef unsigned long long int      ull;


void buildtree(int s, int e, int idx, vector<int> &arr, vector<int> &tree){
  if(s == e){
    tree[idx] = arr[s];
    return;
  }
  int mid = (s + e)/2;
  buildtree(s, mid, 2*idx, arr, tree);
  buildtree(mid + 1, e, 2*idx + 1, arr, tree);
  tree[idx] = min(tree[2*idx] , tree[2*idx + 1]);
  return;
}

int query(int ss, int se, int qs ,int qe,int idx, vector<int> &tree){
  if(ss >= qs && se <= qe){
    return tree[idx];
  }

  if(se < qs || qe < ss){
    return INT_MAX;
  }

  int mid = (ss + se) /2;
  int la = query(ss, mid , qs, qe, 2*idx, tree);
  int ra = query(mid + 1, se, qs, qe, 2*idx + 1, tree);
  return min(la, ra);
}

void update(int ss, int se, int i, int idx,int increment, vector<int> &tree){
  if(i < ss || i > se) return;
  if(ss == se){
    tree[idx] += increment;
    return;
  }
  int mid = (ss + se) /2;
  update(ss, mid, i, 2*idx,increment, tree);
  update(mid + 1, se, i , 2*idx + 1, increment, tree);
  tree[idx] = min(tree[2*idx], tree[2*idx + 1]);
  return; 
}

vector<int> getmax(vector<int> &arr, int n){
  vector<int> tree(4*n+5, 0);

  for(auto &it: arr) update(0, n, it, 1, 1, tree);

  vector<int> ans;
  while(i < n){
    int lo = 0;
    int hi = n;
    int idx = -1;
    while(lo <= hi){
      int mid = (lo + hi) >> 1;
      int res = query(0, n, 0, mid, 1, tree);
      if(res < mid){
        idx = mid;
        hi = mid - 1;
      }else{
        lo = mid + 1;
      }
    }

    cout<<"idx : " << idx <<endl ;
    break;


    idx--;
    if(idx == 0){
      ans.push_back(idx);
      update(bit, 1, -1);
      i++;
      continue;
    }
    ans.push_back(idx);
    set<int> st;
    while(i < n && st.size() < idx){
      if(arr[i] < idx)st.insert(arr[i]);
      update(bit, arr[i], -1);
      i++;
    }
  }
  return ans;

}

int main(){
  ios::sync_with_stdio(false);
    cin.tie(0);
  #ifndef ONLINE_JUDGE
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  #endif

  int n;
  cin >> n;
  vector<int> arr(n);
  for(auto &it: arr)cin >> it;

  vector<int> ans = getmax(arr, n);
  for(auto &it : ans) cout << it <<" ";
  cout<<endl;

  
  
  return 0;
}
