// Assignment 1 - The Bohr Atom
// Program to calculate transition energy using simple Bohr formula
// Student ID: 11069622
// Date: 04/02/2025

#include <cmath>
#include <iostream>

const double eV = 1.602176634e-19;
const double eV_reciprocal = 6.241509074460763e18; // 1/eV

double energy_difference(int initial_energy, int final_energy)
{
  return (1.0 / std::pow(final_energy, 2)) - (1.0 / std::pow(initial_energy, 2));
}

double Bohr_energy_transition(int atomic_number, int initial_energy, int final_energy)
{
  return 13.6 * std::pow(atomic_number, 2) * energy_difference(initial_energy, final_energy);
}

double convert_joules_to_eV(double number_in_joules)
{
  return number_in_joules * eV_reciprocal;
}

double convert_eV_to_joules(double number_in_eV)
{
  return number_in_eV * eV;
}

int main()
{
  // Declare variables here
  int user_atomic_number;
  int user_initial_energy;
  int user_final_energy;
  std::string choice;
  // Ask user to enter atomic number
  std::cout << "Please enter the atomic number below" << '\n';
  std::cin >> user_atomic_number;
  while(user_atomic_number <= 0)
  {
    std::cout << "Error: The atomic number must be positive" << '\n';
    std::cout << "Please enter atomic number below" << '\n';
    std::cin >> user_atomic_number;
  }
  // Ask user to enter initial and final quantum numbers
  std::cout << "Please now enter the initial quantum energy "
               "state of the electron"
            << '\n';
  std::cin >> user_initial_energy;
  std::cout << "Please now enter the final quantum energy "
               "state of the electron"
            << '\n';
  std::cin >> user_final_energy;
  while(energy_difference(user_initial_energy, user_final_energy) <= 0)
  {
    std::cout << "Error: This input is below 0, this is not possible\n";
    std::cout << "Please enter the initial quantum energy "
                 "state of the electron"
              << '\n';
    std::cin >> user_initial_energy;
    std::cout << "Please enter the final quantum energy state that is below "
                 "the initial state"
                 "state of the electron"
              << '\n';
    std::cin >> user_final_energy;
  }
  // Compute photon energy, Delta E = 13.6*(Z^2)*(1/n_j^2-1/n_i^2) eV
  double photon_energy = Bohr_energy_transition(user_atomic_number, user_initial_energy, user_final_energy);
  // Output answer
  std::cout << "Here is the photon energy: " << photon_energy << std::endl;

  std::cout << "Would you like to perform another calculation? (y/n): \n";
  std::cin >> choice;

  if(choice == "y")
  {
    main();
  }

  return 0;
}
