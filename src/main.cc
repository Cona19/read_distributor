#include <iostream>
#include <sstream>
#include <fstream>

#define CFG_NUM_THREAD 24

int main(int argc, char *argv[]){
    if (argc != 4){
        std::cout << "Usage : " << argv[0] << " file1 file2 output_dir"
            << std::endl;
    }
    std::ifstream in(argv[1]);
    std::ofstream out[CFG_NUM_THREAD];
    unsigned long long cnt = 0;
    int turn = 0;
    std::string id, seq, separator, accuracy;

    for (int i = 0; i < CFG_NUM_THREAD; i++){
        std::ostringstream oss;
        oss << argv[3] << i << ".fastq";
        std::cout << oss.str() << std::endl;
        out[i].open(oss.str(), std::ofstream::out);
    }

    while(std::getline(in, id) && std::getline(in, seq) && 
            std::getline(in, separator) && std::getline(in, accuracy)){
        out[turn] << id << std::endl << seq << std::endl <<
            separator << std::endl << accuracy << std::endl;
        turn = (turn+1) % CFG_NUM_THREAD;
        cnt++;
        if (cnt % 10000000 == 0){
            std::cout << ".";
        }
    }
    in.close();
    in.open(argv[2]);
    while(std::getline(in, id) && std::getline(in, seq) && 
            std::getline(in, separator) && std::getline(in, accuracy)){
        out[turn] << id << std::endl << seq << std::endl <<
            separator << std::endl << accuracy << std::endl;
        turn = (turn+1) % CFG_NUM_THREAD;
        cnt++;
        if (cnt % 10000000 == 0){
            std::cout << ".";
        }
    }
    in.close();

    return 0;
}
