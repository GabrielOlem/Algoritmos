#include<bits/stdc++.h>
#define pb push_back
#define pob pop_back

using namespace std;
int c;
vector<int> damas;
vector<string> tabuleiro;
void backtracking(int pos,int n){
	if(pos == n){
        c++;
	}
    else{
	    for(int i=0; i<n; i++){
            bool vai = 1;
            for(int j=0; j<damas.size(); j++){
                if(i == damas[j] && pos != j){
                    vai = 0;
                    break;
                }
                if(!vai){
                    break;
                }
            }
            int xx = pos;
            int yy = i;
            while(1){
                xx -= 1;
                yy += 1;
                if(xx < 0 || yy > n-1) break;
                if(yy == damas[xx]){
                    vai = 0;
                    break;
                }
            }
            xx = pos;
            yy = i;
            while(1){
                xx -= 1;
                yy -= 1;
                if(xx < 0 || yy < 0) break;
                if(yy == damas[xx]){
                    vai = 0;
                    break;
                }
            }
            if(vai){
                damas.pb(i);
                backtracking(pos+1, n);
                damas.pob();
            }
        }
	}
}

int main(void){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int k;
    cin >> k;
    tabuleiro.resize(k);
    for(int i=0; i<k; i++){
        for(int j=0; j<k; j++){
        tabuleiro[i].push_back('.');
        }
    }
	backtracking(0,k);
    cout << c << endl;
	return 0;
}
