#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <sstream>
#include <cstring>

using namespace std;

struct Record {
  char anime_id [10];
  char name [120];
  char type [10];
  char episodes [5];
  char rating [5];
  char members [10];
};

vector<pair<string, int>> identify_maximum(string filename){
  fstream fio;

  pair<string, int> anime_id_max("0", 0);
  pair<string, int> name_max("0", 0);
  pair<string, int> type_max("0", 0);
  pair<string, int> episodes_max("0", 0);
  pair<string, int> rating_max("0", 0);
  pair<string, int> members_max("0", 0);

  fio.open(filename, ios::in | ios::out | ios::binary);
  string line;
  
  getline(fio, line);
  while(getline(fio, line)){
    string str;
    stringstream ss(line);
    vector<string> vec;

    while(getline(ss, str, ',')){
      vec.push_back(str);
    }
    
    int k = 0;
    int m = 0;

    while(m<vec.size()){
      if (k == 0){
        if(vec[m].size() == 0){
          m++;
          k++;
          continue;
        }

        int temp_val = 0;
        if (vec[m][0] == '\"'){
          temp_val = vec[m].size();
          temp_val++;
          m++;

          while(vec[m][vec[m].size()-1] != '\"'){
            temp_val += vec[m].size();
            temp_val++;
            m++;
          }
          if (vec[m][0] == '\"'){
            temp_val += vec[m].size();
            m++;
          }

          if(temp_val > anime_id_max.second){
            anime_id_max.first = vec[0];
            anime_id_max.second = temp_val;
            k++;
          }
        }
        else{
          if(vec[m].size() > anime_id_max.second){
            anime_id_max.first = vec[0];
            anime_id_max.second = vec[m].size();
          }
          m++;
          k++;
        }
      }
      else if (k == 1){
        if(vec[m].size() == 0){
          m++;
          k++;
          continue;
        }

        int temp_val = 0;
        if (vec[m][0] == '\"'){
          temp_val = vec[m].size();
          temp_val++;
          m++;

          while(vec[m][vec[m].size()-1] != '\"'){
            temp_val += vec[m].size();
            temp_val++;
            m++;
          }
          if (vec[m][vec[m].size()-1] == '\"'){
            temp_val += vec[m].size();
            m++;
          }

          if(temp_val > name_max.second){
            name_max.first = vec[0];
            name_max.second = temp_val;
            k++;
          }
        }
        else{
          if(vec[m].size() > name_max.second){
            name_max.first = vec[0];
            name_max.second = vec[m].size();
          }
          m++;
          k++;
        }
      }
      else if (k == 2){
        if(vec[m].size() == 0){
          m++;
          k++;
          continue;
        }

        int temp_val = 0;
        if (vec[m][0] == '\"'){
          temp_val = vec[m].size();
          temp_val++;
          m++;

          while(vec[m][vec[m].size()-1] != '\"'){
            temp_val += vec[m].size();
            temp_val++;
            m++;
          }
          if (vec[m][0] == '\"'){
            temp_val += vec[m].size();
            m++;
          }

          if(temp_val > type_max.second){
            type_max.first = vec[0];
            type_max.second = temp_val;
            k++;
          }
        }
        else{
          if(vec[m].size() > type_max.second){
            type_max.first = vec[0];
            type_max.second = vec[m].size();
          }
          m++;
          k++;
        }
      } 
      else if (k == 3){
        if(vec[m].size() == 0){
          m++;
          k++;
          continue;
        }

        int temp_val = 0;
        if (vec[m][0] == '\"'){
          temp_val = vec[m].size();
          temp_val++;
          m++;

          while(vec[m][vec[m].size()-1] != '\"'){
            temp_val += vec[m].size();
            temp_val++;
            m++;
          }
          if (vec[m][0] == '\"'){
            temp_val += vec[m].size();
            m++;
          }

          if(temp_val > episodes_max.second){
            episodes_max.first = vec[0];
            episodes_max.second = temp_val;
            k++;
          }
        }
        else{
          if(vec[m].size() > episodes_max.second){
            episodes_max.first = vec[0];
            episodes_max.second = vec[m].size();
          }
          m++;
          k++;
        }
      }
      else if (k == 4){
        if(vec[m].size() == 0){
          m++;
          k++;
          continue;
        }
        
        int temp_val = 0;
        if (vec[m][0] == '\"'){
          temp_val = vec[m].size();
          temp_val++;
          m++;

          while(vec[m][vec[m].size()-1] != '\"'){
            temp_val += vec[m].size();
            temp_val++;
            m++;
          }
          if (vec[m][0] == '\"'){
            temp_val += vec[m].size();
            m++;
          }

          if(temp_val > rating_max.second){
            rating_max.first = vec[0];
            rating_max.second = temp_val;
            k++;
          }
        }
        else{
          if(vec[m].size() > rating_max.second){
            rating_max.first = vec[0];
            rating_max.second = vec[m].size();
          }
          m++;
          k++;
        }        
      }
      else if (k == 5){
        if(vec[m].size() == 0){
          m++;
          k++;
          continue;
        }
        
        int temp_val = 0;
        if (vec[m][0] == '\"'){
          temp_val = vec[m].size();
          temp_val++;
          m++;

          while(vec[m][vec[m].size()-1] != '\"'){
            temp_val += vec[m].size();
            temp_val++;
            m++;
          }
          if (vec[m][0] == '\"'){
            temp_val += vec[m].size();
            m++;
          }

          if(temp_val > members_max.second){
            members_max.first = vec[0];
            members_max.second = temp_val;
            k++;
          }
        }
        else{
          if(vec[m].size() > members_max.second){
            members_max.first = vec[0];
            members_max.second = vec[m].size();
          }
          m++;
          k++;
        }    
      }
    }
  }

  vector<pair<string, int>> result{anime_id_max, name_max, type_max, episodes_max, rating_max, members_max};
  return result;
}

void read_dataset(string filename){
  fstream fio;

  fio.open(filename, ios::in | ios::out | ios::binary);
  string line;
  
  getline(fio, line);
  while(getline(fio, line)){
    string str;
    stringstream ss(line);
    vector<string> vec;

    while(getline(ss, str, ',')){
      vec.push_back(str);
    }
    
    Record record;

    int k = 0;
    int m = 0;

    while(m<vec.size()){
      if (k == 0){
        if(vec[m].size() == 0){
          m++;
          k++;
          continue;
        }

        string temp;
        if (vec[m][0] == '\"'){
          temp = vec[m];
          temp += ",";
          m++;

          while(vec[m][vec[m].size()-1] != '\"'){
            temp += vec[m];
            temp += ",";
            m++;
          }
          if (vec[m][0] == '\"'){
            temp += vec[m];
            m++;
          }

          strcpy(record.anime_id, temp.c_str());
          k++;
        }
        else{
          strcpy(record.anime_id, vec[m].c_str());
          m++;
          k++;
        }
      }
      else if (k == 1){
        if(vec[m].size() == 0){
          m++;
          k++;
          continue;
        }

        string temp;
        if (vec[m][0] == '\"'){
          temp = vec[m];
          temp += ",";
          m++;

          while(vec[m][vec[m].size()-1] != '\"'){
            temp += vec[m];
            temp += ",";
            m++;
          }
          if (vec[m][vec[m].size()-1] == '\"'){
            temp += vec[m];
            m++;
          }

          strcpy(record.name, temp.c_str());
          k++;
        }
        else{
          strcpy(record.name, vec[m].c_str());
          m++;
          k++;
        }
      }
      else if (k == 2){
        if(vec[m].size() == 0){
          m++;
          k++;
          continue;
        }

        string temp;
        if (vec[m][0] == '\"'){
          temp = vec[m];
          temp += ",";
          m++;

          while(vec[m][vec[m].size()-1] != '\"'){
            temp += vec[m];
            temp += ";";
            m++;
          }
          if (vec[m][0] == '\"'){
            temp += vec[m];
            m++;
          }

          strcpy(record.type, temp.c_str());
          k++;
        }
        else{
          strcpy(record.type, vec[m].c_str());
          m++;
          k++;
        }
      } 
      else if (k == 3){
        if(vec[m].size() == 0){
          m++;
          k++;
          continue;
        }

        string temp;
        if (vec[m][0] == '\"'){
          temp = vec[m];
          temp += ",";
          m++;

          while(vec[m][vec[m].size()-1] != '\"'){
            temp += vec[m];
            temp += ",";
            m++;
          }
          if (vec[m][0] == '\"'){
            temp += vec[m];
            m++;
          }

          strcpy(record.episodes, temp.c_str());
          k++;
        }
        else{
          strcpy(record.episodes, vec[m].c_str());
          m++;
          k++;
        }
      }
      else if (k == 4){
        if(vec[m].size() == 0){
          m++;
          k++;
          continue;
        }
        
        string temp;
        if (vec[m][0] == '\"'){
          temp = vec[m];
          temp += ",";
          m++;

          while(vec[m][vec[m].size()-1] != '\"'){
            temp += vec[m];
            temp += ",";
            m++;
          }
          if (vec[m][0] == '\"'){
            temp += vec[m];
            m++;
          }

          strcpy(record.rating, temp.c_str());
          k++;
        }
        else{
          strcpy(record.rating, vec[m].c_str());
          m++;
          k++;
        }        
      }
      else if (k == 5){
        if(vec[m].size() == 0){
          m++;
          k++;
          continue;
        }
        
        string temp;
        if (vec[m][0] == '\"'){
          temp = vec[m];
          temp += ",";
          m++;

          while(vec[m][vec[m].size()-1] != '\"'){
            temp += vec[m];
            temp += ",";
            m++;
          }
          if (vec[m][0] == '\"'){
            temp += vec[m];
            temp += ",";
            m++;
          }

          strcpy(record.members, temp.c_str());
          k++;
        }
        else{
          strcpy(record.members, vec[m].c_str());
          m++;
          k++;
        }    
      }
    }
  /*
  cout << record.anime_id<< "|";
  cout << record.name<< "|";
  cout << record.type<< "|";
  cout << record.episodes<< "|";
  cout << record.rating<< "|";
  cout << record.members<< "|";
  cout << endl;
  */
  }
}

int main(){
  vector<pair<string, int>> vec = identify_maximum("animedata2.csv");
  cout<<"anime_id_max: "<<"("<<vec[0].first<<", "<<vec[0].second<<")"<<endl;
  cout<<"name_max: "<<"("<<vec[1].first<<", "<<vec[1].second<<")"<<endl;
  cout<<"type_max: "<<"("<<vec[2].first<<", "<<vec[2].second<<")"<<endl;
  cout<<"episodes_max: "<<"("<<vec[3].first<<", "<<vec[3].second<<")"<<endl;
  cout<<"rating_max: "<<"("<<vec[4].first<<", "<<vec[4].second<<")"<<endl;
  cout<<"members_max: "<<"("<<vec[5].first<<", "<<vec[5].second<<")"<<endl;
  cout<<endl;

  read_dataset("animedata2.csv");
}
