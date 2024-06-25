#include <iostream>
#include <fstream>
#include <string.h>
#include <limits>
#include <memory>
#include <vector>


bool user_input_double(double& value, std::istream& inp_stream, int line_num) {
    bool state = true;
    inp_stream >> value;

    if (state && inp_stream.eof()) {
        std::cerr << "\x1B[31m" << "ERR: unexpected EOF. "
            << "Check line " << line_num << '.' << "\033[0m" << std::endl;
        state = false;
    }

    if (state && inp_stream.fail()) {
        std::cerr << "\x1B[31m" << "ERR: wrong value type. "
            << "Check line " << line_num << '.' << "\033[0m" << std::endl;
        state = false;
    }

    return state;
}

bool user_input_int(int& value, std::istream& inp_stream, int line_num) {
    bool state = true;
    double value_dbl = 0;
    if (!user_input_double(value_dbl, inp_stream, line_num)) {
        state = false;
    }

    value = value_dbl;
    if (state && std::abs(value_dbl - value) > 2 * std::numeric_limits<double>::epsilon()) {
        std::cerr << "\x1B[31m" << "ERR: wrong value type. "
            << "Check line " << line_num << '.' << "\033[0m" << std::endl;
        state = false;
    }

    return state;
}

class ICmd {
public:
    ICmd() = default;
    virtual ~ICmd() = default;
    ICmd(double n_operand) : operand{ n_operand } {}

    virtual double Out(double data) = 0;

protected:
    double operand = 0;
};

class ICmd_add : public ICmd {
public:
    ICmd_add(double n_operand) : ICmd(n_operand) {};
    virtual double Out(double data) final {
        return data + operand;
    };

    static bool TryInit(std::unique_ptr<ICmd>& ptr, std::string& command, double value) {
        bool state = false;
        if (command == "ADD") {
            ptr.reset(new ICmd_add(value));
            state = true;
        }
        return state;
    }
};

class ICmd_sub : public ICmd {
public:
    ICmd_sub(double n_operand) : ICmd(n_operand) {};
    virtual double Out(double data) final {
        return data - operand;
    };

    static bool TryInit(std::unique_ptr<ICmd>& ptr, std::string& command, double value) {
        bool state = false;
        if (command == "SUB") {
            ptr.reset(new ICmd_sub(value));
            state = true;
        }
        return state;
    }
};

class ICmd_mul : public ICmd {
public:
    ICmd_mul(double n_operand) : ICmd(n_operand) {};
    virtual double Out(double data) final {
        return data * operand;
    };

    static bool TryInit(std::unique_ptr<ICmd>& ptr, std::string& command, double value) {
        bool state = false;
        if (command == "MUL") {
            ptr.reset(new ICmd_mul(value));
            state = true;
        }
        return state;
    }
};

class ICmd_div : public ICmd {
public:
    ICmd_div(double n_operand) : ICmd(n_operand) {};
    virtual double Out(double data) final {
        return data / operand;
    };

    static bool TryInit(std::unique_ptr<ICmd>& ptr, std::string& command, double value) {
        bool state = false;
        if (command == "DIV" && value != 0) {
            ptr.reset(new ICmd_div(value));
            state = true;
        }
        return state;
    }
};


class Cmd_Factory {
public:
    Cmd_Factory() = default;
    bool operator()(std::unique_ptr<ICmd>& res_ptr, std::string& cmd, std::istream& inp_stream, int line_num) {
        res_ptr.reset(nullptr);
        double value = 0;

        if (user_input_double(value, inp_stream, line_num)) {
            for (auto cur_init : ptr_data) {
                if (cur_init(res_ptr, cmd, value)) {
                    break;
                }
            }
        }
        return res_ptr != nullptr;
    }

private:
    std::vector<bool (*) (std::unique_ptr<ICmd>&, std::string&, double)>
        ptr_data{ &ICmd_add::TryInit, &ICmd_sub::TryInit,
                  &ICmd_mul::TryInit, &ICmd_div::TryInit };
};

int main(int argc, char* argv[]) {
    std::string input_file_path;
    std::string output_file_path;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-i") == 0) {
            if (i != argc - 1) {
                if (input_file_path.empty()) {
                    input_file_path = argv[i + 1];
                }
                else {
                    std::cerr << "\x1B[31m" << "ERR: input file specified twice!" << "\033[0m" << std::endl;
                    return 0;
                }
            }
            else {
                std::cerr << "\x1B[31m" << "ERR: input file is incorrect!" << "\033[0m" << std::endl;
                return 0;
            }
        }
        else if (strcmp(argv[i], "-o") == 0) {
            if (i != argc - 1) {
                if (output_file_path.empty()) {
                    output_file_path = argv[i + 1];
                }
                else {
                    std::cerr << "\x1B[31m" << "ERR: output file specified twice!" << "\033[0m" << std::endl;
                    return 0;
                }
            }
            else {
                std::cerr << "\x1B[31m" << "ERR: output file is incorrect!" << "\033[0m" << std::endl;
                return 0;
            }
        }
        else if (strcmp(argv[i], "--help") == 0) {
            std::cout << "\t -i <file> \t specify an input file\n";
            std::cout << "\t -o <file> \t specify an output file\n";
            std::cout << "\t --help \t display this screen and exit\n";
            return 0;
        }
    }

    if (input_file_path.empty()) {
        std::cerr << "\x1B[31m" << "ERR: input file not specified!" << "\033[0m" << std::endl;
        return 0;
    }
    if (output_file_path.empty()) {
        std::cerr << "\x1B[31m" << "ERR: output file not specified!" << "\033[0m" << std::endl;
        return 0;
    }

    std::ifstream inp_stream(input_file_path);
    std::ofstream out_stream(output_file_path);

    if (!inp_stream.is_open()) {
        std::cerr << "\x1B[31m" << "ERR: error opening " << input_file_path
            << " as input file" << "\033[0m" << std::endl;
        return 0;
    }
    if (!out_stream.is_open()) {
        std::cerr << "\x1B[31m" << "ERR: error opening " << output_file_path
            << " as output file" << "\033[0m" << std::endl;
        return 0;
    }

    std::vector<std::unique_ptr<ICmd>> data;

    Cmd_Factory make_cmd;
    std::string command;
    int command_number = 1;
    while (inp_stream >> command) {
        if (command == "OUT") {
            double value = 0;
            if (!user_input_double(value, inp_stream, command_number)) {
                break;
            }

            for (auto& ptr : data) {
                value = ptr->Out(value);
            }

            out_stream << value << std::endl;
        }
        else if (command == "REV") {
            int shrink = 0;
            if (!user_input_int(shrink, inp_stream, command_number)) {
                break;
            }

            if (shrink > static_cast<int>(data.size()) || shrink < 0) {
                std::cerr << "\x1B[31m" << "ERR: REV size is incorrect! "
                    << "Check line " << command_number << '.' << "\033[0m" << std::endl;
                break;
            }

            data.resize(data.size() - shrink);
        }
        else {
            std::unique_ptr<ICmd> ptr(nullptr);
            if (make_cmd(ptr, command, inp_stream, command_number)) {
                data.emplace_back(std::move(ptr));
            }
            else {
                std::cerr << "\x1B[31m" << "ERR: unknown command! "
                    << "Check line " << command_number << '.' << "\033[0m" << std::endl;
                break;
            }
        }

        ++command_number;
    }

    return 0;
}
