#include <string>
#include <iostream>
#include <fstream> // ifstream
#include <sstream> // stringstream

template<typename T>
void read_data(T* result, int size, std::string filepath) {
    std::ifstream file_handle(filepath.c_str());
    std::string line;
    int curr_count = 0;
    if (file_handle.is_open()) {
        while(getline(file_handle, line)) {
            std::stringstream ss(line);
            while(getline(ss, line, ' ')) { // split line content
                // T number = std::stof(line);
                if (std::is_same<int, T>::value) {
                    result[curr_count++] = std::stoi(line);
                }
                else {
                    result[curr_count++] = std::stof(line);
                }
            }
        }
        file_handle.close();
        assert(size == curr_count);
    }
    else {
        std::cout << "file:" << filepath << " can't open normally!\n";
    } 
}

void read_data_int8(uint8_t* result, int size, std::string filepath) {
    std::ifstream file_handle(filepath.c_str());
    std::string line;
    int curr_count = 0;
    if (file_handle.is_open()) {
        while(getline(file_handle, line)) {
            std::stringstream ss(line);
            while(getline(ss, line, ' ')) { // split line content
                result[curr_count++] = (uint8_t) std::stoi(line);
            }
        }
        file_handle.close();
        assert(size == curr_count);
    }
    else {
        std::cout << "file:" << filepath << " can't open normally!\n";
    } 
}

template <typename T>
void write_data_binary(T* data_ptr, int size, std::string dst_file) {
    const char* ptr = reinterpret_cast<const char*>(data_ptr);
    std::ofstream ofs(dst_file, std::ios::binary|std::ios::out);
    ofs.write(ptr, sizeof(T) * size);
    ofs.close();
}

template <typename T>
void read_data_binary(T* data_ptr, int size, std::string src_file) {
    std::ifstream ifs(src_file, std::ios::binary | std::ios::in);
    if (ifs.is_open()) {
        ifs.seekg (0, ifs.end);
        int length = ifs.tellg();
        std::cout << src_file << " byte length: " << length << ", reset offset: " << length - sizeof(T) * size << std::endl;
        ifs.seekg(length - sizeof(T) * size, ifs.beg);
        
        ifs.read((char*)data_ptr, sizeof(T) * size);
        ifs.close();
    }
    else {
        std::cout << "file:" << src_file << " can't open normally!\n";
    } 
}

int main(int argc, const char* argv[])  {
    if (argc < 2) {
        std::cout << "========================================================================\n";
        std::cout << "Arguments: codes file path, codebooks file path\n";
        std::cout << "========================================================================\n";
        return -1;
    }

    std::string codes_file_path = argv[1];
    std::string codebooks_file_path = argv[2];
    std::string dst_code_file_path = codes_file_path + ".bin";
    std::string dst_codebooks_file_path = codebooks_file_path + ".bin";


    std::cout << "codes_file_path: " << codes_file_path << "\ncodebooks_file_path: " << codebooks_file_path << std::endl;
    std::cout << "dst_code_file_path: " << dst_code_file_path << "\ndst_codebooks_file_path: " << dst_codebooks_file_path << std::endl;


    int codebooks_size = 256 * 8;
    int codes_size = 1000002 * 8;
    float* codebooks = new float[codebooks_size];
    uint8_t* codes_int8 = new uint8_t[codes_size];

    read_data<float>(codebooks, codebooks_size, codebooks_file_path);
    read_data_int8(codes_int8, codes_size, codes_file_path);

    write_data_binary<float>(codebooks, codebooks_size, dst_codebooks_file_path);
    write_data_binary<uint8_t>(codes_int8, codes_size, dst_code_file_path);

    delete[] codebooks;
    delete[] codes_int8;

    return 0;
}