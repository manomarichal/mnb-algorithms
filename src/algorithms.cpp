//
// Created by mano on 15.10.19.
//
#include "./algorithms.h"

void printCykTable(const std::vector<std::vector<std::vector<std::string>>> &table, std::string filename)
{
    std::fstream file;
    file.open("./outputfiles/" + filename + ".html", std::fstream::out);

    file << "<style>\n"
    "table {\n"
    "   border-collapse: collapse;\n"
    "}\n"
    "td, th {\n"
    "   border: 1px solid orange;\n"
    "   padding: 15px;\n"
    "}\n"
    "</style>\n";

    file << "<table>";
    for (u_long y = table.size()-1; y<table.size(); --y) {
        file << "<tr>\n";
        for (u_long x = 0; x<table.size(); ++x) {
            file << "<th>";
            if (!table[x][y].empty()) file << "{";
            else file << "∅";
            for (auto var:table[x][y]) {
                file << var;
                if (var != *--table[x][y].end()) file << ", " ;
            }
            if (!table[x][y].empty()) file << "}";
            file << "</th>\n";
        }
        file << "</tr>";
    }
    file << "</table>";
    file.close();
}


void
generateBody(std::vector<std::string> &stack, std::string body, PDA &pda, CFG &cfg, const std::string &top, int level,
             int max) {
    if (max == -1) {
        if (body[0] == '[') {
            cfg.addProduction(top + body.substr(1, body.size() - 1), {"ε"});
        } else cfg.addProduction(top + body.substr(2, body.size() - 2), {body[0]});
        return;
    };

    if (level == max) {
        for (const auto &state:pda.getStates()) {
            std::string orgBody = body;
            orgBody += stack[level] + state.stateName + "]";
            cfg.addProduction(top + state.stateName, orgBody);
        }
        return;
    }
    for (const auto &state:pda.getStates()) {
        std::string orgBody = body;
        orgBody += stack[level] + state.stateName + "][" + state.stateName;
        generateBody(stack, orgBody, pda, cfg, top, level + 1, max);
    }
}

CFG convertToCfg(PDA &pda) {
    CFG cfg;
    cfg.setTerminals(pda.getAlphabet());

    std::vector<std::string> variables;
    variables.emplace_back("S");

    for (const auto &v1:pda.getStates()) {
        for (const auto &symbol:pda.getStackAlphabet()) {
            for (const auto &v2:pda.getStates()) {
                variables.emplace_back(v1.stateName + symbol + v2.stateName);
            }
        }
    }

    cfg.setVariables(variables);

    cfg.setStart("S");

    for (const auto &v1:pda.getStates()) {
        // productions for startsymbol S
        cfg.addProduction("S", "[" + pda.getStartState().stateName + pda.getStartStackSymbol() + v1.stateName + "]");

        //productions for the rest
        for (const auto &transition:v1.getTransitions()) {
            std::vector<std::string> stack = std::get<2>(transition.second);
            generateBody(stack, transition.first.first + "[" + std::get<0>(transition.second)->stateName,
                         pda, cfg, v1.stateName + transition.first.second,
                         0, std::get<2>(transition.second).size() - 1);
        }
    }

    return cfg;
}

bool CYK(CFG &cfg, std::vector<std::string> input, std::string filename) {
    std::vector<std::vector<std::vector<std::string>>> table;

    // create table
    for (u_long y = 0; y < input.size(); y++) {
        table.emplace_back();
        for (u_long x = 0; x < input.size(); x++) {
            table[y].emplace_back();
        }
    }

    // loop over the table
    for (u_long y = 0; y < input.size(); y++) {
        for (u_long x = 0; x < input.size(); x++) {

            // skip upper cases
            if (x + y >= input.size()) continue;

            // base case
            if (y == 0) {
                for (auto &var: cfg.getProductions()) {
                    for (auto &production: var.second) {
                        if (production.size() == 1 and production[0] == std::string(input[x])) {
                            table[x][y].emplace_back(var.first);
                        }
                    }
                }
                continue;
            }
            // not base case
            if (x == 2 and y == 1) {
                int a = 5;
            }

            // look for all possible bodies
            std::vector<std::vector<std::string>> bodies;
            for (u_long k = 0; k < y; k++) {
                for (std::string var1:table[x][k]) {
                    for (std::string var2:table[x + k + 1][y - (k + 1)]) {
                        std::vector<std::string> t = {var1, var2};
                        bodies.emplace_back(t);
                    }
                }
            }

            // check which variables have the bodies and put them in the table entry
            for (auto body:bodies) {
                for (auto &var: cfg.getProductions()) {
                    for (auto &production: var.second) {
                        if (production == body) {
                            table[x][y].emplace_back(var.first);
                        }
                    }
                }
            }
        }
    }

    printCykTable(table, filename);

    for(auto var:table[0][input.size()-1])
    {
        if (var == cfg.getStart()) return true;
    }

    return false;
}



