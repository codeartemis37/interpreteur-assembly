#include <iostream>
#include <string>
#include <vector>
#include <sstream>

// Découpe le code en lignes
std::vector<std::string> parse(const std::string& assembly_code) {
    std::vector<std::string> lignes;
    std::istringstream iss(assembly_code);
    std::string ligne;
    while (std::getline(iss, ligne)) {
        lignes.push_back(ligne);
    }
    return lignes;
}

// Exécute une ligne : si "print", affiche ce qui suit
void execute_vm(const std::string& ligne) {
    std::istringstream iss(ligne);
    std::string instruction;
    iss >> instruction; // premier mot

    if (instruction == "print") {
        std::string to_print;
        std::getline(iss, to_print); // récupère le reste de la ligne
        // Enlève l'espace initial éventuel
        if (!to_print.empty() && to_print[0] == ' ')
            to_print = to_print.substr(1);
        std::cout << to_print << std::endl;
    }
    // Tu peux ajouter d'autres instructions ici (ex: input, mov, etc.)
}

int main() {
    std::string code = "print salut\nprint comment ca va ?\nprint 42";

    std::vector<std::string> lignes = parse(code);

    for (const auto& ligne : lignes) {
        execute_vm(ligne);
    }

    return 0;
}
