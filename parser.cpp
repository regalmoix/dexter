#include<bits/stdc++.h>
using namespace std;
int main()
{
    // string item_name;
    // ifstream nameFileout;
    // nameFileout.open("perftsuite.txt");
    // string temp;
    // vector<string> lines;
    // while(std::getline(nameFileout, temp))
    // {
    //     lines.push_back(temp);
    //     // TODO: assign item_name based on line (or if the entire line is 
    //     // the item name, replace line with item_name in the code above)
    // }

    // vector<int> depths;

    // for(int i = 0; i < lines.size(); i++){
    //     bool flag = false;
    //     string word = "";
    //     string fin = "";
    //     for(auto x : lines[i]){
    //         if(x!=''&&flag){
    //             int val = (lines[i][j]-'0')*10 + (lines[i][j+1]-'0')
    //         }
    //         if(word ==";D1"){
    //             flag = true;
    //         }
    //     }
    // }// vector<string> fens;

    // string item_name;
    // ifstream nameFileout;
    // nameFileout.open("perftsuite.txt");
    // string temp;
    // vector<string> lines;
    // while(std::getline(nameFileout, temp))
    // {
    //     lines.push_back(temp);
    //     // TODO: assign item_name based on line (or if the entire line is 
    //     // the item name, replace line with item_name in the code above)
    // }

    // for(int i = 0; i < lines.size();i++){
    //     string word = "";
    //     for(auto x : lines[i]){
    //         if(x==';'){
    //             fens.push_back(word);
    //             word = "";
    //             break;
    //         }
    //         else{
    //             word+=x;
    //         }
    //     }
    // }

    // vector<int> myDepths;

    // for(int i = 0; i < fens.size(); i++){
    //     Board b(fens[i]);
    //     HASH.GenerateHash(b);
    //     int x = PerftTest(1, b);
    //     myDepths.push_back(x);
    // }
    

    // fstream file; 
    // string word, t, q, filename; 
  
    // // filename of the file 
    // filename = "perftsuite.txt"; 
  
    // // opening file 
    // file.open(filename.c_str()); 
  
    // // extracting words from the file 
    // vector<int> depths;
    // bool flag = false;
    // while (file >> word) 
    // { 
    //     if(flag){
    //         int val = stoi(word);
    //         depths.push_back(val);
    //         flag = false;
    //     }
    //     if(word==";D1"){
    //         flag = true;
    //     }
        
    // } 


    // cout<<"\n\n";
    // for(int i = 0; i < myDepths.size(); i++){
    //     if(myDepths[i]!=depths[i]){
    //         cout<<i+1<<"\n";
    //     }
    // }

    fstream file; 
    string word, t, q, filename; 
  
    // filename of the file 
    filename = "perftsuite.txt"; 
  
    // opening file 
    file.open(filename.c_str()); 
  
    // extracting words from the file 
    vector<int> depths;
    bool flag = false;
    while (file >> word) 
    { 
        if(flag){
            int val = stoi(word);
            depths.push_back(val);
            flag = false;
        }
        if(word==";D1"){
            flag = true;
        }
        
    } 
  
    for(int i = 0; i < depths.size(); i++){
        cout<<depths[i]<<"\n";
    }
    return 0; 
}