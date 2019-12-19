#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

class TrieNode
{

public:
    char data;
    TrieNode **children;
    bool isTerminal;

    TrieNode(char data)
    {

        this->data = data;
        children = new TrieNode *[26];

        for (int i = 0; i < 26; i++)
        {
            children[i] = NULL;
        }

        isTerminal = false;
    }
};

class Trie
{

    TrieNode *root;

public:
    int count;

    Trie()
    {

        this->count = 0;
        root = new TrieNode('\0');
    }

    bool insertWord(TrieNode *root, string word)
    {

        if (word.size() == 0)
        {
            if (!root->isTerminal)
            {
                root->isTerminal = true;
                return true;
            }
            else
            {
                return false;
            }
        }

        int index = word[0] - 'a';
        TrieNode *child;

        if (root->children[index] != NULL)
        {
            child = root->children[index];
        }
        else
        {
            child = new TrieNode(word[0]);
            root->children[index] = child;
        }

        return insertWord(child, word.substr(1));
    }

    void insertWord(string word)
    {
        if (insertWord(root, word))
        {
            this->count++;
        }
    }

    void possibleWord(TrieNode *root, string ans, string pattern)
    {

        if (!pattern.size() && root->isTerminal == true)
        {
            cout << ans << endl;
        }

        if (pattern.size())
        {
            int index = pattern[0] - 'a';
            if (root->children[index] == NULL)
            {
                return;
            }
            else
            {
                ans += pattern[0];
                possibleWord(root->children[index], ans, pattern.substr(1));
            }
        }
        else
        {
            for (int i = 0; i < 26; i++)
            {
                if (root->children[i] != NULL)
                {
                    string smallAns = ans;
                    smallAns += root->children[i]->data;
                    possibleWord(root->children[i], smallAns, pattern);
                }
            }
        }
    }

    TrieNode *findWord(TrieNode *root, string pattern)
    {

        if (pattern.size() == 0)
        {
            return root;
        }

        int index = pattern[0] - 'a';
        TrieNode *child;

        if (root->children[index] != NULL)
        {
            child = root->children[index];
            return findWord(child, pattern.substr(1));
        }
        else
        {
            return NULL;
        }
    }

    void autoComplete(vector<string> input, string pattern)
    {

        for (int i = 0; i < input.size(); i++)
        {
            insertWord(input[i]);
        }

        string ans = "";

        possibleWord(root, ans, pattern);
    }
};

int main()
{
    Trie t;
    stack <string > recent;
    vector <string > tempstack;

    string word;
    string word1;
    string pattern;
    vector<string> vect;
    int k;
    while (1)
    {
        system("cls");
        gotoxy(50, 19);
        cout << "1.Enter words from Saved file " << endl;
        gotoxy(50, 20);
        cout << "2.Enter new words " << endl;
        gotoxy(50, 21);
        cout << "3.Autosuggestion tab " << endl;
        gotoxy(50, 22);
        cout << "4.Import Prevoius searches for Autosuggest  " << endl;
        gotoxy(50, 23);
        cout << "5. User Searched Words " << endl;
        gotoxy(50, 24);
        cout << "6.Exit " << endl;
        gotoxy(50, 26);
        cout << "Enter your Choice" << endl;
        gotoxy(50, 27);
        cin >> k;
        switch (k)

        {
        case 1:
        {
            system("cls");
            gotoxy(50, 20);
            ifstream infile;
            ofstream ofile;
            string filename;
            cout << "Enter Name of file you want to enter" << endl;
            cin >> filename;
            filename += ".txt";
            infile.open(filename, ios::app);
            ofile.open("words.txt", ios::app);
            int count = 0;
            string wordcount;
            while (infile >> wordcount)
            {
                ++count;
            }
            gotoxy(50, 22);
            cout << "Your file has " << count << " words ,how many do you want to import ?";
            int N;
            cin >> N;
            infile.close();
            infile.open(filename, ios::app);
            string word;
            for (int i = 0; i < N; i++)
            {
                gotoxy(50, 20 + i + 1);
                infile >> word;
                transform(word.begin(), word.end(), word.begin(), ::tolower);
                cout << word;
                ofile << word << endl;
            }
            gotoxy(50, 20 + N + 1);
            cout << "Words Entered Successfully";
            gotoxy(50, 20 + N + 2);
            cout << "Press Any Key To Continue";
            _getch();
            ofile.close();
            infile.close();
            break;
        }
        case 2:
        {
            system("cls");
            gotoxy(50, 20);
            ofstream ofile;
            ofile.open("words.txt", ios::app);
            int N;
            cout << "Enter number of words you want to enter";
            cin >> N;
            for (int i = 0; i < N; i++)
            {
                gotoxy(50, 20 + i + 1);
                cin >> word;
                transform(word.begin(), word.end(), word.begin(), ::tolower);
                ofile << word << endl;
            }
            gotoxy(50, 20 + N + 1);
            cout << "Words Entered Successfully";
            gotoxy(50, 20 + N + 2);
            cout << "Press Any Key To Continue";
            _getch();
            ofile.close();
            break;
        }
        case 3:
        {
            system("cls");
            ifstream ifile;
            gotoxy(50, 20);
            ifile.open("words.txt", ios::in);
            string username;
            cout<<"Enter your Username ";cin>>username;cout<<endl;
            username+=".txt";
            cout << " Enter Pattern ";
            cin >> pattern;
            transform(pattern.begin(), pattern.end(), pattern.begin(), ::tolower);
            ofstream ofile;
            ofile.open(username,ios::app);


            while (ifile >> word1)
            {
                transform(word1.begin(), word1.end(), word1.begin(), ::tolower);
                vect.push_back(word1);
            }
            ifile.close();

            t.autoComplete(vect, pattern);
            recent.push(pattern);

            //bool flag=true;
            string ans;
            cout<<"Did you find your word ? y/n"<<endl;
            cin>>ans;
            if(ans=="n")
            {
                string newword;
                cout<<"Enter the word you were looking for "<<endl;
                cin>>newword;
                ifstream ifile;
                ifile.open("words.txt",ios::in);
                bool flag=false;
                string checkstr;
                while(ifile>>checkstr)
                {
                    if(checkstr==newword)
                    {
                        flag=true;
                        break;
                    }
                }
                if(flag)
                {
                    cout<<"You Entered "<<newword<<" which is already present."<<endl;
                }
                else
                {
                    cout<<"Your word was saved . Thank you "<<endl;
                    recent.push(newword);
                    transform(newword.begin(), newword.end(), newword.begin(), ::tolower);
                    ofile<<newword<<endl;
                }
            }
            ofile.close();
            ifile.close();
            cout << " Press any key to continue "<<endl;
            _getch();
            break;
        }

        case 4:
        {
            system("cls");
            gotoxy(50, 20);
            ifstream infile;
            ofstream ofile;
            string filename;
            cout << "Enter Username " << endl;
            cin >> filename;
            string na=filename;
            filename += ".txt";
            infile.open(filename, ios::app);
            ofile.open("words.txt", ios::app);
            int count = 0;
            string wordcount;
            while (infile >> wordcount)
            {
                ++count;
            }
            gotoxy(50, 22);
            cout << " Hi ,"<<na << " you have "<<count<<" search record, how many do you want to add to Autosuggest? "<<endl;
            int N;
            cin >> N;
            infile.close();
            infile.open(filename, ios::app);
            string word;
            for (int i = 0; i < N; i++)
            {
                gotoxy(50, 20 + i + 1);
                infile >> word;
                cout << word<<endl;
                ofile << word << endl;
            }
            gotoxy(50, 20 + N + 1);
            cout << "Words Entered Successfully"<<endl;
            gotoxy(50, 20 + N + 2);
            cout << "Press Any Key To Continue"<<endl;
            _getch();
            ofile.close();
            infile.close();
            break;
        }
        case 5:
        {
            cout<<"List of words searched by ALL Users "<<endl;

            while(!recent.empty())
            {
                string temp=recent.top();
                tempstack.push_back(temp);
                recent.pop();
                cout<<temp<<endl;
            }
            for(auto x:tempstack)
                recent.push(x);
            cout << "Press Any Key To Continue"<<endl;
            _getch();
            break;
        }
        case 6:
        {
            exit(0);
            break;
        }
        default:
        {
            gotoxy(50, 24);
            cout << "Invalid choice";
            break;
        }
        }
    }
}
