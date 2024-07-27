#include <bits/stdc++.h>
#include <queue>

using namespace std;
queue<int> qe;

int main()
{
    int n,m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
	qe.push(i);
    }

    int e = 1;
    while(qe.size())
    {
	if(e == m)
	{
	    cout << qe.front() << " ";
	    qe.pop();
	    e = 1;
	}
	else
	{
	    qe.push(qe.front());
	    qe.pop();
	    e++;
	}
    }
}



