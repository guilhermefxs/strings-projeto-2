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

void getSuffix(string s, ofstream &out){
    vector< pair<int,string> > answer;
    int countLetter[256] = {0}; 
    pair<int, string> send;
    int count=0; 
    for(long unsigned int i=0; i<s.length(); i++){
        string concat="";
        countLetter[s[i]]++;
        for(long unsigned int k = i; k<s.length(); k++){
            concat+=s[k];
        }
        send.first=count;
        send.second=concat;
        answer.push_back(send);
        count++;
    }
    sort(answer.begin(), answer.end(), sortSec);
    for(long unsigned int i=0; i<answer.size(); i++){
        out<< answer[i].first;
        if(i!=answer.size()-1) out<<" ";   
    }
    out<<"\n";
    for(int i=0; i<256; i++){
        out<<countLetter[i];
        if(i!=255)out<<" ";
    }
    out<<"\n";

}



vector<pair <int, string> > fix(vector<int> &first, vector<int> &countLetter){
    int currentPos =0;
    vector<pair < int, string> > answer(first.size());
    string concat(first.size(), 'a');
    for(long unsigned int i=0; i<countLetter.size(); i++){
        for(int j=0; j<countLetter[i]; j++){
            concat[first[currentPos]]=(char) i;
            currentPos++;
        }
    }
    for(long unsigned int i=0; i<first.size(); i++){
        answer[i].first = first[i];
        answer[i].second = concat.substr(i);
    }
    sort(answer.begin(), answer.end(), sortSec);

    return answer;
}


vector<int> searchPattern(string pattern, vector< pair< int, string > > &suffixArray){
    int lo = 0;
    int hi = suffixArray.size()-1;
    int saveMin=-1;
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

void createSufix (std::string fileToCreateSufix){
    ifstream infile(fileToCreateSufix, ifstream::in);
    string line;
    std::string::size_type const p(fileToCreateSufix.find_last_of('.'));
    std::string file_without_extension = fileToCreateSufix.substr(0, p);
    ofstream out(file_without_extension+".idx");
    while (getline(infile, line))
    {   
        getSuffix(line, out);  
    }
}

void findPattern (std::string sufixFile, std::vector<char*> pattern, bool showOnlyCountOfPatterns){
    string line;
    ifstream outfile(sufixFile);
    int numberOfPatterns = 0;
    int numberOfLinesWithPatterns = 0;
    while(getline(outfile, line)){  
        bool hasThePattern = false;
        vector<int> suffixArray;
        vector<int> count;
        vector< pair< int, string > > fixed;
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
        
        fixed = fix(suffixArray, count);

        for(long unsigned int i=0; i<pattern.size(); i++){
            vector<int> answer;
            answer= searchPattern(pattern[i], fixed);
            if(answer.size() > 0){
                hasThePattern = true;
                numberOfPatterns += answer.size();
            }
        }
        if(hasThePattern && !showOnlyCountOfPatterns){
            auto it = std::max_element(fixed.begin(), fixed.end(),
                               [](const auto& a, const auto& b) {
                                   return a.second.size() < b.second.size();
                               });
            pair< int, string > line = *it;
            cout << line.second << endl;
            numberOfLinesWithPatterns++;
        }
    }
    cout << "Number of occ of the patterns: " << numberOfPatterns << endl;
    cout << "Number of lines with the patterns: " << numberOfLinesWithPatterns << endl;
}