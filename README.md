# Scintillator Efficiency Monte Carlo Simulation

This repository contains a Geant4-based Monte Carlo simulation designed to model a scintillation detector and evaluate its detection efficiency. 

## Detector Geometry
The simulation builds a detailed, realistic model of a standard scintillator setup:
* **Crystal:** A 1"x1" NaI(Tl) (Sodium Iodide) crystal.
* **Reflector & Housing:** The crystal is surrounded by an MgO (Magnesium Oxide) powder reflector and enclosed within an Aluminum housing with a diameter of 31.5 mm and a wall thickness of 1.57 mm[cite: 8].
* **Source Package:** The radioactive source is simulated inside a standard Plexiglass button.
* **Adjustable Distance:** The distance between the source and the detector can be dynamically adjusted using the custom macro command `/det/setDistance`.

## Simulation Execution 
The repository includes macro files designed to automate the data collection process across different experimental setups:
* **Energy Scans:** Macros can automatically sweep through multiple incident gamma energies (e.g., from 205 keV up to 511 keV) at a fixed detector distance (e.g., 35 cm) with high statistics (10,000,000 events per run)[cite: 9].
* **Distance Scans:** The distance can be iteratively modified during a run sequence using the `/det/setDistance` command followed by `/run/reinitializeGeometry`, allowing for distance-dependent efficiency curves without recompiling the code[cite: 10].

## Output
* **Data Saving:** At the end of each simulated event, if the deposited energy is greater than zero, the Event ID and the total Energy Deposited are saved into an Ntuple.
* **Dynamic Output Generation:** Output CSV files are dynamically named within the macro files using the `/analysis/setFileName` command (e.g., `r2_35cm_444keV` or `r1_17`), ensuring organized and trackable datasets for post-processing[cite: 9, 10].

## Requirements
* Geant4 toolkit.
* C++ compiler
