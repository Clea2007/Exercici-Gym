#include <iostream>
#include <string>
#include <vector>
#include <memory>

// 1. CLASSE TARIFA (Classe de suport)

class Tarifa {
private:
    std::string nomTarifa;
    double preuMensual;

public:
    Tarifa(const std::string& nom = "Estandard", double preu = 0.0)
        : nomTarifa(nom), preuMensual(preu) {}

    std::string getNomTarifa() const { return nomTarifa; }
    double getPreuMensual() const { return preuMensual; }
};

// 2. CLASSE SOCI (Composició amb Tarifa)

class Soci {
protected:
    std::string nom;
    int idSoci;
    Tarifa tarifa; 

public:
    Soci(const std::string& nom, int idSoci, const Tarifa& tarifa)
        : nom(nom), idSoci(idSoci), tarifa(tarifa) {}

    virtual ~Soci() = default; 

    virtual double calcularQuota() const {
        return tarifa.getPreuMensual();
    }

    std::string getNom() const { return nom; }
    int getIdSoci() const { return idSoci; }
    Tarifa getTarifa() const { return tarifa; }
};

// 3. CLASSE SOCIVIP (Herència de Soci)

class SociVIP : public Soci {
private:
    double descompteEntrenador;

public:
    SociVIP(const std::string& nom, int idSoci, const Tarifa& tarifa, double descompteEntrenador)
        : Soci(nom, idSoci, tarifa), descompteEntrenador(descompteEntrenador) {}

    // Redefinició (override) del mètode virtual
    double calcularQuota() const override {
        double quotaBase = tarifa.getPreuMensual();
        double quotaFinal = quotaBase - descompteEntrenador;
        return (quotaFinal > 0.0) ? quotaFinal : 0.0;
    }

    double getDescompteEntrenador() const { return descompteEntrenador; }
};

// PROGRAMA DE PROVA

int main() {
    // Definició de tarifes
    Tarifa tarifaCompleta("Completa 24/7", 60.0);

    // Creació de socis
    Soci sociNormal("Clea Gonzalez", 101, tarifaCompleta);
    SociVIP sociVIP("Eric Parcerisas", 102, tarifaCompleta, 15.0); 

    // Mostrar dades
    std::cout << "--- DEMOSTRACIO DE QUOTES ---" << std::endl;
    std::cout << "Soci: " << sociNormal.getNom()
        << " | Tarifa: " << sociNormal.getTarifa().getNomTarifa()
        << " | Quota final: " << sociNormal.calcularQuota() << " EUR" << std::endl;

    std::cout << "Soci VIP: " << sociVIP.getNom()
        << " | Tarifa: " << sociVIP.getTarifa().getNomTarifa()
        << " | Quota final: " << sociVIP.calcularQuota() << " EUR" << std::endl;

    // Demostració de polimorfisme
    std::cout << "\n--- DEMOSTRACIO POLIMORFICA ---" << std::endl;
    std::vector<std::unique_ptr<Soci>> llistaSocis;
    llistaSocis.push_back(std::make_unique<Soci>("Clea Gonzalez", 103, tarifaCompleta));
    llistaSocis.push_back(std::make_unique<SociVIP>("Eric Parcerisas", 104, tarifaCompleta, 20.0));

    for (const auto& soci : llistaSocis) {
        std::cout << "ID " << soci->getIdSoci() << " - " << soci->getNom()
            << " paga una quota de: " << soci->calcularQuota() << " EUR" << std::endl;
    }

    return 0;
}