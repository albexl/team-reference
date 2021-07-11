const int maxn = 2000;
const int alpha = 26;
const int init = 'a';

int go[maxn][alpha];
int fail[maxn], final[maxn];
int idx = 2;

void insert(string s, int p){
    int node = 1;
    int n = s.size();
    for(int i = 0; i < n; i++){
        if(!go[node][s[i] - init])
            go[node][s[i] - init] = idx++;
        node = go[node][s[i] - init];
    }
    final[node] |= (1 << p);
}

void build(){
    queue<int> Q;

    for(int i = 0; i < alpha; i++){
        if(!go[1][i])
            go[1][i] = 1;
        else
            Q.push(go[1][i]), fail[go[1][i]] = 1;
    }

    fail[1] = 1;

    while(!Q.empty()){
        int u = Q.front();Q.pop();
        int f = fail[u];
        for(int i = 0; i < alpha; i++){
            if(!go[u][i])
                go[u][i] = go[f][i];
            else{
                fail[go[u][i]] = go[f][i];
                final[go[u][i]] |= final[go[f][i]];
                Q.push(go[u][i]);
            }
        }
    }
}

int next_state(int state, char input){
    int ans = state;
    if(!go[state][input - init])
        ans = fail[state];
    return go[ans][input - init];
}