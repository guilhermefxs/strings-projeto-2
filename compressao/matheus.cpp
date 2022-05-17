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
 
ofstream out("output.idx");

void getSuffix(string s){
    vector< pair<int,string> > answer;
    int countLetter[256] = {0}; 
    pair<int, string> send;
    int count=0; 
    for(int i=0; i<s.length(); i++){
        string concat="";
        countLetter[s[i]]++;
        for(int k = i; k<s.length(); k++){
            concat+=s[k];
        }
        send.first=count;
        send.second=concat;
        answer.push_back(send);
        count++;
    }
    sort(answer.begin(), answer.end(), sortSec);
    for(int i=0; i<answer.size(); i++){
        out<< answer[i].first;
        out<<" ";
    }
    out<<"\n";
    for(int i=0; i<256; i++){
        out<<countLetter[i];
        out<<" ";
    }
    out<<"\n";
}



void fix(vector<int> &first, vector<int> &countLetter){
    int currentPos =0;
    vector<pair < int, string> > answer(first.size());
    string concat(first.size(), 'a');
    for(int i=0; i<countLetter.size(); i++){
        for(int j=0; j<countLetter[i]; j++){
            concat[first[currentPos]]=(char) i;
            currentPos++;
        }
    }
    for(int i=0; i<first.size(); i++){
        answer[i].first = first[i];
        answer[i].second = concat.substr(i);
    }
}


vector<int> searchPattern(string pattern, vector< int, string> &suffixArray){
    int lo = 0;
    int hi = suffixArray.size()-1;
    int saveMin=-1;
    int countAnswer =0;
    while(lo<=hi){
        int mid = (lo+hi)/2;
        if(startsWith(suffixArray[mid].second, pattern)){
            if(saveMin==-1) saveMin=mid;
            else if(mid<saveMin) saveMin=mid;
            //cout<<"entrei save min "<<saveMin<<endl;
            hi = mid-1;
        }       
        else if(suffixArray[mid].second>pattern){
            hi = mid-1;
            mid = (lo+hi)/2;
        }
        else if(suffixArray[mid].second<pattern){
            lo = mid+1; 
            mid = (lo+hi)/2;
        }
    }

    int secLo =0;
    int secHi = suffixArray.size()-1;
    int saveMax=-1;
    while(secLo<=secHi){
        int mid = (secLo+secHi)/2;
        if(mid==secLo) mid= secHi;
        if(startsWith(suffixArray[mid].second, pattern)){
           // cout<<"mid nesse"<<mid<<endl;
            if(saveMax==-1) saveMax=mid;
            else if(mid>saveMax) saveMax=mid;
            //cout<<"teste "<<saveMax<<endl;
            secLo = mid+1;
        }       
        else if(suffixArray[mid].second>pattern){
            secHi = mid-1;
            mid = (secHi+secLo)/2;
            if(mid==secLo) mid = secHi;
           // cout<<"mid "<<mid<<endl;
        }
        else if(suffixArray[mid].second<pattern){
            secLo = mid+1; 
            mid = (secLo+secHi)/2;
        }
    }
    
    if(saveMax==-1 && saveMin>=0)  return vector<int> (1, suffixArray[saveMin].first);
    if(saveMax == -1 && saveMin==-1) return vector<int> ();
    vector<int> answer;
    for(int i=saveMin; i<=saveMax; i++){
        answer.push_back(suffixArray[i].first);
    }
    return answer;
}
 
int main(){
   /* string s, pattern;
    cin>> s >> pattern;
    int answer;
    answer= getSuffix(s, pattern);
    cout<< answer<<endl;
    */

    string pattern;
    cin>> pattern;
    ifstream infile("in.txt", ifstream::in);
    string line;
    long long count=0;
    while (getline(infile, line))
    {   
        //int answer;
        getSuffix(line);  
        //count+=answer;
    }
   // cout<<"O padrão "<< "*"<< pattern<< "*"<<" aparece "<<count<<" vezes no texto."<<endl;
    out.close();
    
    ifstream outfile("output.idx");
    while(getline(outfile, line)){  
        vector<int> suffixArray;
        vector<int> count;
        stringstream extract(line);
        string extracted;
        while( extract >> extracted){
            suffixArray.push_back(stoi(extracted));
        }
        getline(outfile, line);
        extract= stringstream(line);
        while(extract >> extracted){
            count.push_back(stoi(extracted));
        }
        fix(suffixArray, count);
    }

}    