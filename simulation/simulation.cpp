//====================================================================
// simulation.cpp
// Programming Assignment 1 : Sensor Simulation
// Author: Samuel Sikes
// Date: June 2016
// This program is entirely my own work
//====================================================================
#include "simulation.h"

//---------------------------------
//---------------------------------
//--------PRIVATE METHODS----------
//---------------------------------
//---------------------------------

//---------------------------------
//function: simulationDescription1()
//Displays a description of the
//program.
//---------------------------------
void simulation::simulationDescription1(){

    for (int i = 0; i < 60; i++)
        std::cout << "=";

    std::cout <<  "\n" << "|" << std::setw(52) <<
    "ENVIRONMENTAL SENSORS SIMULATION DEMONSTRATION" <<
    std::setw(7) << "|" << "\n" <<
    "|" << std::setw(46) <<
    "CS 307 -- Programming Assignment 1" <<
    std::setw(13) << "|" << "\n";

    for (int i = 0; i < 60; i++)
        std::cout << "=";
    std::cout << "\n\n";
};

void simulation::simulationDescription2(){

    std::cout << "\n\n\n" << "Beginning simulation run..." << "\n\n";
    for (int i = 0; i < 20; i++)
        std::cout << "=";
    std::cout << " Running simulation ";
    for (int i = 0; i < 20; i++)
        std::cout << "=";
    std::cout << "\n\n" << "Press Ctrl-c to terminate the simulation" << "\n\n";
    std::cout << "Press S to have display devices subscribe or unsubscribe to a" << "\n" <<
    std::setw(20) << "sensor data feed." << "\n\n";
}

void simulation::simulationDescription3() {

    for (int i = 0; i < 60; i++)
        std::cout << "=";
    std::cout << "\n\n";
}

//---------------------------------
//function: getFile()
//Prompts user to enter the name
//of the file that they want parsed.
//---------------------------------
void simulation::getFile(){

    char fileName[64];
    std::cout << "Please enter the name of the simulation data file then press Enter: ";
    std::cin >> fileName;

    //pass user's file to data parser
    this->dataParserPtr->initDataParser(fileName);
};

//---------------------------------
//function: buildDevices()
//Gets the number of sensor and
//display devices to create and
//passes those counts to the create
//functions for both displays and
//sensors. Then, deletes instance of
//data parser.
//---------------------------------
void simulation::buildDevices(){

    int air = 0, water = 0, earth = 0;

    //get air, earth and water sensor counts
    this->dataParserPtr->getSensorCounts(&earth, &air, &water);

    //create different sensors
    this->createAirSensors(air);
    this->createWaterSensors(water);
    this->createEarthSensors(earth);

    //create displays
    this->createDisplays();

    //link devices
    if(!sensorMountPtr->linkSensorsToDisplays())
        std::cout << "\n" << "Linking Sensors To Displays FAILED" << "\n";
};

//---------------------------------
//function: createDisplays()
//Creates the appropriate number of
//displays and passes each display
//to display's setDisplay() method
//---------------------------------
void simulation::createDisplays(){

    int count = this->dataParserPtr->getDisplayCount();

    for(int i=0; i < count; i++){

        //create display class instance
        display* displayPtr = this->SDFptr->createDisplayInstance();

        //create display node instance
        displayNode* displayNodePtr = new displayNode;

        //print message if parsing fails
        if(!this->dataParserPtr->getDisplayData(displayNodePtr->type,displayNodePtr->IDs,&displayNodePtr->IDCount))
            cout << "\n" << "Parsing for Display " << i << " failed" << "\n";

        else {

            //link display node to display class
            displayPtr->setDisplay(displayNodePtr);
            this->vDisplays->push_back(displayPtr);

            //link display class to sensor mount
            this->sensorMountPtr->attachDisplay(displayPtr);
        }
    }
};

//---------------------------------
//function: createAirSensors()
//---------------------------------
void simulation::createAirSensors(int& airCtr) {

    //if there are air sensors
    if (airCtr != 0) {

        //swap to air sensor factory
        this->ASFptr = airSensorFactory::getInstance();

        for (int i = 0; i < airCtr; i++) {

            //create sensorNode instance
            sensorNode *sensorNodePtr = new sensorNode;
            strcpy(sensorNodePtr->type, "Air");

            //print message if parsing fails
            if (!this->dataParserPtr->getSensorData(sensorNodePtr->type, sensorNodePtr->material,
            &sensorNodePtr->ID, sensorNodePtr->units, &sensorNodePtr->minVal, &sensorNodePtr->maxVal))
                cout << "\n" << "Parsing for Sensor " << i << " failed" << "\n";

            //initialize data
            sensorNodePtr->sensorData = 0;

            //create air sensor
            this->sensorTypePtr = this->ASFptr->createSensorInstance();
            this->sensorTypePtr->setSensor(sensorNodePtr);
            this->vSensors->push_back(this->sensorTypePtr);

            //attach sensor to sensor mount
            sensorMountPtr->attachSensor(this->sensorTypePtr);
        }
    }
}

//---------------------------------
//function: createWaterSensors()
//---------------------------------
void simulation::createWaterSensors(int& waterCtr) {

    //if there are water sensors
    if (waterCtr != 0) {

        //swap to water sensor factory
        this->ASFptr = waterSensorFactory::getInstance();

        for (int i = 0; i < waterCtr; i++) {

            //create sensorNode instance
            sensorNode *sensorNodePtr = new sensorNode;
            strcpy(sensorNodePtr->type, "Water");

            //print message if parsing fails
            if (!this->dataParserPtr->getSensorData(sensorNodePtr->type, sensorNodePtr->material,
            &sensorNodePtr->ID, sensorNodePtr->units, &sensorNodePtr->minVal, &sensorNodePtr->maxVal))
                cout << "\n" << "Parsing for Sensor " << i << " failed" << "\n";

            //initialize data
            sensorNodePtr->sensorData = 0;

            //create water sensor
            this->sensorTypePtr = this->ASFptr->createSensorInstance();
            this->sensorTypePtr->setSensor(sensorNodePtr);
            this->vSensors->push_back(this->sensorTypePtr);

            //attach sensor to sensor mount
            sensorMountPtr->attachSensor(this->sensorTypePtr);
        }
    }
}

//---------------------------------
//function: createEarthSensors()
//---------------------------------
void simulation::createEarthSensors(int& earthCtr) {

    //if there are earth sensors
    if (earthCtr != 0) {

        //swap to earth sensor factory
        this->ASFptr = earthSensorFactory::getInstance();

        for (int i = 0; i < earthCtr; i++) {

            //create sensorNode instance
            sensorNode *sensorNodePtr = new sensorNode;
            strcpy(sensorNodePtr->type, "Earth");

            //print message if parsing fails
            if (!this->dataParserPtr->getSensorData(sensorNodePtr->type, sensorNodePtr->material,
            &sensorNodePtr->ID, sensorNodePtr->units, &sensorNodePtr->minVal, &sensorNodePtr->maxVal))
                cout << "\n" << "Parsing for Sensor " << i << " failed" << "\n";

            //initialize data
            sensorNodePtr->sensorData = 0;

            //create earth sensor
            this->sensorTypePtr = this->ASFptr->createSensorInstance();
            this->sensorTypePtr->setSensor(sensorNodePtr);
            this->vSensors->push_back(this->sensorTypePtr);

            //attach sensor to sensor mount
            sensorMountPtr->attachSensor(this->sensorTypePtr);
        }
    }
}

//---------------------------------
//function: updateSensors()
//---------------------------------
void simulation::updateSensors() {

    for(unsigned long i = 0; i < this->vSensors->size(); i++)
        vSensors->at(i)->updateSensor();
}

//---------------------------------
//---------------------------------
//--------PUBLIC METHODS-----------
//---------------------------------
//---------------------------------

//---------------------------------
//function: simulation()
//dynamically creates instances of
//sensor, display, and sensor mount
//---------------------------------
simulation::simulation(){

    //create singleton of air sensor factory
    this->ASFptr = airSensorFactory::getInstance();
    //create singleton of water sensor factory
    this->ASFptr = waterSensorFactory::getInstance();
    //create singleton of earth sensor factory
    this->ASFptr = earthSensorFactory::getInstance();
    //create singleton of data parser
    this->dataParserPtr = EnviroSimDataParser::getInstance();
    //create singleton of simple display factory
    this->SDFptr = simpleDisplayFactory::getInstance();

    this->vSensors = new std::vector<sensorType* >;
    this->vDisplays = new std::vector<display* >;
    sensorMountPtr = new sensorMount;
};

//---------------------------------
//function: ~simulation()
//deallocates memory for: display,
//sensor, and sensor mount
//sets all private pointers to NULL
//---------------------------------
simulation::~simulation(){

    delete this->vDisplays;
    delete this->vSensors;
    delete sensorMountPtr; sensorMountPtr = NULL;
};

//---------------------------------
//function: runSimulation()
//calls appropriate simulation
//methods. Then, generates sensor
//data and displays it every 5
//seconds
//---------------------------------
void simulation::runSimulation() {

    this->simulationDescription1();
    this->getFile();
    this->buildDevices();
    this->sensorMountPtr->displayConnectedDevices();

    this->simulationDescription2();

    while(true){
        usleep(5000000);

        this->simulationDescription3();

        this->updateSensors();

        for(unsigned long i = 0; i < this->vDisplays->size(); i++) {
            //this->vDisplays->at(i)->displayData();
            //this->vDisplays->at(i)->notifyObservers();

            //Call display fctn to print sensor ID selection
            std::cout << i+1 << ". Device " <<
            this->vDisplays->at(i)->relayDisplayData()->type;
            this->vDisplays->at(i)->displayMonitoredSensors();
        }
        //print sub / un-sub message
        std::cout << "To subscribe/unsubscribe enter the device number (1-6)" << "\n" <<
        std::setw(64) << "a space, then a sensor ID for that device, then press [Enter]";


            //UPDATE OBSERVERS STATEMENT NEEDED HERE

        std::cout << "\n\n\n";

    }
};
