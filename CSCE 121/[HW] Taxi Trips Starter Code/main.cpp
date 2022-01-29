#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "taxi_trips.h"
using std::string, std::ifstream, std::cin, std::cout, std::endl;

int main() {

  // TODO(student): implement


  string filename;
    cout << "Enter name of input file: ";
    cin >> filename;
    ifstream ifs(filename);
    if (!ifs.is_open()) {
      cout << "Can't open " << filename << endl;
      return 1;
    }

    string line;
    int array_index = 0;

    string possible_payments[4] = {"CreditCard", "Cash", "NoCharge", "Unknown"};

    string taxi_id;
    double trip_seconds;
    double trip_miles;
    double trip_fare;
    double trip_tip;
    string payment_type;

    string taxi_id_array[MAX_TRIPS];
    double trip_seconds_array[MAX_TRIPS];
    double trip_miles_array[MAX_TRIPS];
    double trip_fare_array[MAX_TRIPS];
    double trip_tip_array[MAX_TRIPS];
    string payment_type_array[MAX_TRIPS];

    int invalid = 0;

    while (!ifs.eof())
    {
      ifs >> taxi_id;
      ifs >> trip_seconds;
      ifs >> trip_miles;
      ifs >> trip_fare;
      ifs >> trip_tip;
      ifs >> payment_type;

      if ((trip_seconds <= (24 * 60 * 60)) && (trip_miles <= 1500) &&
      (trip_fare + trip_tip <= 5000) && (is_payment_valid(payment_type, possible_payments, 4)))
      {
        taxi_id_array[array_index] = taxi_id;
        trip_seconds_array[array_index] = trip_seconds;
        trip_miles_array[array_index] = trip_miles;
        trip_fare_array[array_index] = trip_fare;
        trip_tip_array[array_index] = trip_tip;
        payment_type_array[array_index] = payment_type;
        array_index++;
      }
      else
        invalid++;
    }

    double max_min = max(trip_seconds_array, array_index);
    double min_min = min(trip_seconds_array, array_index);
    double avg_min = average(trip_seconds_array, array_index);
    double mode_min = mode(trip_seconds_array, array_index);

    double max_miles = max(trip_miles_array, array_index);
    double min_miles = min(trip_miles_array, array_index);
    double avg_miles = average(trip_miles_array, array_index);
    double mode_miles = mode(trip_miles_array, array_index);

    double max_fare = max(trip_fare_array, array_index);
    double min_fare = min(trip_fare_array, array_index);
    double avg_fare = average(trip_fare_array, array_index);
    double mode_fare = mode(trip_fare_array, array_index);

    double max_tip = max(trip_tip_array, array_index);
    double min_tip = min(trip_tip_array, array_index);
    double avg_tip = average(trip_tip_array, array_index);
    double mode_tip = mode(trip_tip_array, array_index);

    cout << "Number of trips: " << array_index << endl;
    cout << "Number of trips with invalid data: " << invalid << endl;
    cout << "Duration: " << "max " << max_min << " min " << min_min << " avg " << avg_min << " mode " << mode_min << endl;
    cout << "Distance: " << "max " << max_miles << " min " << min_miles << " avg " << avg_miles << " mode " << mode_miles << endl;
    cout << "Fare: " << "max " << max_fare << " min " << min_fare << " avg " << avg_fare << " mode " << mode_fare << endl;
    cout << "Tip: " << "max " << max_tip << " min " << min_tip << " avg " << avg_tip << " mode " << mode_tip << endl;
    cout << "Length of longest sequence without tips: " << length_longest_seq_zeros(trip_tip_array, array_index) << endl;

  return 0;
}
