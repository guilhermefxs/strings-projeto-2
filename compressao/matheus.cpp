#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;
 
bool sortSec(pair<int, string> &a, pair<int, string> &b){
    return a.second< b.second;
}

bool startsWith(string a, string b){
    // Convert mainStr to lower case
    for_each(a.begin(), a.end(), [](char & a){
        a = tolower(a);
    });

    for_each(b.begin(), b.end(), [](char & b){
        b = tolower(b);
    });
    //transform(a.begin(), a.end(), a.begin(), tolower);
    // Convert toMatch to lower case
    //transform(b.begin(), b.end(), b.begin(), tolower);
    if(a.find(b) == 0)
        return true;
    else
        return false;
}
 
int getSuffix(string s, string pattern){
    vector< pair<int,string> > answer;
    pair<int, string> send;
    int count=0;
    for(int i=0; i<s.length(); i++){
        string concat="";
        for(int k = i; k<s.length(); k++){
            concat+=s[k];
        }
        send.first=count;
        send.second=concat;
        answer.push_back(send);
        count++;
    }
    sort(answer.begin(), answer.end(), sortSec);
    
    int lo = 0;
    int hi = answer.size()-1;
    int saveMin=-1;
    int countAnswer =0;
    while(lo<=hi){
        int mid = (lo+hi)/2;
        if(startsWith(answer[mid].second, pattern)){
            if(saveMin==-1) saveMin=mid;
            else if(mid<saveMin) saveMin=mid;
            cout<<"entrei save min "<<saveMin<<endl;
            hi = mid-1;
        }       
        else if(answer[mid].second>pattern){
            hi = mid-1;
            mid = (lo+hi)/2;
        }
        else if(answer[mid].second<pattern){
            lo = mid+1; 
            mid = (lo+hi)/2;
        }
    }

    int secLo =0;
    int secHi = answer.size()-1;
    int saveMax=-1;
    while(secLo<=secHi){
        int mid = (secLo+secHi)/2;
        if(mid==secLo) mid= secHi;
        if(startsWith(answer[mid].second, pattern)){
            cout<<"mid nesse"<<mid<<endl;
            if(saveMax==-1) saveMax=mid;
            else if(mid>saveMax) saveMax=mid;
            cout<<"teste "<<saveMax<<endl;
            secLo = mid+1;
        }       
        else if(answer[mid].second>pattern){
            secHi = mid-1;
            mid = (secHi+secLo)/2;
            if(mid==secLo) mid = secHi;
            cout<<"mid "<<mid<<endl;
        }
        else if(answer[mid].second<pattern){
            secLo = mid+1; 
            mid = (secLo+secHi)/2;
        }
    }
    cout<<"saveMIn "<<saveMin<<endl;
    cout<<saveMin<<endl;
    cout<<saveMax<<endl;
    
    if(saveMax==-1 && saveMin>=0) return 1;
    if(saveMax == -1 && saveMin==-1) return 0;
    return (saveMax-saveMin)+1;
}

 
 
int main(){
    string s, pattern;
    cin>> s >> pattern;
    ifstream infile("arqui.txt", ifstream::in);
    string line;
    while (getline(infile, line))
    {   
        int answer;
        answer= getSuffix(line, pattern);  
        cout<< answer<<endl;
    }
}    