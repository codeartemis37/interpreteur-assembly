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

// Exécute une ligne : si "print", affiche ce qui suit ou si "input", demande une entrée utilisateur
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
    } else if (instruction == "input") {
        std::string prompt;
        std::getline(iss, prompt); // récupère le reste de la ligne
        // Enlève l'espace initial éventuel
        if (!prompt.empty() && prompt[0] == ' ')
            prompt = prompt.substr(1);
        std::cout << prompt; // Affiche le message de demande d'entrée
        std::string user_input;
        std::cin >> user_input; // Lit l'entrée utilisateur
        std::cout << "Vous avez saisi : " << user_input << std::endl;
    }
    // Tu peux ajouter d'autres instructions ici (ex: mov, etc.)
}

int main() {
    std::string code = "print salut\ninput Entrez votre nom :\nprint 42";

    std::vector<std::string> lignes = parse(code);

    for (const auto& ligne : lignes) {
        execute_vm(ligne);
    }

    return 0;
}
