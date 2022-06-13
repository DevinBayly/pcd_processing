#include "pts_reader.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <filesystem>
#include <ranges>
#include <string_view>
#include <algorithm>
using namespace std;
struct PT
{
    float x;
    float y;
    float z;
};
void read_xyz()
{
    string name = "suzanne_pts.xyz";
    uintmax_t size = filesystem::file_size(name);
    ifstream ifile(name);
    string buf(size, '\0');
    ifile.read(buf.data(), size);
    auto floats =
        buf | views::split(' ');
    vector<float> coords;
    for (auto i: floats) {
        string flt{};
        for (auto ptr = i.begin(); ptr != i.end();ptr++) {
            if (*ptr =='\n') {
                continue;
            }
            flt +=*ptr;
        }
        if( flt != "") {
        coords.push_back(stof(flt));
        }
    }
    // make a new ptr and reinterpret cast the coords data to a pointer of PT structs
    PT * pts_ptr = reinterpret_cast<PT * >(coords.data());
    // attempt to print out data from the first element
    PT pt = pts_ptr[0];
    cout << pt.x << ' ' << pt.y << ' ' << pt.z << endl;

    ofstream ofile("suz.binary");
    ofile.write(reinterpret_cast<char *>(coords.data()),coords.size()*sizeof(float));
    ofile.close();

}
void yaml_reader() {
    string name = "topic1.yaml";
    uintmax_t size = filesystem::file_size(name);
    ifstream ifile(name);
    string buf(size, '\0');
    ifile.read(buf.data(), size);
    size_t ind = buf.find(']');
    cout << buf.size() << endl;
    for(int i = 0; i < ind ; i++) {
    cout << buf[i];
    }
    cout << endl;

}
struct pcdPt{
    float x;
    float y;
    float z;
    char buffer[36];
};
PT makePTCopy(pcdPt * ptr) {
    PT _pt {
        ptr->x,
        ptr->y,
        ptr->z
    };
    return _pt;
}
void process_file(string name,ofstream & ofile) {
    vector<PT> pts{};
    ifstream ifile(name);
    for(int i = 0 ; i <11 ; i++){
        string line{};
        getline(ifile,line);
    }
    // no*w we are into the binary data
    for (size_t i = 0; i < 262144; i++) {
        char buf[48];
        ifile.read(buf,48);
        pcdPt * singlePoint = reinterpret_cast<pcdPt *>(&buf);
        pts.push_back(makePTCopy(singlePoint));
    }
    cout << "fin " << name << endl;
    ofile.write(reinterpret_cast<char *>(pts.data()),pts.size()*sizeof(PT));
    ifile.close();
}
void run_converter() {
    // string name = "/home/dash/Documents/output_pcd/258.517830990.pcd";
    string pth = "/home/bigo/Downloads/output_pcd/";
    vector<string> names{};
    for (auto & name : filesystem::directory_iterator(pth)){
        cout << name.path() << endl;
        names.push_back(name.path());
    }
    //sort the names so that the data will be in right order
    sort(names.begin(),names.end());
    ofstream ofile(pth + "all_scans.bin",ios::binary);
    for (auto const name: names) {
        process_file(name,ofile);
    }
    ofile.close();

}