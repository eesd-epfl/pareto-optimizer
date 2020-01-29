"""
This file has been written by Mahmoud S. Shaqfa
To test the behaviour of the new algorithm
It should be smart and fast.
Supervisor Prof. K. Beyer
"""

def clear_all():
    # Clear all the memory before start
    import copy
    instances = copy.copy(globals())
    for ins in instances:
        if ins[0] == '_': continue
    del globals()[ins]

clear_all()

import os, sys, copy, time, random, subprocess
import numpy as np
import numpy.matlib
import pyDOE
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from benchmarks import *
from animator import *

class LHSSampler:
    # This class is specialized in generating random matricies
    # LHS sampling
    def __init__(self, dim, pop_size):
        self.dim = dim
        self.pop_size = pop_size
    
    def _gen_random(self):
        np.random.seed() # Change the time seed
        random_pop = pyDOE.lhs(n = self.dim\
                                    , criterion = 'm'\
                                    , samples = self.pop_size)
        return random_pop

class MonteCarloSampler:
    # This class is specialized in generating random matricies
    # MonteCarlo sampling
    def __init__(self, dim, pop_size):
        self.dim = dim
        self.pop_size = pop_size
    
    def _gen_random(self):
        np.random.seed() # Change the time seed
        random_pop = np.random.rand(self.pop_size, self.dim)
        return random_pop

class Algorithm:
    """
    This to simulate the test of the LHS solver that M. Shaqfa Proposed
    """
    
    def __init__(self, iterations, pop_size, acceptance_rate,
                 sampling_method, objective_function, plot = True, history = True):
        #! iterations: the size of the main population
        #! pop_size: the size of the sub-population
        #! sampling_method = 'LHS' or 'MonteCarlo'
        #! acceptance_rate: the probability of accepting a solution in the normal range
        #! LB: is the lower bound of the optimization problem
        #! UB: is the upper bound of the optimization problem
        #! reduced_LB: the reduced lower-bound in the current domain
        #! reduced_UB: the reduced upper-bound in the current domain
        #! objective_function: the objective function instance
        #! funval: the objective function evaluation f(x)
        #! dim: the size of the optimization problem (dimensions)
        
        self.acceptance_rate = acceptance_rate
        self.iterations = iterations
        self.pop_size = pop_size
        self.objective_function = objective_function
        self.LB, self.UB, self.steps =  objective_function.get_bounds()
        self.dim = objective_function.dim
        self.main_funval = np.zeros([iterations, 1])
        self.funval = np.zeros([pop_size, 1])
        self.population = np.zeros([pop_size, self.dim])
        self.funval_his = np.zeros([iterations + 1, 1])
        
        if history:
            self.solutions_vectors_his = np.zeros([(iterations+1)\
                                               * pop_size, self.dim])
        self.reduced_LB = 0.
        self.reduced_UB = 0.
        self.sampling_method = sampling_method
        
        # Initalize a sampling method
        if self.sampling_method == 'LHS':
            self.sampler = LHSSampler(self.dim, self.pop_size)
        elif self.sampling_method == 'MonteCarlo':
            self.sampler = MonteCarloSampler(self.dim, self.pop_size)
        else:
            raise Exception('{} samplinmg method is not defined. Please choose "LHS" or "MonteCarlo"'.format(self.sampling_method))
        
        self.limits_his = np.zeros([iterations + 1, self.dim * 2])
        
        self.plot = plot
        self.history = history
    
    def run(self):
        """
        To run the analysis of the optimizer
        """
        t1 = time.time()
        
        # The initial population sampling
        LB_mat = np.matlib.repmat(self.LB, self.pop_size, 1)
        UB_mat = np.matlib.repmat(self.UB, self.pop_size, 1)
        steps_mat = np.matlib.repmat(self.steps, self.pop_size, 1)
        self.random_pop = self.sampler._gen_random()
        self.population = np.round((LB_mat + self.random_pop * \
                                    (UB_mat - LB_mat)) / steps_mat) * steps_mat
        del LB_mat, UB_mat, steps_mat
        
        # Evaluate the initial solutions
        for i in range(self.pop_size):
            self.funval[i, 0] = self.objective_function.calculate(self.population[i, :])
        
        # Find the best initial solution and store it
        best_index = np.argmin(self.funval)
        self.funval_his[0, 0] = self.funval[best_index, 0]
        best_sol = copy.copy(self.population[best_index, :])
        new_solution = True
        
        # Hold population memory
        if self.history:
            self.solutions_vectors_his[0:self.pop_size, :] = self.population
        
        for i in range(1, self.iterations+1):
            self.random_pop = self.sampler._gen_random()
            
            for j in range(self.pop_size):
                for k in range(self.dim):
                    
                    # Update the ranges
                    if new_solution:
                        # The deviation is positive dynamic real number
                        deviation = abs(0.5 * (1. - self.acceptance_rate)\
                         * (self.UB[0, k] - self.LB[0, k])) \
                         * (1 - (i/(self.iterations )))
                    
                    self.reduced_LB = best_sol[k] - deviation
                    self.reduced_LB = np.amax([self.reduced_LB , self.LB[0, k]])
                    
                    self.reduced_UB = self.reduced_LB + deviation * 2.
                    self.reduced_UB = np.amin([self.reduced_UB, self.UB[0, k]])
                    
                    self.limits_his[i, k * 2] = self.reduced_LB
                    self.limits_his[i, k * 2 + 1] = self.reduced_UB
                    
                    # Choose new solution
                    if np.random.rand() <= self.acceptance_rate:
                        # choose a solution from the prominent domain
                        self.population[j, k] = self.reduced_LB + self.random_pop[j, k]\
                            * (self.reduced_UB - self.reduced_LB)
                    else:
                        # choose a solution from the overall domain
                        self.population[j, k] = self.LB[0, k] + self.random_pop[j, k]\
                            * (self.UB[0, k] - self.LB[0, k])
                    
                    # Round for the step size
                    self.population[j, :] = np.round(self.population[j, :] / self.steps) * self.steps
                # Evaluate the solution
                self.funval[j] = self.objective_function.calculate(self.population[j, :])

            # Hold population memory
            if self.history:
                self.solutions_vectors_his[i * self.pop_size: (i + 1) * self.pop_size, :] = self.population
            
            # Find the current best solution
            if np.amin(self.funval) <= self.funval_his[i - 1]:
                best_index = np.argmin(self.funval)
                self.funval_his[i] = self.funval[best_index, 0]
                best_sol = copy.copy(self.population[best_index, :])
                new_solution = True
            else:
                self.funval_his[i] = self.funval_his[i - 1]
                new_solution = False
            
            print("Iteration number {} and best fittness is: {}"\
                  .format(i, np.amin(self.funval_his[i])))
        
        subprocess.call(['spd-say', '"The algorithm has finished"'])
        
        print('\nThe elapsed time is {} min\n'.format((time.time() - t1) / 60.))
        
        if self.plot:
            plt.close('all')
            # 2D Drawing
            fig = plt.figure()
            fig.set_size_inches(4.5, self.dim * 2)
            
            plt.subplot(self.dim +1, 1, 1)
            plt.semilogx(np.arange(self.funval_his.size), self.funval_his)
            plt.xlabel("Iterations")
            plt.ylabel("The objective function evaluation")
            plt.title("The convergance curve")
            plt.xlim([1, self.funval_his.size])
            plt.grid()
            plt.subplots_adjust(hspace = 1)
            
            for i in range(1, self.dim + 1):
                plt.subplot(self.dim +1, 1, i+1)
                plt.semilogx(np.arange(self.funval_his.size),\
                             self.limits_his[:, 2*(i-1)], '-b',  linewidth = 0.5)
                plt.semilogx(np.arange(self.funval_his.size),\
                             self.limits_his[:, 2*i-1], '-g', linewidth = 0.5)
                plt.semilogx(np.arange(self.funval_his.size)\
                         , self.objective_function.exact * np.ones([self.funval_his.size, 1])\
                         ,'r--', linewidth = 0.5)
                if i == 1:
                    plt.xlabel("Iterations")
                    plt.ylabel("The limits value")
                    plt.title("The bounding limits evaluation")
                plt.xlim([1, self.funval_his.size])
                plt.grid()
                plt.fill_between(np.arange(self.funval_his.size)\
                                 , self.limits_his[:, 2*(i-1)], self.limits_his[:, 2*i-1]\
                                 , facecolor='lightgray')
            plt.savefig('results.pdf', bbox_inches='tight')
            plt.savefig('results.pdf')
            plt.show()
        
        if self.history: return best_sol, self.solutions_vectors_his
        else: return best_sol, []
    
    def plot_history(self):
        pass
    
    def __str__(self):
        output = "\nThis solver consists of {} iterations and {} sub iterations.\n"\
            .format(self.iterations, self.pop_size)
        return output

if __name__ == "__main__":
    # The main function callout
    os.system("clear")
    sys.modules.update()
    
    # ------------- Objective Function Options --------------
    iterations = 500
    pop_size = 30
    acceptance_propability = 0.95
    
    # [1] -> 'LHS' (slow option), [2] -> 'MonteCarlo' (fast option)
    assign_sampling_method = 1
    
    dim = 30
    objective_option = 1
    step = 10e-10
    
    export_2D_animtaions = True
    animation_step_size = 1.
    
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
    
    algo_test = Algorithm(iterations, pop_size,\
                          acceptance_propability, sampling_method, obj, plot = True)
    best_solution, pop_hist = algo_test.run()
    
    print("The best solution obtained is: ", best_solution)
    
    if export_2D_animtaions:
        animations = Animator(obj = obj, population_hist = pop_hist, iterations = iterations,
                              pop_size = pop_size, step_size = animation_step_size)
        animations.animate()
        animations.save_video()
    
    # The End XD