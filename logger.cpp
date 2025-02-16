#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <unistd.h>  // For sleep() function
#include <sstream>
#include <fstream>

using namespace std;

// Function to read the temperature from the DS18B20 sensor
float readDS18B20() {
    // Path to the temperature sensor's data file
    string sensorPath = "/sys/bus/w1/devices/28-xxxxxxxxxxxx/w1_slave"; // Replace with your device path

    // Open the sensor data file
    ifstream sensorFile(sensorPath);

    if (!sensorFile.is_open()) {
        cerr << "Error opening sensor data file!" << endl;
        return -1;  // Return error code if file can't be opened
    }

    string line;
    string rawData;
    float temperature = 0.0;

    // Read the sensor data lines
    while (getline(sensorFile, line)) {
        rawData += line;
    }

    // Check if the sensor reading is valid
    if (rawData.find("YES") != string::npos) {
        size_t pos = rawData.find("t=");  // Find the position of the temperature value
        if (pos != string::npos) {
            string tempStr = rawData.substr(pos + 2);  // Extract the temperature string
            temperature = atof(tempStr.c_str()) / 1000.0;  // Convert to Celsius
        }
    }

    return temperature;
}

// Function to log data to the CSV file
void logTemperature(float temperature) {
    // Open a file in write mode
    ofstream outFile("temperature_log.csv", ios::app); // Open in append mode to preserve previous data

    // Check if file opened successfully
    if (!outFile) {
        cerr << "Error opening file!" << endl;
        return;
    }

    // Writing CSV headers if the file is empty (i.e., first run)
    if (outFile.tellp() == 0) {
        outFile << "Timestamp,Temperature" << endl;
    }

    // Get current timestamp
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std:stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%dT%H:%M:%SZ");
    
    // Write the timestamp and temperature to the CSV file
    outFile << ss.str() << "," << temperature << endl;

    // Close the file
    outFile.close();
}

int main() {
    while (true) {
        // Get the actual temperature reading from the sensor
        float temperature = readDS18B20();

        // If the temperature is valid, log it
        if (temperature > -100) {
            logTemperature(temperature);
        } else {
            cerr << "Failed to read temperature!" << endl;
        }

        // Sleep for 10 minutes (600 seconds)
        sleep(600);  // sleep() function takes time in seconds
    }

    return 0;
}

