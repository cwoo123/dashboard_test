#include<string>
#include<vector>
#include<iostream>

using namespace std;

int main(){

vector<string>  ch_ID, replic;
string arr[8] = {"a", "b", "b", "c","c","c","d", "a" };
int ch_count = 0;
string name;

for(int i = 0; i<8 ; i++){
  ch_ID.push_back(arr[i]);
}

cout<<"HI"<<endl;

for(int i = 0;i<ch_ID.size();i++){
  replic.push_back(ch_ID.at(i));
  name = ch_ID.at(i);
  if( count(replic.begin(), replic.end(), name) > 1 )
    continue;
  ch_count = count(ch_ID.begin(), ch_ID.end(), name);
  cout<<ch_count<<endl;

  }
}
