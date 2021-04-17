#include <iostream>
#include <unordered_map>

void block_parser(std::unordered_map<std::string, int> var_dict)
{
    std::string input_line;
    while (std::getline(std::cin, input_line))
    {
//        std::cout << "Got line: " << input_line << std::endl;
        if (input_line.find('{') != std::string::npos) {
            block_parser(var_dict);
            continue;
        }
        if (input_line.find('}') != std::string::npos)
            return;

        size_t delimiter_position = input_line.find('=');
        std::string var = input_line.substr(0, delimiter_position);
        input_line.erase(0, delimiter_position + 1);

//        std::cout << "Parsed to " << var << " " << input_line << std::endl;

        if (std::isdigit(input_line[0]) || input_line[0]=='-') {
            var_dict[var] = std::stoi(input_line);
        }
        else {
            if (var_dict.find(input_line) != var_dict.end())
                var_dict[var] = var_dict[input_line];
            else
                var_dict[var] = 0;
            std::cout <<  var_dict[var] << std::endl;
        }
    }
}

int main()
{
    std::unordered_map<std::string, int> var_dict;
    block_parser(var_dict);
}
