#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "picojson.h"
#include <fstream>
#include <map>
#include <vector>


using namespace picojson;

class Map {
    std::string Id;
    std::string Lane;
    std::vector<double> g1;
    std::vector<double> L_bound_data;
    std::vector<double> R_bound_data;
    Map(std::vector<double> v, std::string id, std::string lane, std::vector<double> l_bound_data, std::vector<double> r_bound_data) // or using initializer list: a() : i(0) {}
    {
        g1 = v;
        Id= id;
        Lane = lane;
        L_bound_data = l_bound_data;
        R_bound_data = r_bound_data;


    }
    void data(){

    std::cout << "Output of begin and end: "<<" ";
    std::cout<<Id<<std::endl;
    std::cout<<Lane<<std::endl;
    for (auto i = L_bound_data.begin(); i != L_bound_data.end(); ++i)
        std::cout << *i << std::endl;
    }
};



struct Lane{
 int id;
 std::vector<std::vector<double>> center_point;
};

int main()
{

    std::ifstream f("map.json");
    std::string json;

     std::string ostringstream;
     if(f) {

      std::ostringstream ss;
       ss << f.rdbuf(); // reading data
       json = ss.str();
    }

     picojson::value v;
     std::string err, id, lane;
     picojson::array arr;
     picojson::parse(v, json.c_str(), json.c_str() + strlen(json.c_str()), &err);

     if (! err.empty()) {

    std::cerr << err <<"Heavy Error" << std::endl;

     }

      id = v.get("ID").get<std::string>();
      lane = v.get("Lane").get<std::string>();


      std::vector<double> l_temp_array;
      auto left_result = v.get("LeftBound").get<array>();
        for(int i=0; i<=1; i++){
            l_temp_array.push_back(left_result[i].get<double>());
        }

        std::vector<double> r_temp_array;
        auto right_result = v.get("RightBound").get<array>();
        for(int i=0; i<=1; i++){
            r_temp_array.push_back(left_result[i].get<double>());
        }


      auto array_result = v.get("Points").get<array>();
      std::vector<std::vector<double>> points;
      std::vector<double> tmp_array;
        for (int i=0; i<=40; i++){
                tmp_array.push_back(array_result[i].get<array>()[0].get<double>());
                tmp_array.push_back(array_result[i].get<array>()[1].get<double>());
                points.push_back(tmp_array);
        }


      Map m(tmp_array, id, lane, l_temp_array, r_temp_array);
      m.data();





    return 0;

    }













/*
    vector<int> vec;
    for (int i = 1; i <= 5; i++)
        vec.push_back(i);
    Geeks g(vec);
    g.data();


    cout << "Size : " << g1.size();
    cout << "\nCapacity : " << g1.capacity();
    cout << "\nMax_Size : " << g1.max_size();
    g1.resize(20);


    // Assign vector
    vector<int> v;

    // fill the array with 10 five times
    v.assign(10, 30);
    // inserts 5 at the beginning
    v.insert(v.begin(), 5);

    cout << "The vector elements are: ";
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
*/



    //std::cout<<"the value is "<<points[0]<<std::endl;


          //for(int i=0; i<=102; i++){
            //  vec.push_back(array_result)
                //std::cout<<array_result[i]<<std::endl;
          // }



