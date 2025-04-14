#include <iostream>
#include <fstream>
#include <math.h>
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

const int duration = 2;
const int max_amp = 32760;
const double freq = 350;

void write_as_bytes(ofstream &file, int value, int byte_size){
    file.write(reinterpret_cast<const char*>(&value), byte_size);
}
int main()
{

    ofstream wavFile;
    wavFile.open("test.wav", ios::binary);

    if(wavFile.is_open()){

        //riff
        wavFile << chunk_id;
        wavFile << chunk_size;
        wavFile << chunk_format;

        //for the fmt
        wavFile << subchunk1_id;
        write_as_bytes(wavFile, subchunk1_size, 4);//turnign them into bytes to be written and read
        write_as_bytes(wavFile, audio_format, 2);
        write_as_bytes(wavFile, sampRate, 4);
        write_as_bytes(wavFile, byteRate, 4);
        write_as_bytes(wavFile, blockAlign, 2);
        write_as_bytes(wavFile, bits_per_sample, 2);

        //"data " sub chunk
       wavFile << subchunk2_id;
       wavFile << subchunk2_size;

       int start_audio = wavFile.tellp();

       for(int i=0; i <sampRate * duration; i++){
            double amp = (double)i / sampRate * max_amp;
            double value = sin((2 * 3.14 * i * freq) / sampRate);

            double channel1 = amp * value / 2;
            double channel2 = (max_amp - amp) * value;

        write_as_bytes(wavFile, channel1, 2);
        write_as_bytes(wavFile, channel2, 2); 
       }

       int end_audio = wavFile.tellp();
       wavFile.seekp(start_audio - 4);
        write_as_bytes(wavFile, end_audio - start_audio, 4);

        wavFile.seekp(4, ios::beg); //beginning (beg) seeking 4 places after
        write_as_bytes(wavFile, end_audio - 8, 4);
    }
    wavFile.close();

    return 0;
}