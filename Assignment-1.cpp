// Assignment 1 - The Bohr Atom
// Program to calculate transition energy using simple Bohr formula
// Student ID: 11069622
// Date: 04/02/2025

#include <cmath>
#include <iostream>
#include <string>

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

// Function to handle user input and handle any errors
int user_input_handler(std::string message, std::string error_message)
{
  // return variable
  int user_number{0};
  // Tempt variables for string checks
  std::string input{""};
  std::size_t size{0};

  std::cout << message << '\n';
  std::cin >> input;
  try
  {
    user_number = std::stoi(input, &size);
    return user_number;
  }
  catch(const std::exception& e)
  {
    std::cout << "Exception error: " << e.what() << '\n';
  }

  std::cout << input << std::cin.fail() << input.length() << size << '\n';
  // Check that the user inputted a correct number, check that the number string size matches the exact size of the user input
  while(user_number <= 0 || std::cin.fail() || input.length() != size) // Ascii clear and ignore goes through bit by bit, however the cin data type is classed it will iterate through by that size
  {
    std::cout << error_message << '\n';
    std::cout << message << '\n'; // When user_atomic_number is set to an integer, when character is sent through iostream the integer turns to 0.
    std::cin.clear();
    std::cin.ignore(); // You can add amount to ignore in parameters you idiot...
    std::cin >> input;
    try
    {
      user_number = std::stoi(input, &size);
    }
    catch(const std::exception& e)
    {
      std::cout << "Exception error: " << e.what() << '\n';
    }
  }
  return user_number;
}

int main()
{
  // Declare variables here
  int user_atomic_number;
  int user_initial_energy;
  int user_final_energy;
  std::string choice;

  // Ask user to enter atomic number

  user_atomic_number = user_input_handler("Please enter the atomic number below", "Error: This is not a positive integer");

  user_initial_energy = user_input_handler("Please enter the initial quantum energy below", "Error: this is not a positive integer");

  user_final_energy = user_input_handler("Please enter the final quantum energy state below", "Error: this is not a positive integer");

  while(energy_difference(user_initial_energy, user_final_energy) <= 0 || user_final_energy == 0 || user_initial_energy == 0)
  {
    std::cout << "Error: The final energy **must** be below the initial energy and the values must be strictly above 0, please try again with physically possible values below\n";
    user_initial_energy = user_input_handler("Please enter the initial quantum energy below", "Error: this is not a positive integer");
    user_final_energy = user_input_handler("Please enter the final quantum energy state below", "Error: this is not a positive integer");
  }
  // Compute photon energy, Delta E = 13.6*(Z^2)*(1/n_j^2-1/n_i^2) eV
  double photon_energy = Bohr_energy_transition(user_atomic_number, user_initial_energy, user_final_energy);

  // Which energy unit would the user like there answer in
  int ev_or_joule = user_input_handler("Please provide the unit of measurement you would like\n0 for joules (J)\n1 for electron volts (eV)", "Error this is not valid input");
  while(ev_or_joule != 0 && ev_or_joule != 1)
  {
    std::cout << "Error: input must be either 0 or 1" << '\n';
    ev_or_joule = user_input_handler("Please provide the unit of measurement you would like\n0 for joules (J)\n1 for electron volts (eV)\n", "Error this is not valid input");
  }
  if(ev_or_joule == 0)
  {
    photon_energy = convert_eV_to_joules(photon_energy);
  }
  // Output answer
  std::cout << "Here is the photon energy: " << photon_energy << std::endl;

  std::cout << "Would you like to perform another calculation? (y/n): \n";
  std::cin >> choice;

  while(choice != "y" && choice != "n")
  {
    std::cout << "Would you like to perform another calculation? (please enter y or n): \n";
    std::cin >> choice;
  }

  if(choice == "y")
  {
    main();
  }

  return 0;
}
