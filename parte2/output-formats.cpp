//
// Created by skidr on 28/12/2019.
//

#include "output-formats.h"

string printTable(vector<Habitacao*> habitacoes) {
    unsigned int numHabs = habitacoes.size();
    fort::char_table table;
    table.set_border_style(FT_DOUBLE2_STYLE);

    if (habitacoes.empty()) {
        cout << "\tNothing to show\n";
        return "";
    }

    table << fort::header
          << "ID" << "Type of Habitation" << "Address" << "Habitation's Area" << "Status" << "External Area" << "Typology" << "Pool" << "Floor" << "Monthly Payment" << fort::endr;

    for (unsigned int i = 0; i < numHabs; i++) {
        table << habitacoes[i]->getID();
        (habitacoes[i]->getID()[0] == 'V') ? table << "Villa" : table << "Apartment";

        table << habitacoes[i]->getMorada();
        table << habitacoes[i]->getAreaHabitacional();

        (habitacoes[i]->getEstado()) ? table << "occupied" : table << "unoccupied";

        if (habitacoes[i]->getID()[0] == 'V') {
            table << habitacoes[i]->extraInfo()[0] << "-" << habitacoes[i]->extraInfo()[1] << "-";
        } else {
            table << "-" << habitacoes[i]->extraInfo()[0] << "-" << habitacoes[i]->extraInfo()[1];
        }
        table << habitacoes[i]->mensalidade << fort::endr;
    }
    table.set_cell_text_align(fort::text_align::center);
    return table.to_string();
}

string printTable(vector<Condomino *> condominos) {
    unsigned int numCon = condominos.size();
    fort::char_table table;
    table.set_border_style(FT_DOUBLE2_STYLE);

    if (condominos.empty()) {
        cout << "\tNothing to show\n";
        return "";
    }

    table << fort::header
          << "Name" << "VAT" << "Habitations" << "Services" << "Monthly Payment" << fort::endr;

    for (unsigned int i = 0; i < numCon; i++) {
        table << condominos[i]->getNome() << condominos[i]->getNIF();
        int numHab = condominos[i]->getNumHabitacoes();
        if (numHab == 0)
            table << 0;
        else {
            string habs;
            for (int j = 0; j < numHab; j++) {
                habs += condominos[i]->getHabitacoes()[j]->getID();
                if (j != numHab - 1) habs += " : ";
            }
            table << habs;
        }

        int numServ = condominos[i]->getServicos().size();
        if (numServ == 0)
            table << 0;
        else {
            string servs;
            for (int j = 0; j < numServ; j++) {
                servs += condominos[i]->getServicos()[j]->getTipo();
                if (j != numServ - 1) servs += " : ";
            }
            table << servs;
        }
        table << condominos[i]->mensalidadeTotal() << fort::endr;
    }
    table.set_cell_text_align(fort::text_align::center);
    return table.to_string();
}

string printTable(tabHFormerMembers formerMembers) {
    fort::char_table table;
    table.set_border_style(FT_DOUBLE2_STYLE);

    if (formerMembers.empty()) {
        cout << "\tNothing to show\n";
        return "";
    }

    table << fort::header
          << "Name" << "VAT" << "Membership Time" << fort::endr;

    for (auto& fm : formerMembers) {
        table << fm.name << fm.nif << fm.time << fort::endr;
    }
    table.set_cell_text_align(fort::text_align::center);
    return table.to_string();
}

string printTable(vector<Transporte> transports) {
    fort::char_table table;
    table.set_border_style(FT_DOUBLE2_STYLE);

    if (transports.empty()) {
        cout << "\tNothing to show\n";
        return "";
    }

    table << fort::header
          << "Location" << "Distance (m)" << "Destiny" << "Active?" << fort::endr;

    for (auto & tr : transports) {
        table << tr.getLocalization() << tr.getDistance() << tr.getDestiny();
        (tr.getState()) ? table << "Yes" : table << "No";
        table << fort::endr;
    }

    table.set_cell_text_align(fort::text_align::center);
    return table.to_string();
}

string printTable(BST<Condominio *> condominios) {
    fort::char_table table;
    table.set_border_style(FT_DOUBLE2_STYLE);

    if (condominios.isEmpty()) {
        cout << "\tNothing to show\n";
        return "";
    }
    table << fort::header
          << "Designation" << "Location" << "Members" << "Habitations" << "Revenue" << fort::endr;

    BSTItrLevel<Condominio*> it(condominios);
    while (!it.isAtEnd()) {
        table << it.retrieve()->getDesignation() << it.retrieve()->getLocation() <<
                it.retrieve()->getNumCondominos() << it.retrieve()->getNumHabitacoes() <<
                it.retrieve()->calcReceitas() << fort::endr;
        it.advance();
    }
    table.set_cell_text_align(fort::text_align::center);
    return table.to_string();
}

string printTable(vector<Servico*> servicos) {
    fort::char_table table;
    table.set_border_style(FT_DOUBLE2_STYLE);

    if (servicos.empty()) {
        cout << "\tNothing to show\n";
        return "";
    }
    table << fort::header
          << "Service" << "Cost" << "Provider" << fort::endr;

    for (auto & s : servicos) {
        table << s->getTipo() << s->getCusto() << s->getPrestador() << fort::endr;
    }

    table.set_cell_text_align(fort::text_align::center);
    return table.to_string();
}

string printTable(vector<FormerMember> formerMembers) {
    fort::char_table table;
    table.set_border_style(FT_DOUBLE2_STYLE);

    if (formerMembers.empty()) {
        cout << "\tNothing to show\n";
        return "";
    }
    table << fort::header
          << "Name" << "VAT" << "Time" << fort::endr;

    for (auto & fm : formerMembers) {
        table << fm.name << fm.nif << fm.time << fort::endr;
    }

    table.set_cell_text_align(fort::text_align::center);
    return table.to_string();
}

ostream &operator<<(ostream &os, FormerMember &fm) {
    os << "\tName: " << fm.name << endl;
    os << "\tVAT number: " << fm.nif << endl;
    os << "\tTime on condominium: " << fm.time;
    return os;
}
