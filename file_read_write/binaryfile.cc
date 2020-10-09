#include <string>
#include <iostream>
#include <fstream> // ifstream
#include <sstream> // stringstream
#include <chrono>
#include <vector>

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
        ifs.read((char*)data_ptr, sizeof(T) * size);
        ifs.close();
    }
    else {
        std::cout << "file:" << src_file << " can't open normally!\n";
    } 
}


double average(std::vector<double>& arr) {
    double result = 0;
    for (int i=0; i<arr.size(); i++) result+= arr[i];
    return result/arr.size();
}



int main(int argc, const char* argv[])  {
    if (argc < 4) {
        std::cout << "========================================================================\n";
        std::cout << "Arguments: file_path, dump_type, dtype, loop_count\n";
        std::cout << "========================================================================\n";
        return -1;
    }

    std::string file_path = argv[1];
    std::string dump_type = argv[2];
    std::string dtype = argv[3];
    int loop_count = std::atoi(argv[4]);

    int size = 0;

    int codebooks_size = 256 * 8;
    int codes_size = 1000002 * 8;
    float* codebooks = new float[codebooks_size];
    int* codes = new int[codes_size];
    uint8_t* codes_int8 = new uint8_t[codes_size];
    // std::string codebooks_path = "/Users/chenxiaotao03/dataset/din/din_codebook.txt";
    // std::string codes_path = "/Users/chenxiaotao03/dataset/din/din_dict.codes";
    // read_data<float>(codebooks, codebooks_size, codebooks_path);
    // read_data<int>(codes, codes_size, codes_path);
    // read_data_int8(codes_int8, codes_size, codes_path);


    // write_data_binary<float>(codebooks, codebooks_size, "/Users/chenxiaotao03/dataset/din/din_codebook.bin");
    // write_data_binary<int>(codes, codes_size, "/Users/chenxiaotao03/dataset/din/din_codes_int32.bin");
    // write_data_binary<uint8_t>(codes_int8, codes_size, "/Users/chenxiaotao03/dataset/din/din_codes_int8.bin");
    // return 0;
    assert(dtype == "float" || dtype == "int" || dtype == "int8");
    assert(dump_type == "binary" || dump_type == "string");


    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);


    std::vector<double> times;

    if (dump_type == "binary") {
        if (dtype == "float") {
            size = 256 * 8;
            for (int i=0; i<loop_count; i++) {
                start = std::chrono::system_clock::now();
                read_data_binary<float>(codebooks, size, file_path);
                end = std::chrono::system_clock::now();
                duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                double tmp_time = double(duration.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den;
                times.push_back(tmp_time);
            }
            
        }
        else if (dtype == "int") {
            size = 1000002 * 8;
            for (int i=0; i<loop_count; i++) {
                start = std::chrono::system_clock::now();
                read_data_binary<int>(codes, size, file_path);
                end = std::chrono::system_clock::now();
                duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                double tmp_time = double(duration.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den;
                times.push_back(tmp_time);
            }
        }
        else if (dtype == "int8") {
            size = 1000002 * 8;
            for (int i=0; i<loop_count; i++) {
                start = std::chrono::system_clock::now();
                read_data_binary<uint8_t>(codes_int8, size, file_path);
                end = std::chrono::system_clock::now();
                duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                double tmp_time = double(duration.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den;
                times.push_back(tmp_time);
            }
        }
        else {
            std::cout << "don't support dump type: " << dump_type << ", dtype: " << dtype << std::endl;
        }
    }
    else if (dump_type == "string") {
        if (dtype == "float") {
            size = 256 * 8;
            for (int i=0; i<loop_count; i++) {
                start = std::chrono::system_clock::now();
                read_data<float>(codebooks, size, file_path);
                end = std::chrono::system_clock::now();
                duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                double tmp_time = double(duration.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den;
                times.push_back(tmp_time);
            }
        }
        else if (dtype == "int") {
            size = 1000002 * 8;
            for (int i=0; i<loop_count; i++) {
                start = std::chrono::system_clock::now();
                read_data<int>(codes, size, file_path);
                end = std::chrono::system_clock::now();
                duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                double tmp_time = double(duration.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den;
                times.push_back(tmp_time);
            }
        }
        else if (dtype == "int8") {
            size = 1000002 * 8;
            for (int i=0; i<loop_count; i++) {
                start = std::chrono::system_clock::now();
                read_data_int8(codes_int8, size, file_path);
                end = std::chrono::system_clock::now();
                duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                double tmp_time = double(duration.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den;
                times.push_back(tmp_time);
            }
        }
        else {
            std::cout << "don't support dump type: " << dump_type << ", dtype: " << dtype << std::endl;
        }
    }

    std::cout << "read " << file_path << " target size: " << size << " dump type: " << dump_type << " loop count: " << loop_count << " take " << average(times) << "s" << std::endl;


    delete[] codebooks;
    delete[] codes;
    delete[] codes_int8;

    return 0;
}