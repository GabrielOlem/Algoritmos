#include<bits/stdc++.h>
#define pb push_back
#define pob pop_back

using namespace std;
int c;
vector<int> damas;
int tabuleiro[100][100];
void backtracking(int pos,int n){
	if(pos == n){
        c++;
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                cout << tabuleiro[i][j] << ' ';   
            }        
            cout << endl;
        }
        cout << endl;
	}
    else{
	    for(int i=0; i<n; i++){
            bool vai = 1;
            for(int j=0; j<pos; j++){
                if(i == damas[j] && pos != j){
                    vai = 0;
                    break;
                }
                if((pos + i) == (j + damas[j]) || (pos - i) == (j - damas[j])){
                    vai = 0;
                    break;    
                }
            }
            if(vai){
                damas.pb(i);
                tabuleiro[pos][i] = 1;  
                backtracking(pos+1, n);
                tabuleiro[pos][i] = 0;
                damas.pob();
            }
        }
        return;
	}
}

int main(void){
	ios::sync_with_stdio(false);
	cin.tie(0);
	backtracking(0,15);
    cout << c << endl;
	return 0;
}
