#include<bits/stdc++.h>
#define pb push_back
#define pob pop_back

using namespace std;
int c;
vector<int> damas;
vector<vector<int> > monstro;
int *fixo;
vector<vector<int> > solutotal;
vector<vector<int> > solufixas;
vector<vector<vector<int> > > monstro3d;
int n, p, f;
int totalzao;
void backtracking(int pos){
	if(pos == 0){
        totalzao++;
        solutotal.pb(damas);
        bool npode = 1;
        for(int i=0; i<n; i++){
            if(damas[n-i-1] != fixo[i] && fixo[i] != -1){
                npode = 0;
                break;
            }
        }
        if(npode){
            c++;
            solufixas.pb(damas);
        }
	}
    else{
        for(int i=0; i<n; i++){
            bool vai = 1;
            for(int j=0; j<n-pos; j++){
                if(i == damas[j] && n-pos != j){
                    vai = 0;
                    break;
                }
                if((n-pos + i) == (j + damas[j]) || (n-pos - i) == (j - damas[j])){
                    vai = 0;
                    break;    
                }
            }
            if(vai){
                damas.pb(i); 
                backtracking(pos-1);
                damas.pob();
            }
        }
        return;
	}
}
int outro;
void outrobacktracking(int pos){
    if(pos == 0){
        outro++;
        monstro3d.pb(monstro);
    }
    else{
        if(pos-1 == f && p != 0){
            for(int i=0; i<solufixas.size(); i++){
                bool pode = 1;
                for(int j=0; j<n-pos; j++){
                    for(int k=0; k<n; k++){
                        if(monstro[j][k] == solufixas[i][k]){
                            pode = 0;
                            break;
                        }
                    }
                }
                if(pode){
                    monstro.pb(solufixas[i]);
                    outrobacktracking(pos-1);
                    monstro.pob();
                }
            }
        }
        else{
            for(int i=0; i<solutotal.size(); i++){
                bool pode = 1;
                for(int j=0; j<n-pos; j++){
                    for(int k=0; k<n; k++){
                        if(monstro[j][k] == solutotal[i][k]){
                            pode = 0;
                            break;
                        }
                    }
                }
                if(pode){
                    monstro.pb(solutotal[i]);
                    outrobacktracking(pos-1);
                    monstro.pob();
                }
            }
        }
    }
}
int main(void){
	ios::sync_with_stdio(false);
	cin.tie(0);
    cin >> n >> p >> f;
    fixo = new int[n];
    for(int i=0; i<n; i++){
        fixo[i] = -1;
    }
    for(int i=0; i<p; i++){
        int x, y;
        cin >> x >> y;
        fixo[x] = y;
    }
    backtracking(n);
    cout << c << endl;
    for(int i=0; i<solufixas.size(); i++){
        cout << i << ": ";
        for(int j=n-1; j>=0; j--){
            cout << solufixas[i][j];
            if(j != 0){
                cout << ' ';
            }
        }
        cout << endl;
        cout << endl;
    }
    if(totalzao < n || n <= 4 || (n != 5 && n != 7)){
        cout << '0' << endl;
    }
    else{
        outrobacktracking(n);
        cout << outro << endl;
        for(int k=0; k<outro; k++){
            cout << k << ":\n";
            for(int i=n-1; i>=0; i--){
                for(int j=n-1; j>=0 ; j--){
                    cout << monstro3d[k][i][j];
                    if(j != 0){
                        cout << ' ';
                    }
                }
                cout << endl;
            }
            cout << endl;
        }
    }
    return 0;
}
