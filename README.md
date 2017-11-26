# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---


## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

## Project Instructions 

Note: regardless of the changes you make, your project must be buildable using
cmake and make!


## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.


## Reflection

Describe the effect each of the P, I, D components had in your implementation.
 * The first implementation I noticed that the car was doing a lot of zig zag which 
   hinted me (from video modules) to reduce the Proportional gain and increase the
   Differential and Integral to have the car adjust. This worked fine after a couple of 
   changes to the values and it clearly showed me the how each gain had an effect on 
   the steering.
   
   As I understood from the videos, the proportional gain tends to overshoot, the Differential
   converges to a value close to the reference but never actually reaches it and the 
   Integral gain converges to the reference value after some time. The overshoot of the 
   proportional gain was noticed when the car zig zag abruptly. The increase in the differential
   help a little but the one that had more influence on the smoothing steering was the 
   Integral gain. This helped me gain an intuitive understanding of the PID controller.
   
Describe how the final hyperparameters were chosen.
 * To chose the final hyperparameters I used Twiddle because it seem easier and I 
 already had the pseudocode for the algorithm from the class modules. This helped the 
 values converged quickly and the car steered much better than when I had tested it by 
 manually tuning the parameters. 