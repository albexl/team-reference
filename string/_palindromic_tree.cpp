#include "bits/stdc++.h"

using namespace std;

#define endl '\n'

typedef long long ll;

const int MAXN = 10000 + 5;

struct Node
{
    int start, end;

    int length;

    int insertEdg[26];

    int suffixEdg;
};

Node root1, root2;

Node tree[MAXN];

int currNode;
string s;
int ptr;

void insert(int idx)
{
    int tmp = currNode;
    while (true)
    {
        int curLength = tree[tmp].length;
        if (idx - curLength >= 1 and s[idx] == s[idx-curLength-1])
            break;
        tmp = tree[tmp].suffixEdg;
    }

    if(tree[tmp].insertEdg[s[idx]-'A'] != 0)
    {
        currNode = tree[tmp].insertEdg[s[idx]-'A'];
        return;
    }

    ptr++;

    tree[tmp].insertEdg[s[idx]-'A'] = ptr;

    tree[ptr].length = tree[tmp].length + 2;

    tree[ptr].end = idx;

    tree[ptr].start = idx - tree[ptr].length + 1;

    tmp = tree[tmp].suffixEdg;

    currNode = ptr;
    if (tree[currNode].length == 1)
    {

        tree[currNode].suffixEdg = 2;
        return;
    }
    while (true)
    {
        int curLength = tree[tmp].length;
        if (idx-curLength >= 1 and s[idx] == s[idx-curLength-1])
            break;
        tmp = tree[tmp].suffixEdg;
    }

    tree[currNode].suffixEdg = tree[tmp].insertEdg[s[idx]-'A'];
}

const ll mod = 1e9 + 7;
const ll B = 331;

ll pows[MAXN], H[MAXN], HR[MAXN];

int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    pows[0] = 1LL;
    for(int i = 1; i < MAXN; i++)
        pows[i] = (pows[i - 1] * B) % mod;

    int k;
    cin >> k >> s;

    int ans = 0;

    root1.length = -1;
    root1.suffixEdg = 1;
    root2.length = 0;
    root2.suffixEdg = 1;

    tree[1] = root1;
    tree[2] = root2;
    ptr = 2;
    currNode = 1;

    int l = s.length();

    for (int i = 0; i < l; i++)
        insert(i);

    for (int i = 3; i <= ptr; i++){
        string pal = "";

        int sz = tree[i].end - tree[i].start + 1;

        if(sz < k)
            continue;

        for(int j = tree[i].start; j <= tree[i].end; j++)
            pal += s[j];

        bool ok = false;
        for(int i = 1; i <= sz; i++)
            H[i] = ( (H[i - 1] * B) % mod + (pal[i - 1] - 'a') ) % mod;
        HR[sz + 1] = 0LL;
        for(int i = sz; i >= 1; i--)
            HR[i] = ( (HR[i + 1] * B) % mod + (pal[i - 1] - 'a') ) % mod;

        for(int i = 1; i < sz; i++){
            ll h1 = H[i];
            ll h3 = HR[i + 1];
            ll h4 = ( H[sz] + mod - (H[i] * pows[sz - i]) % mod ) % mod;
            ll h2 = ( HR[1] + mod - (HR[i + 1] * pows[i]) % mod ) % mod;

            if(h1 == h2 && h3 == h4){
                ok = true;
                break;
            }
        }

        if(ok)
            ++ans;
    }

    cout << ans << endl;

    return 0;
}