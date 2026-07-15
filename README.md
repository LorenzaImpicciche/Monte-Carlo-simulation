# Scintillator Efficiency Monte Carlo Simulation

This repository contains a Geant4-based Monte Carlo simulation designed to model a scintillation detector and evaluate its detection efficiency. 

## Detector Geometry
The simulation builds a detailed, realistic model of a standard scintillator setup:
* **Crystal:** A 1"x1" NaI(Tl) crystal.
* **Reflector & Housing:** The crystal is surrounded by an MgO powder reflector and enclosed within an Aluminum housing.
* **Source Package:** The radioactive source is simulated inside a standard Plexiglass button.
* **Adjustable Distance:** The distance between the source and the detector can be dynamically adjusted.

## Simulation Execution 
The repository includes macro files designed to automate the data collection process across different experimental setups:
* **Energy Scans:** Macros can automatically sweep through multiple incident gamma energies at a fixed detector distance with high statistics (10,000,000 events per run).
* **Distance Scans:** The distance can be iteratively modified during a run sequence using the `/det/setDistance` command followed by `/run/reinitializeGeometry`, allowing for distance-dependent efficiency curves without recompiling the code.

## Output
* **Data Saving:** At the end of each simulated event, if the deposited energy is greater than zero, the Event ID and the total Energy Deposited are saved into an Ntuple.
* **Dynamic Output Generation:** Output CSV files are dynamically named within the macro files.
## Requirements
* Geant4 toolkit.
* C++ compiler
