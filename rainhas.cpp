#include<bits/stdc++.h>
#define pb push_back
#define pob pop_back

using namespace std;

vector<int> damas;

void backtracking(int pos,int n){
	if(pos == n){
		for(int i=0; i<damas.size(); i++){
            cout << i << ' ' << damas[i] << endl;
        }
        cout << "fim\n";
		return;
	}else{
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
            if(!vai){
                break;
            }
            int xx = pos;
            int yy = i;
            while(1){
                xx += 1;
                yy -= 1;
                if(xx > damas.size() - 1 || yy < 0) break;
                
                if(yy == damas[xx]){
                    vai = 0;
                    break;
                }
            }
            if(!vai){
                break;
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
            if(!vai){
                break;
            }
            xx = pos;
            yy = i;
            while(1){
                xx += 1;
                yy += 1;
                if(xx > damas.size() - 1 || yy > damas.size() - 1) break;
                
                if(yy == damas[xx]){
                    vai = 0;
                    break;
                }
            }
            if(!vai){
                break;
            }
            xx = pos;
            yy = i;
            while(1){
                xx -= 1;
                yy += 1;
                if(xx < 0 || yy > damas.size() - 1) break;
                
                if(yy == damas[xx]){
                    vai = 0;
                    break;
                }
            }
            if(!vai){
                break;
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
	backtracking(0,k);

	return 0;
}