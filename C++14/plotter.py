import csv, os
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec

class Reader:
    def __init__(self, file_name):
        self.file_name = file_name + ".csv"
    
    def read(self):
        self.reader = csv.reader(open(self.file_name, "r"), delimiter = ",")
        data = np.array(list(self.reader)).astype("float")
        return data
    
    def __del__(self):
        pass

if __name__ == "__main__":
    os.system("clear")
    print("Python3.- is currently processing the plots ...")
    
    # Read input data
    input_reader = Reader('input_data')
    inputs = input_reader.read()
    pop_size = inputs[0]
    iterations = inputs[1]
    dim = inputs[2]
    acceptance_probability = inputs[3]
    
    # Read funval_hist
    funval_his_read = Reader('funval_history')
    funval_his = funval_his_read.read()

    # Read limits history
    limits_his_read = Reader('limits_history')
    limits_his = limits_his_read.read()
    
    # Plotting the figures
    plt.close('all')
    fig = plt.figure()
    fig.set_size_inches(4.5, dim * 2)
    plt.subplot(dim +1, 1, 1)
    plt.semilogx(np.arange(funval_his.size), funval_his)
    plt.xlabel("Iterations")
    plt.ylabel("The objective function evaluation")
    plt.title("The convergance curve")
    plt.xlim([1, funval_his.size])
    plt.grid()
    plt.subplots_adjust(hspace = 1)
    for i in range(1, np.int(dim) + 1):
        plt.subplot(dim +1, 1, i+1)
        plt.semilogx(np.arange(funval_his.size),\
                     limits_his[:, 2*(i-1)], '-b',  linewidth = 0.5)
        plt.semilogx(np.arange(funval_his.size),\
                     limits_his[:, 2*i-1], '-g', linewidth = 0.5)
        
        if i == 1:
            plt.xlabel("Iterations")
            plt.ylabel("The limits value")
            plt.title("The bounding limits evaluation")

        plt.xlim([1, funval_his.size])
        plt.grid()
        plt.fill_between(np.arange(funval_his.size)\
                         , limits_his[:, 2*(i-1)], limits_his[:, 2*i-1]\
                         , facecolor='lightgray')
    plt.savefig('results.pdf', bbox_inches='tight')
    plt.savefig('results.pdf')
    plt.show()