#include <iostream> 
#include<queue>
#include<unordered_map>
#include<string>
#include<bits/stdc++.h>
using namespace std; 

class node{
public:
    char ch;
    int freq;
    node *left =NULL;
    node* right = NULL;
};

node* getnode(char ch ,int freq,node* left, node* right){
    node* newnode = new node();

    newnode->ch = ch;
    newnode->left = left;
    newnode->right = right;
    newnode->freq = freq;

    return newnode;
}

class compare{
public:
    bool operator()(node * below , node* above){
        return (below->freq > above->freq);
    }
};

void encode (node* root , string str , unordered_map<char,string> &huffcode){
    if(root ==  NULL){
        return;
    }

    if(!root->left && !root->right){
        huffcode[root->ch] = str;
    }

    encode(root->left , str + '0' , huffcode);
    encode(root-> right , str + '1' , huffcode);
}

void decode(node * root , int &index , string code ){
    if(root == NULL) return ;
    if(!root->left && !root->right){
        cout<<root->ch;
        return;
    }
    index ++;
    
    if(code[index] == '0') decode(root->left , index , code );
    else decode(root->right , index , code );
}

void BuildHuffCode(string text){
    unordered_map<char , int> freq;
    for(auto it: text){
        freq[it]++;
    }

    priority_queue<node* , vector<node*> , compare> pq;

    for(auto it : freq){
        pq.push(getnode(it.first , it.second , NULL , NULL));
    }
    
    while(pq.size() != 1){
        node* left = pq.top(); pq.pop();
        node* right = pq.top(); pq.pop();

        int sum = left->freq + right->freq;
        pq.push(getnode('\0', sum , left , right));

    }

    node * root = pq.top();

    
    unordered_map<char,string> huffcode;
    encode(root , "" , huffcode);

    cout<<endl<<"Folowing is the huffmancode obtained:"<<endl<<endl;
    for(auto it : huffcode){
        cout<<it.first<<"-->"<<it.second;
        cout<<endl;
    }

    string code = "";
    cout<<endl<<"Encoded string is: ";
    for(auto  it: text){
        cout<<huffcode[it];
        code += huffcode[it];
    }
    cout<<endl;

    cout<<endl<<"Decoded string is: ";
    int index = -1;
    while (index < (int)code.size() - 2){
        decode(root , index ,code );
    }
    cout<<endl;
    
    int lenOriginalString = 8 * (text.length()) ; 
    int lenEncodedString = ceil(code.length() / 8);
    double rate = ((double)lenEncodedString/lenOriginalString ) * 100;
    cout<<"The string has been compressed to " <<rate <<"% of original string."<<endl; 


}

int main()
{
   string text ;
   cout<<endl<<"Enter the input String: ";
   getline(cin , text);
   BuildHuffCode(text); 

}
