#include <iostream>
#include <fstream>
using namespace std;

//Riff chnk
const string chunk_id = "RIFF";
const string chunk_size = "----"; // four dahses because it takes 4 bytes maximum
const string chunk_format = "WAVE"; //file type header

//sub chunk
const string subchunk1_id = "fmt";
const int subchunk1_size = 16; //also takes maximum 16 bytes
const int audio_format = 1; // pcm is equals to 1
const int numChannels = 2; // 1 = mono, 2 = stereo
const int sampRate = 44100;
const int byteRate = sampRate * numChannels * (subchunk1_size/8);
const int blockAlign = numChannels * (subchunk1_size/8);
const int bits_per_sample = 16;

//"data" sub chunk : The "data" subchunk contains the size of the data and the actual sound

const string subchunk2_id = "data";
const string subchunk2_size =  "----"; 

void write_as_bytes(ofstream &file, int value, int byte_size){
    file.write(reinterpret_cast<const char*>(&value), byte_size);
}




int main()
{

    ofstream wavFile;
    wavFile.open("test.wav", ios::binary);

    return 0;
}