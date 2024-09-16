#include <bits/stdc++.h>
using namespace std;

struct Node
{
    Node *links[26];
    bool flag = false;

    bool contains(char c)
    {
        return links[c - 'a'] != NULL;
    }

    void put(char c, Node *node)
    {
        links[c - 'a'] = node;
    }

    Node *getNext(char c)
    {
        return links[c - 'a'];
    }
};

class Trie
{
private:
    Node *root;

public:
    Trie()
    {
        root = new Node();
    }

    ~Trie()
    {
        
    }

    void insert(string word)
    {
        Node *node = root;
        for (int i = 0; i < word.size(); i++)
        {
            if (!node->contains(word[i]))
            {
                node->put(word[i], new Node());
            }
            node = node->getNext(word[i]);
        }

        node->flag = true;
    }

    int spellCheck(string word)
    {
        Node *node = root;
        for (int i = 0; i < word.size(); i++)
        {
            if (!node->contains(word[i]))
            {
                return 0;
            }
            node = node->getNext(word[i]);
        }

        if (node->flag == true)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    void dfs(Node *node, string &s, vector<string> &words)
    {
        if (node->flag == true)
        {
            words.push_back(s);
        }

        for (int i = 0; i < 26; i++)
        {
            if (node->links[i] != NULL)
            {
                s += ('a' + i);
                Node *temp = node->getNext('a' + i);
                dfs(temp, s, words);
                s.pop_back();
            }
        }
    }

    void autocomplete(string word)
    {
        string curr = "";
        Node *node = root;
        for (int i = 0; i < word.size(); i++)
        {
            if (!node->contains(word[i]))
            {
                return;
            }
            node = node->getNext(word[i]);
            curr += word[i];
        }

        vector<string> words;
        for (int i = 0; i < 26; i++)
        {
            if (node->links[i] != NULL)
            {
                curr += ('a' + i);
                Node *temp = node->getNext('a' + i);
                dfs(temp, curr, words);
                curr.pop_back();
            }
        }

        if (words.size() > 0)
        {
            cout << 1 << endl;
        }

        for (auto it : words)
        {
            cout << it << endl;
        }

        return;
    }

    void autocorrect(string word)
    {
        vector<string> dictionary;
        string curr = "";
        Node *node = root;
        for (int i = 0; i < 26; i++)
        {
            if (node->links[i] != NULL)
            {
                curr += ('a' + i);
                Node *temp = node->getNext('a' + i);
                dfs(temp, curr, dictionary);
                curr.pop_back();
            }
        }

        int count = 0;
        vector<string> correctedWords;
        for (auto it : dictionary)
        {
            int n = it.size();
            int m = word.size();

            vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
            for (int i = 0; i < n; i++)
            {
                dp[i][0] = i;
            }

            for (int i = 0; i < n; i++)
            {
                dp[0][i] = i;
            }

            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= m; j++)
                {
                    if (it[i - 1] == word[j - 1])
                    {
                        dp[i][j] = dp[i - 1][j - 1];
                    }
                    else
                    {
                        dp[i][j] = 1 + min({dp[i - 1][j - 1], dp[i][j - 1], dp[i - 1][j]});
                    }
                }
            }

            if (dp[n][m] <= 3)
            {
                count++;
                correctedWords.push_back(it);
            }
        }

        cout << count << endl;
        for (auto it : correctedWords)
        {
            cout << it << endl;
        }
    }
};

int main()
{
    Trie trie;

    int n, q;
    cin >> n >> q;
    while (n--)
    {
        string s;
        cin >> s;
        trie.insert(s);
    }

    while (q--)
    {
        int a;
        string t;
        cin >> a >> t;

        switch (a)
        {
        case 1:
            cout << trie.spellCheck(t) << endl;
            break;

        case 2:
            trie.autocomplete(t);
            break;

        case 3:
            trie.autocorrect(t);
            break;

        default:
            cout << "Wrong choice given please enter only 1, 2, 3\n";
            break;
        }
    }

    return 0;
}