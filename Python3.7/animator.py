# This class is used to animate the solutions in 3D space

from benchmarks import *
from main_algorithm import *
import os

class Animator:
    def __init__(self, obj, population_hist, iterations, pop_size, step_size):
        if obj.dim != 2:
            raise Exception("Please make sure that the algorithm has only 2 dimentions to be visualized in the right way.")
        self.obj = obj
        self.population_hist = population_hist
        self.iterations = iterations
        self.pop_size = pop_size
        self.step_size = step_size
        self.cwd = os.getcwd() + "/Figures"
    
    def animate(self):
        for i in range(self.iterations):
            obj.plot(step = self.step_size,\
                     Xpoints = self.population_hist[i * self.pop_size : (i+1) * self.pop_size, 0] ,\
                     Ypoints = self.population_hist[i * self.pop_size : (i+1) * self.pop_size, 1] ,\
                     name = "Itr" + str(i))
    
    def save_video(self):
        # To make a video from the png images we have created
        # It works only for linux os
        os.system('ffmpeg -r 1 -i "{}"/Itr%01d.png -vcodec mpeg4 -y animation.mp4'.format(self.cwd))
    
    def __str__(self):\
        pass

if __name__ == "__main__":
    os.system('clear')
    
    # ************* This is just a repetion -test- *************
    iterations  = 50
    pop_size = 30
    acceptance_propability = 0.95
    assign_sampling_method = 2
    dim = 2
    step = 10e-10
    objective_option = 1
    if   objective_option == 1: obj = Schwefel(dim, step)
    elif objective_option == 2: obj = Rastrigin(dim, step)
    elif objective_option == 3: obj = Ackley(dim, step)
    elif objective_option == 4: obj = Sphere(dim, step)
    elif objective_option == 5: obj = XinSheYang(dim, step)
    elif objective_option == 6: obj = XinSheYang2(dim, step)
    elif objective_option == 7: obj = XinSheYang4(dim, step)
    elif objective_option == 8: obj = Quartic(dim, step)
    elif objective_option == 9: obj = Michalewicz(dim, step)
    elif objective_option == 10: obj = Rosenbrock(dim, step)
    elif objective_option == 11: obj = Easom(dim, step) # only 2D
    elif objective_option == 12: obj = Griewank(dim, step)
    else: raise Exception('Please choose a valid objective function')    
    if   assign_sampling_method == 1: sampling_method = 'LHS'
    elif assign_sampling_method == 2: sampling_method = 'MonteCarlo'
    else: raise Exception('Please choose a valid sampling method [1] or [2].')
    algo_test = Algorithm(iterations, pop_size, acceptance_propability, sampling_method, obj)
    best_solution, pop_hist = algo_test.run()
    print("The best solution obtained is: ", best_solution)
    # ************* This is just a repetion -test- *************
    
    print("Please wait .. saving animation.")
    
    # Test animator
    step_size = 1
    test_animator = Animator(obj, pop_hist, iterations, pop_size, step_size)
    test_animator.animate()
    test_animator.save_video() # Linux OS only (otherwise it will not work)
