// TIME
for (int a = 0; ;++a){
    if (clock()>=2.5*CLOCKS_PER_SEC) break;
    // It will stop when 2.5 seconds have passed
}


// LAMBDA
function<bool(int, int)> add_edge = [&](int u, int v)
{
    // code here...
    return true;
};