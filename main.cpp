#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <functional>

// Structure pour stocker une ligne de code parsée
struct Instruction {
    std::string fonction;                 // Nom de l'instruction (ex: "mov", "print", etc.)
    std::vector<std::pair<std::string, std::string>> arguments; // Liste des arguments avec leur type ("texte", "registre", "memoire")
};

// Émulation de registres et mémoire
std::unordered_map<std::string, int> registres;
std::unordered_map<int, int> memoire;

// Fonction pour détecter le type d'un argument
std::string detecter_type(const std::string& argument) {
    if (argument[0] == 'R') {
        return "registre";
    } else if (argument[0] == 'M') {
        return "memoire";
    } else {
        return "texte";
    }
}

// Fonction parse améliorée
std::vector<Instruction> parse(const std::string& assembly_code) {
    std::vector<Instruction> instructions;
    std::istringstream iss(assembly_code);
    std::string ligne;

    while (std::getline(iss, ligne)) {
        std::istringstream ligne_stream(ligne);
        std::string fonction;
        ligne_stream >> fonction; // Récupère l'instruction (ex: "mov", "print")

        Instruction instruction;
        instruction.fonction = fonction;

        std::string argument;
        while (ligne_stream >> argument) {
            std::string type = detecter_type(argument); // Détecte le type de l'argument
            instruction.arguments.emplace_back(type, argument); // Ajoute l'argument et son type
        }

        instructions.push_back(instruction);
    }

    return instructions;
}

// Commandes implémentées
void cmd_print(const Instruction& instruction) {
    for (const auto& arg : instruction.arguments) {
        if (arg.first == "texte") {
            std::cout << arg.second << " ";
        } else if (arg.first == "registre") {
            std::cout << registres[arg.second] << " ";
        }
    }
    std::cout << std::endl;
}

void cmd_input(const Instruction& instruction) {
    const auto& reg = instruction.arguments[0].second;
    std::cout << "Entrez une valeur : ";
    int user_input;
    std::cin >> user_input;
    registres[reg] = user_input;
}

void cmd_mov(const Instruction& instruction) {
    const auto& dest = instruction.arguments[0].second;
    const auto& src = instruction.arguments[1].second;

    if (src[0] == 'R') { // Source est un registre
        registres[dest] = registres[src];
    } else if (isdigit(src[0]) || src[0] == '-') { // Source est une valeur immédiate
        registres[dest] = std::stoi(src);
    } else if (src[0] == 'M') { // Source est une adresse mémoire
        int addr = std::stoi(src.substr(1));
        registres[dest] = memoire[addr];
    }
}

void cmd_store(const Instruction& instruction) {
    const auto& reg = instruction.arguments[0].second;
    int addr = std::stoi(instruction.arguments[1].second);
    memoire[addr] = registres[reg];
}

// Table de hachage des commandes
std::unordered_map<std::string, std::function<void(const Instruction&)>> commandes = {
    {"print", cmd_print},
    {"input", cmd_input},
    {"mov", cmd_mov},
    {"store", cmd_store}
};

// Exécuter les instructions parsées
void execute_vm(const Instruction& instruction) {
    auto it = commandes.find(instruction.fonction);
    if (it != commandes.end()) {
        it->second(instruction); // Appelle la commande correspondante
    } else {
        std::cerr << "Erreur : Commande inconnue '" << instruction.fonction << "'\n";
    }
}

int main() {
    // Exemple de code d'assemblage
    std::string code = 
        "input R1\n"
        "mov R2 R1\n"
        "store R2 100\n"
        "mov R3 M100\n"
        "print R3";

    // Parse le code
    std::vector<Instruction> instructions = parse(code);

    // Exécute chaque instruction
    for (const auto& instruction : instructions) {
        execute_vm(instruction);
    }

    return 0;
}
