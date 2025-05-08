#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>

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

// Émulation de registres et mémoire
std::unordered_map<std::string, int> registres;
std::unordered_map<int, int> memoire;

// Exécute une ligne : supporte print, input et mov
void execute_vm(const std::string& ligne) {
    std::istringstream iss(ligne);
    std::string instruction;
    iss >> instruction; // premier mot

    if (instruction == "print") {
        std::string to_print;
        std::getline(iss, to_print); // récupère le reste de la ligne
        if (!to_print.empty() && to_print[0] == ' ')
            to_print = to_print.substr(1); // Enlève l'espace initial
        std::cout << to_print << std::endl;
    }
    if (instruction == "input") {
        std::string reg;
        iss >> reg; // lit le registre
        std::string prompt;
        std::getline(iss, prompt); // récupère le reste de la ligne
        if (!prompt.empty() && prompt[0] == ' ')
            prompt = prompt.substr(1);
        std::cout << prompt; // Affiche le message de demande d'entrée
        int user_input;
        std::cin >> user_input; // Lit l'entrée utilisateur
        registres[reg] = user_input; // Stocke dans le registre
    }
    if (instruction == "mov") {
        std::string dest, src;
        iss >> dest >> src; // lit destination et source
        if (src[0] == 'R') { // Source est un registre
            registres[dest] = registres[src];
        } else if (isdigit(src[0]) || src[0] == '-') { // Source est une valeur immédiate
            registres[dest] = std::stoi(src);
        } else if (src[0] == 'M') { // Source est une adresse mémoire
            int addr = std::stoi(src.substr(1));
            registres[dest] = memoire[addr];
        }
    }
    if (instruction == "store") {
        std::string reg;
        int addr;
        iss >> reg >> addr; // lit registre et adresse
        memoire[addr] = registres[reg]; // Stocke dans la mémoire
    }
}

int main() {
    // Exemple de code d'assemblage
    std::string code = 
        "input R1 Entrez une valeur :\n"
        "mov R2 R1\n"
        "store R2 100\n"
        "mov R3 M100\n"
        "print R3";

    std::vector<std::string> lignes = parse(code);

    for (const auto& ligne : lignes) {
        execute_vm(ligne);
    }

    return 0;
}
