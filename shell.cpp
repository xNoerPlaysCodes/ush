#include <iostream>
#include <string>
#include <cstdlib>
#include <filesystem>
#include <sstream>
#include <vector>
#include <thread>
#include <chrono>
#include <fstream>
#include <cmath>
#include <ctime>
using str = std::string;
str loadConfig(const str &configFile);

// Binary loading
void loadFile(const str &name) {
    str bindir = loadConfig("bindir");
    str command = bindir + name;
    std::system(command.c_str());
}

auto split(str &input) {
    std::istringstream iss(input);
    std::vector<std::string> args;
    std::string arg;
    while (iss >> arg) {
        args.push_back(arg);
    }
    return args;
}

void sleep(int time /* In seconds */) {
    std::this_thread::sleep_for(std::chrono::seconds(time));
}

str loadConfig(const str &configFile) {
    str fs = "./.ush/config/" + configFile + ".txt";
    std::ifstream file(fs);

    if (file.is_open()) {
        str line;
        while (std::getline(file, line)) {
            return line;
        }
        file.close();
    } else {
        std::cerr << "Unable to open config file '" << configFile << ".txt'.\n";
        // Unable to open config file '{configFile}.txt'\n
    }
}

str saveConfig(const str configFile, const str newValue) {
    str fs = "./.ush/config/" + configFile + ".txt";
    std::ofstream file(fs);

    if (file.is_open()) {
        file << newValue;
        file.close();
        return "WRITE_SUCCESS";
    } else {
        return "WRITE_FAILURE";
    }
}

/* ************************************* */
int main() {
    // ShellInit
    if (std::filesystem::exists("./.ush/")) {
        std::cout << "uSH Initialised\n";
    }
    else {
        std::system("mkdir ./.ush/");
        std::system("mkdir ./.ush/programs/");
        std::system("mkdir ./.ush/programs/text");
    }
    /* *********************** */
    // Startup of shell settings:
    bool shell_is_running = true;
    /* *********************** */
    while (shell_is_running) {
        str user_input;
        std::cout << "ush: ";
        std::getline(std::cin, user_input);
        // Handling of Empty Inputs
        if (user_input.empty()) { continue; }
        else if (user_input.find(" ") == 0) { continue; }
        else if (user_input.find("    ") == 0) { continue; }
            /* ******** */
        else if (user_input == "help") {
            loadFile("help");
        } else if (user_input == "about") {
            std::cout << "ush is a simple shell coded in C++\nCredits go to:\nnoerlol - dev\n";
        } else if (user_input == "clear") {
            std::system("clear");
        } else if (user_input == "exit") {
            shell_is_running = false;
        } else if (user_input.find("text") == 0) {
            auto args = split(user_input);
            if (args.size() < 2) {
                std::cerr << "Not enough arguments.\n";
            } else {
                if (args[1] == "--editor") {
                    loadFile("text");
                } else if (args[1] == "--read-mode") {
                    loadFile("text_readmode");
                } else {
                    std::cerr << "Invalid arguments at position 1.\n";
                }
            }
        } else if (user_input.find("echo") == 0) {
            auto args = split(user_input);
            if (args.size() < 2) {
                std::cerr << "Not enough arguments.\n";
            } else {
                for (int i = 1; i < args.size(); i++) {
                    if (i == args.size() - 1) {
                        std::cout << args[i] << '\n';
                    } else {
                        std::cout << args[i] << ' ';
                    }
                }
            }
        } else if (user_input.find("bindir --change") == 0) {
            str current_bindir = loadConfig("bindir");
            if (current_bindir == "./bin/") {
                saveConfig("bindir", "/bin/");
                std::cout << "Changed binaries directory to /bin/. Now your ush binaries won't work but you can access your installed programs and things.\n";
            } else if (current_bindir == "/bin/") {
                saveConfig("bindir", "./bin/");
                std::cout << "Changed binaries directory to ./bin/. Now only your ush binaries will work.\n";
            } else {
                std::cout << "Invalid bindir location.\n";
            }
        } else {
            str bindir = loadConfig("bindir");
            if (bindir == "/bin/") {
                loadFile(user_input);
            } else {
                std::cout << "Invalid Command.\n";
            }
        }
    }
}
