// Assignment 1 - The Bohr Atom
// Program to calculate transition energy using simple Bohr formula
// Student ID: 11069622
// Date: 04/02/2025

#include <cmath>
#include <iostream>
#include <string>

const double eV = 1.602176634e-19;
const double eV_reciprocal = 6.241509074460763e18;  // 1/eV

double energy_difference(int initial_energy, int final_energy)
{
  return (1.0 / std::pow(final_energy, 2)) - (1.0 / std::pow(initial_energy, 2));
}

double Bohr_energy_transition(int atomic_number, int initial_energy, int final_energy)
{
  return 13.6 * std::pow(atomic_number, 2) * energy_difference(initial_energy, final_energy);
}

double joules_to_eV(double number_in_joules)
{
  return number_in_joules * eV_reciprocal;
}

double eV_to_joules(double number_in_eV)
{
  return number_in_eV * eV;
}

// Function to handle user input and any errors, returns -1 if failed in an unexpected way.
int user_input_handler(std::string user_message, std::string error_message)
{
  // return variable.
  int user_input{-1};
  // Temporary variables for string checks.
  std::string input{""};
  std::size_t size{0};

  std::cout << user_message << '\n';
  std::cin >> input;
  try
  {  // Try to convert user input to an integer, return the number of characters converted as well (size)
    user_input = std::stoi(input, &size);
  }
  catch(const std::exception &e)
  {
  }  // Catch error so we may ask user for input again

  // Check that the user inputted a positive integer, check that the converted number string (user_input) size matches the exact size of the user input
  while(user_input <= 0 || std::cin.fail() || input.length() != size)
  {
    std::cout << error_message << '\n';
    std::cout << user_message << '\n';
    std::cin.clear();
    std::cin.ignore();  // Clear the error and flush the input
    std::cin >> input;
    try
    {
      user_input = std::stoi(input, &size);
    }
    catch(const std::exception &e)
    {
    }
  }
  return user_input;
}

int main()
{
  // Variables declared here
  int user_atomic_number;
  int user_initial_energy;
  int user_final_energy;
  std::string choice;

  // Introductory message
  std::cout << "Hi there, this program is for the purposes of calculating the "
               "energy transition of an electron using the Bohr model."
            << '\n';

  // Ask user for required parameters
  user_atomic_number = user_input_handler("Please enter the atomic number below", "Error: This is not a positive integer");
  user_initial_energy = user_input_handler("Please enter the initial quantum energy below", "Error: this is not a positive integer");
  user_final_energy = user_input_handler("Please enter the final quantum energy state below", "Error: this is not a positive integer");

  // Final check to ensure that the energy difference is positive.
  while(energy_difference(user_initial_energy, user_final_energy) <= 0 || user_final_energy == 0 || user_initial_energy == 0)
  {
    std::cout << "Error: The final energy **must** be below the initial energy "
                 "and the values must be strictly above 0, please try again "
                 "with physically possible values below\n";
    user_initial_energy = user_input_handler("Please enter the initial quantum energy below", "Error: this is not a positive integer");
    user_final_energy = user_input_handler("Please enter the final quantum energy state below", "Error: this is not a positive integer");
  }

  // Compute photon energy, Delta E = 13.6*(Z^2)*(1/n_j^2-1/n_i^2) eV
  double photon_energy = Bohr_energy_transition(user_atomic_number, user_initial_energy, user_final_energy);

  // Which energy unit would the user like there answer in
  int ev_or_joule = user_input_handler("Please provide the unit of measurement you would "
                                       "like\n1 for joules (J)\n2 for electron volts (eV)",
                                       "Error this is not valid input");
  while(ev_or_joule != 1 && ev_or_joule != 2)
  {
    std::cout << "Error: input must be either 1 or 2" << '\n';
    ev_or_joule = user_input_handler("Please provide the unit of measurement you would like\n1 for joules "
                                     "(J)\n2 for electron volts (eV)\n",
                                     "Error this is not valid input");
  }
  if(ev_or_joule == 1)
  {
    photon_energy = eV_to_joules(photon_energy);
  }
  // Output answer
  std::cout << "Here is the photon energy: " << photon_energy << std::endl;

  std::cout << "Would you like to perform another calculation? (y/n): \n";
  std::cin >> choice;

  while(choice != "y" && choice != "n")
  {
    std::cout << "Would you like to perform another calculation? (please enter "
                 "y or n): \n";
    std::cin >> choice;
  }

  if(choice == "y")
  {
    main();  // Recursive call to repeat
  }

  return 0;
}
