#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <cstring>
using namespace std;

struct trie{
    map<char,trie*> c_map;
    bool isword;
    int occurence;
    int T[3][10];
};

trie* newnode(){
    trie* node = new trie;
    node->isword = false;
    node->occurence = 0;  
    for(int j=0; j<10; j++){
        for(int i=0; i<3; i++){
                node->T[i][j] = 0;
            }
    }
    return node;
};

bool search_bool(trie* head, char* str){    
    char* c =str;
    // return false if Trie is empty
    if (head == nullptr) {
        return false;
    }
 
    trie* curr = head;
    while (*str){
        // go to the next node
        curr = curr->c_map[*str];
 
        // if the string is invalid (reached end of a path in the Trie)
        if (curr == nullptr) {
            return false;
        }
 
        // move to the next character
        str++;
    }
 
    // return true if the current node is a leaf and the
    // end of the string is reached
    if(curr->isword == true){
        return true;
    }
    else {
        return false;
    }
    
}

void insert(trie*& root, char* str, int A[3]){

    char* m =str;
    if(root == nullptr){
        root = newnode();
    }

    trie* curr = root;

    while(*str){
            // if the charectors doesnot match then create a new node with that charecter.
    if(curr->c_map.find(*str) == curr->c_map.end()){
        curr->c_map[*str] = newnode();
        }

    // go to next next node for both if and else 
    curr = curr->c_map[*str];

    // go to next charecter.
    str = str + 1;                
    }

    //cout<<"first "<<curr->occurence<<endl;
    // cout<<search_bool(root, c)<<endl;
    if((curr->isword == true)&&(curr->occurence >= 1)){
        curr->occurence = curr->occurence + 1;
        for(int i=0; i<3; i++){
            curr->T[i][curr->occurence - 1] = A[i];
        }
        //cout<<"second "<<curr->occurence<<endl;
    }
    else{
        // the curr as leaf after completing the insertion of the given string.
        curr->isword = true;
        //cout<<curr->occurence<<endl;

        //make occurence to one as it is its first occurence!
        curr->occurence = 1;
        for(int i=0; i<3; i++){
            curr->T[i][0] = A[i];
        }
    }        
    
    
}

//finding the given word and its occurence
char* search(trie* head, char* str){    
    char* m =str;
    // return false if Trie is empty
    if(head == nullptr){
        return "word not there!";
    }
 
    trie* curr = head;
    while(*str){
        // go to the next node
        curr = curr->c_map[*str];
 
        // if the string is invalid (reached end of a path in the Trie)
        if(curr == nullptr){
            return "word not there!";
        }
 
        // move to the next character
        str++;
    }
 
    // return true if the current node is a leaf and the
    // end of the string is reached
    if((curr->isword== true)&&(curr->occurence>=1)){
        for(int j=0; j<curr->occurence; j++){
            for(int i=0; i<3; i++){
                std::cout<<curr->T[i][j]<<", ";
            }
            std::cout<<endl;
        }
        
        
        std::cout<<"no of occurences:"<<curr->occurence<<endl;
        return "word there!";
    }
    else {
        return "word not there!";
    }
    
}

// Returns true if the given node has any children
bool havechildren(trie const* curr){

    for (auto it: curr->c_map){
        if(it.second != nullptr){
            return true;
        }
    }
 
    return false;
}
 
// deleting the word from bottom!
bool deletion(trie*& head, char* str){
    if(head == nullptr){
        return false;
    }
 
    trie* curr = head;
    while(*str){
        // go to the next node
        curr = curr->c_map[*str];
 
        // if the string is invalid (reached end of a path in the Trie)
        if(curr == nullptr){
            return false;
        }
 
        // move to the next character
        str++;
    }
 
    //if word is reached end of word
    if(curr->isword == true){

        //if it doesnot have children then simply delete the node.
        if (!havechildren(curr)){
            if(curr->occurence == 1){
                curr->occurence = curr->occurence - 1;
                delete curr;    // delete the current node
                curr = nullptr;

                return true;    
            }
            if(curr->occurence >1){
                curr->occurence = curr->occurence-1;
                return true;
            }
            
        }
 
        // if the current node is a leaf node and has children
        else {
            if(curr->occurence == 1){
                // mark the current node as a non-word but dont delete it
                curr->isword = false;

                return true;   
            }
            if(curr->occurence >1){
                curr->occurence = curr->occurence - 1;
                return true;
            }
            
        }
        
    }

    else{
        return false;
    }   
 
    
    
}



int main(){

    //finding the no of words in the text file.

    ifstream file1; //Declares a file stream object
    string filename;
    string word;
    int count = 0;

    cout << "Enter the file name:  ";
    getline(cin,filename);

    file1.open(filename.c_str());

    while(!file1.eof()){               
        file1 >> word; 
        count++;
    }

    cout << "total no of words in the file: " << count<<endl;
    cout<<endl;
    cout<<endl;
    file1.close();


    // reading the words in the text file into an array!
    ifstream file2(filename);
    
    if(file2.is_open()){

        string A[count];
        trie* root = nullptr;
        int s=0;
        for(int i=0; i<count; i++){
            file2 >> A[i];
            int n = A[i].length();
            char c[n + 1];
            s = s+n;
            int B[3] = {i+1, s-n+1, s };
            
            strcpy(c, A[i].c_str());
            insert(root, c, B);
        }

        //for searching the words given by us!        

        // cout<<"enter the words which you want to search one by one"<<endl;
        // string B[50];        
        // for(int i=0; i<50; i++){
        //     cin>>B[i];
        //     int m = A[i].length();
        //     char d[m + 1];
        //     strcpy(d, B[i].c_str());
        //     cout<<endl;
        //     cout<<search(root, d)<<endl;
        //     cout<<endl;
            
        // }

        //for deleting the words given by us!
        
        for(int i=0; i<10; i++){
            string d_word;
            cout<<"enter the word you want to delete: "<<endl;
            cin>> d_word;
            cout<<endl;
            int n = d_word.length();
            char c[n + 1];
            strcpy(c, d_word.c_str());

            // cout<<deletion(root , d_word)<<endl;
            // cout<<deletion(root , d_word)<<endl;
            // cout<<deletion(root , d_word)<<endl;
            if(deletion(root , c)==1){
                cout<<"deletion successful!"<<endl;
            }
            else{
                cout<<"no deletion took place"<<endl;
            }
            
            std::cout<<search(root, c)<<endl;
            cout<<endl;
            cout<<endl;
        }

        
    }
}