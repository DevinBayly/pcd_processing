#include "pts_reader.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <filesystem>
#include <string_view>
#include <algorithm>
using namespace std;
struct PT
{
    float x;
    float y;
    float z;
};
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
void run_converter(string pth) {
    // string name = "/home/dash/Documents/output_pcd/258.517830990.pcd";
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