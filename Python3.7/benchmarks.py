import numpy as np
import numpy.matlib 
import random, copy, os
import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d
from matplotlib import ticker, cm
from matplotlib.ticker import MaxNLocator

class Objective:
    dim = 0;
    exact = 0;
    def __init__(self, dim, step):
        self.dim = dim
        self.step = step
        self.basic_LB = np.ones((1, dim))
        self.basic_UB = copy.copy(self.basic_LB)
        self.steps = copy.copy(self.basic_LB) * self.step
        try:
            os.mkdir("Figures")
        except:
            pass
        self.cwd = os.getcwd()
    
    def get_bounds(self):
        pass
    
    def calculate(self, design_varaible):
        pass
    
    def test(self):
        pass
    
    def plot(self, step = 1., Xpoints = [], Ypoints = [], name = ""):
        pass
    
    def __str__(self):
        return "Just an abstract objective function"

class Schwefel(Objective):
    """
    The reference for this function has been retrieved from:
    http://benchmarkfcns.xyz/benchmarkfcns/schwefelfcn.html
    https://www.sfu.ca/~ssurjano/schwef.html
    """
    exact = 420.9687
    def __init__(self, dim, step):
        super().__init__(dim, step)
        
    def get_bounds(self):
        self.LB =  -500. * self.basic_LB
        self.UB =   500. * self.basic_UB
        return self.LB, self.UB, self.steps
    
    def calculate(self, design_varaible):
        return (418.9829 * self.dim - (np.sum(design_varaible * np.sin(np.sqrt(np.abs(design_varaible))))))
    
    def test(self):
        ans = self.calculate(np.ones((1, self.dim)) * 420.9687)
        print("The exact answer is {}".format(ans))
        return ans
    
    def plot(self, step = 1., Xpoints = [], Ypoints = [], name = ""):
        def f(x, y):
            return 418.9829 * 2. - x * np.sin(np.sqrt(np.abs(x))) - y * np.sin(np.sqrt(np.abs(y)))
        x = np.linspace(-500., 500., (500. - -500.)/step)
        y = copy.copy(x)
        X, Y = np.meshgrid(x, y)
        Z = f(X, Y)

        fig = plt.figure()
        cp = plt.contourf(X, Y, Z, cmap=cm.GnBu)
        cp2 = plt.contour(X, Y, Z)
        plt.colorbar(cp)
        plt.xlabel('x1')
        plt.ylabel('x2')
        plt.xlim([-500., 500.])
        plt.ylim([-500., 500.])
        if Xpoints != [] and Ypoints != []:
            plt.scatter(Xpoints, Ypoints, alpha=0.5, marker = '^', c = 'black')
        plt.title('Schwefel - ' + name)
        if name == "":
            name = "Fig"
        current_folder = self.cwd +'/Figures/' + name
        print("Saving .. ", current_folder)
        plt.savefig(current_folder)
        plt.close()
    
    def __str__(self):
        output = "\nThis is the Schwefel function with {} dimension\n".format(self.dim)
        return output

class Sphere(Objective):
    exact = 0.
    
    def __init__(self, dim, step):
        super().__init__(dim, step)
    
    def get_bounds(self):
        self.LB = -5.12 * self.basic_LB
        self.UB =  5.21 * self.basic_UB
        return self.LB, self.UB, self.steps

    def calculate(self, design_varaible):
        return np.sum(design_varaible ** 2.)
    
    def test(self):
        ans = self.calculate(np.ones((1, self.dim)) * 0.0)
        print("The exact answer is {}".format(ans))
        return ans
    
    def plot(self, step = 1., Xpoints = [], Ypoints = [], name = ""):
        def f(x, y):
            return x**2. + y**2.
        x = np.linspace(-5.12, 5.12, (5.12 - -5.12)/step)
        y = copy.copy(x)
        X, Y = np.meshgrid(x, y)
        Z = f(X, Y)
        
        fig = plt.figure()
        cp = plt.contourf(X, Y, Z, cmap=cm.GnBu)
        cp2 = plt.contour(X, Y, Z)
        plt.colorbar(cp)
        plt.xlabel('x1')
        plt.ylabel('x2')
        plt.xlim([-5.12, 5.12])
        plt.ylim([-5.12, 5.12])
        if Xpoints != [] and Ypoints != []:
            plt.scatter(Xpoints, Ypoints, alpha=0.5, marker = '^', c = 'black')
        plt.title('Sphere - ' + name)
        if name == "":
            name = "Fig"
        current_folder = self.cwd +'/Figures/' + name
        print("Saving .. ", current_folder)
        plt.savefig(current_folder)
        plt.close()
    
    def __str__(self):
        output = "\nThis is the Sphere function with {} dimension\n".format(self.dim)
        return output

class Ackley(Objective):
    exact = 0.
    
    def __init__(self, dim, step):
        super().__init__(dim, step)
    
    def get_bounds(self):
        self.LB = -32. * self.basic_LB
        self.UB =  32. * self.basic_UB
        return self.LB, self.UB, self.steps
    
    def calculate(self, design_varaible):
        return -20. * np.exp(-0.2 * np.sqrt(np.sum(design_varaible**2.)/self.dim))\
            - np.exp(np.sum(np.cos(2*np.pi * design_varaible))/self.dim) + 20. + np.exp(1)
    
    def test(self):
        ans = self.calculate(np.ones((1, self.dim)) * 0.0)
        print("The exact answer is {}".format(ans))
        return ans
    
    def plot(self, step = 1., Xpoints = [], Ypoints = [], name = ""):
        def f(x, y):
            return -20. * np.exp(-0.2 * np.sqrt(x**2. + y**2.)/self.dim)\
            - np.exp((np.cos(2*np.pi * x) + np.cos(2*np.pi * y))/self.dim) + 20. + np.exp(1)
        
        x = np.linspace(-32., 32., (32.- -32.)/step)
        y = copy.copy(x)
        X, Y = np.meshgrid(x, y)
        Z = f(X, Y)
        
        fig = plt.figure()
        cp = plt.contourf(X, Y, Z, cmap=cm.GnBu)
        cp2 = plt.contour(X, Y, Z)
        plt.colorbar(cp)
        plt.xlabel('x1')
        plt.ylabel('x2')
        plt.xlim([-32., 32.])
        plt.ylim([-32., 32.])
        if Xpoints != [] and Ypoints != []:
            plt.scatter(Xpoints, Ypoints, alpha=0.5, marker = '^', c = 'black')
        plt.title('Ackley - ' + name)
        if name == "":
            name = "Fig"
        current_folder = self.cwd + "/Figures/" + name
        print("Saving .. ", current_folder)
        plt.savefig(current_folder)
        plt.close()
    
    def __str__(self):
        output = "\nThis is the Ackley function with {} dimension\n".format(self.dim)
        return output

class Rastrigin(Objective):
    exact = 0.
    
    def __init__(self, dim, step):
        super().__init__(dim, step)
    
    def get_bounds(self):
        self.LB = -5.12 * self.basic_LB
        self.UB =  5.12 * self.basic_UB
        return self.LB, self.UB, self.steps

    def calculate(self, design_varaible):
        return 10. * self.dim + np.sum(design_varaible ** 2. - 10. * np.cos(2. * np.pi * design_varaible))
    
    def test(self):
        ans = self.calculate(np.ones((1, self.dim)) * 0.0)
        print("The exact answer is {}".format(ans))
        return ans
    
    def plot(self, step = 1., Xpoints = [], Ypoints = [], name = ""):
        def f(x, y):
            return 10. * self.dim + x ** 2. - 10. * np.cos(2. * np.pi * x) + y ** 2. - 10. * np.cos(2. * np.pi * y)
        
        x = np.linspace(-5.12, 5.12, (5.12- -5.12)/step)
        y = copy.copy(x)
        X, Y = np.meshgrid(x, y)
        Z = f(X, Y)
        
        fig = plt.figure()
        cp = plt.contourf(X, Y, Z, cmap=cm.GnBu)
        cp2 = plt.contour(X, Y, Z)
        plt.colorbar(cp)
        plt.xlabel('x1')
        plt.ylabel('x2')
        plt.xlim([-5.12, 5.12])
        plt.ylim([-5.12, 5.12])
        if Xpoints != [] and Ypoints != []:
            plt.scatter(Xpoints, Ypoints, alpha=0.5, marker = '^', c = 'black')
        plt.title('Rastrigin - ' + name)
        if name == "":
            name = "Fig"
        current_folder = self.cwd + "/Figures/" + name
        print("Saving .. ", current_folder)
        plt.savefig(current_folder)
        plt.close()        
    def __str__(self):
        output = "\nThis is the Rastrigin function with {} dimension\n".format(self.dim)
        return output

class XinSheYang(Objective):
    exact = 0.
    
    def __init__(self, dim, step):
        super().__init__(dim, step)
    
    def get_bounds(self):
        self.LB = -5. * self.basic_LB
        self.UB =  5. * self.basic_UB
        return self.LB, self.UB, self.steps

    def calculate(self, design_varaible):
        answer = 0.
        for i in range(design_varaible.size):
            answer += abs(design_varaible[i]**float(i)) * np.random.rand()
        return answer
    
    def test(self):
        ans = self.calculate(np.ones((1, self.dim)) * 0.0)
        print("The exact answer is {}".format(ans))
        return ans
    
    def plot(self, step = 1., Xpoints = [], Ypoints = [], name = ""):
        def f(x, y):
            return abs(x**float(1)) * np.random.rand() + abs(y**float(2)) * np.random.rand()
        
        x = np.linspace(-5., 5., (5.- -5.)/step)
        y = copy.copy(x)
        X, Y = np.meshgrid(x, y)
        Z = f(X, Y)
        
        fig = plt.figure()
        cp = plt.contourf(X, Y, Z, cmap=cm.GnBu)
        cp2 = plt.contour(X, Y, Z)
        plt.colorbar(cp)
        plt.xlabel('x1')
        plt.ylabel('x2')
        plt.xlim([-5, 5])
        plt.ylim([-5, 5])
        if Xpoints != [] and Ypoints != []:
            plt.scatter(Xpoints, Ypoints, alpha=0.5, marker = '^', c = 'black')
        plt.title('XinSheYang - ' +  name)
        if name == "":
            name = "Fig"
        current_folder = self.cwd + "/Figures/" + name
        print("Saving .. ", current_folder)
        plt.savefig(current_folder)
        plt.close()
    
    def __str__(self):
        output = "\nThis is the XinSheYang function with {} dimension\n".format(self.dim)
        return output

class XinSheYang2(Objective):
    exact = 0.
    
    def __init__(self, dim, step):
        super().__init__(dim, step)
    
    def get_bounds(self):
        self.LB = -np.pi * 2. * self.basic_LB
        self.UB =  np.pi * 2. * self.basic_UB
        return self.LB, self.UB, self.steps

    def calculate(self, design_varaible):
        return np.sum(np.sum(np.abs(design_varaible))) * np.exp(-1 * np.sum(np.sin(design_varaible**2.)))
    
    def test(self):
        ans = self.calculate(np.ones((1, self.dim)) * 0.0)
        print("The exact answer is {}".format(ans))
        return ans
    
    def plot(self, step = 1., Xpoints = [], Ypoints = [], name = ""):
        def f(x, y):
            return (np.abs(x)+np.abs(y)) * np.exp(-1 * (np.sin(x**2.) + np.sin(y**2.)))
        
        x = np.linspace(-2., 2., (2.- -2.)/step)
        y = copy.copy(x)
        X, Y = np.meshgrid(x, y)
        Z = f(X, Y)
        
        fig = plt.figure()
        cp = plt.contourf(X, Y, Z, cmap=cm.GnBu)
        cp2 = plt.contour(X, Y, Z)
        plt.colorbar(cp)
        plt.xlabel('x1')
        plt.ylabel('x2')
        plt.xlim([-2, 2])
        plt.ylim([-2, 2])
        if Xpoints != [] and Ypoints != []:
            plt.scatter(Xpoints, Ypoints, alpha=0.5, marker = '^', c = 'black')
        plt.title('XinSheYang2.0 - ' + name)
        if name == "":
            name = "Fig"
        current_folder = self.cwd + "/Figures/" + name
        print("Saving .. ", current_folder)
        plt.savefig(current_folder)
        plt.close()        
    def __str__(self):
        output = "\nThis is the XinSheYang2 function with {} dimension\n".format(self.dim)
        return output

class XinSheYang4(Objective):
    exact = -1.
    
    def __init__(self, dim, step):
        super().__init__(dim, step)
    
    def get_bounds(self):
        self.LB = -10. * self.basic_LB
        self.UB =  10. * self.basic_UB
        return self.LB, self.UB, self.steps

    def calculate(self, design_varaible):
        return (np.sum(np.sin(design_varaible)**2.) - np.exp(-np.sum(design_varaible**2.)))\
            * np.exp(-np.sum(np.sin(np.sqrt(np.abs(design_varaible)))**2.))
    
    def test(self):
        ans = self.calculate(np.ones((1, self.dim)) * 0.0)
        print("The exact answer is {}".format(ans))
        return ans
    
    def plot(self, step = 1., Xpoints = [], Ypoints = []):
        # Plot a 2D optimization problem (3D surface)
        line_grid = np.arange(-1., 1., step) * np.pi * 2
        x = np.zeros([line_grid.size, 2])
        z = np.arange(-1., 1., step) * 0.
        x[:, 0] = line_grid
        x[:, 1] = line_grid
        temp = XinSheYang4(2)
        for i in range(line_grid.size):
            z[i] = temp.calculate(x[i, :])
        plt.close('all')
        fig = plt.figure()
        plt.plot(x, z)
        plt.title('XinSheYang4.0 - ' + name)
        if name == "":
            name = "Fig"
        current_folder = self.cwd + "/Figures/" + name
        print("Saving .. ", current_folder)
        plt.savefig(current_folder)
        plt.close()        
    def __str__(self):
        output = "\nThis is the XinSheYang4 function with {} dimension\n".format(self.dim)
        return output

class Quartic(Objective):
    exact = 0.
    
    def __init__(self, dim, step):
        super().__init__(dim, step)
    
    def get_bounds(self):
        self.LB = -1.28 * self.basic_LB
        self.UB =  1.28 * self.basic_UB
        return self.LB, self.UB, self.steps

    def calculate(self, design_varaible):
        answer = 0.
        for i in range(self.dim): answer += float(i) * (design_varaible[i]**4.) + np.random.rand()
        return answer
    
    def test(self):
        ans = self.calculate(np.ones((1, self.dim)) * 0.0)
        print("The exact answer is {}".format(ans))
        return ans
    
    def plot(self, step = 1., Xpoints = [], Ypoints = [], name = ""):
        def f(x, y):
            return float(1) * (x**4.) + np.random.rand() + float(2) * (y**4.) + np.random.rand()
        
        x = np.linspace(-1.28, 1.28, (1.28- -1.28)/step)
        y = copy.copy(x)
        X, Y = np.meshgrid(x, y)
        Z = f(X, Y)
        
        fig = plt.figure()
        cp = plt.contourf(X, Y, Z, cmap=cm.GnBu)
        cp2 = plt.contour(X, Y, Z)
        plt.colorbar(cp)
        plt.xlabel('x1')
        plt.ylabel('x2')
        plt.xlim([-1.28, 1.28])
        plt.ylim([-1.28, 1.28])
        if Xpoints != [] and Ypoints != []:
            plt.scatter(Xpoints, Ypoints, alpha=0.5, marker = '^', c = 'black')
        plt.title('Quartic - ' + name)
        if name == "":
            name = "Fig"
        current_folder = self.cwd + "/Figures/" + name
        print("Saving .. ", current_folder)
        plt.savefig(current_folder)
        plt.close()
    
    def __str__(self):
        output = "\nThis is the Quartic function with {} dimension\n".format(self.dim)
        return output

class Michalewicz(Objective):
    exact = -9.66015 # d = 10
    #exact = -4.687658 # d = 5
    #exact = -1.8013 # d = 2
    # The first root should be 2.20 and the others 1.57
    
    def __init__(self, dim, step):
        super().__init__(dim, step)
        self.indcies = np.arange(1, self.dim+1)
    
    def get_bounds(self):
        self.LB = 0.0 * self.basic_LB
        self.UB = np.pi * self.basic_UB
        return self.LB, self.UB, self.steps
    
    def calculate(self, design_varaible):        
        return -np.sum(np.sin(design_varaible) * np.sin(design_varaible**2.\
                        * self.indcies / np.pi) ** (2.*10.))
    
    def test(self):
        ans = self.calculate(np.ones((1, self.dim)) * 0.0)
        print("The exact answer is {}".format(ans))
        return ans
    
    def plot(self, step = 1., Xpoints = [], Ypoints = [], name = ""):
        # Plot a 2D optimization problem (3D surface)
        line_grid = np.arange(-1., 1., step) * 1.28
        x = np.zeros([line_grid.size, 2])
        z = np.arange(-1., 1., step) * 0.
        x[:, 0] = line_grid
        x[:, 1] = line_grid
        temp = Michalewicz(2)
        for i in range(line_grid.size):
            z[i] = temp.calculate(x[i, :])
        plt.close('all')
        fig = plt.figure()
        plt.plot(x, z)
        plt.title('Michalwicz - ' + name)
        if name == "":
            name = "Fig"
        current_folder = self.cwd + "/Figures/" + name
        print("Saving .. ", current_folder)
        plt.savefig(current_folder)
        plt.close()        
    
    def __str__(self):
        output = "\nThis is the Michalewicz function with {} dimension\n".format(self.dim)
        return output

class Rosenbrock(Objective):
    exact = 1.0
    
    def __init__(self, dim, step):
        super().__init__(dim, step)
        self.indcies = np.arange(1, self.dim+1)
    
    def get_bounds(self):
        self.LB = -2.048 * self.basic_LB
        self.UB =  2.048 * self.basic_UB
        return self.LB, self.UB, self.steps
    
    def calculate(self, design_varaible):        
        answer = 0.
        for i in range(0, self.dim - 1):
            answer+= (100. * (design_varaible[i+1] - design_varaible[i]**2.)**2. \
                     + (design_varaible[i] - 1.)**2.)
        return answer
    
    def test(self):
        ans = self.calculate(np.ones((1, self.dim)) * 0.0)
        print("The exact answer is {}".format(ans))
        return ans
    
    def plot(self, step = 1., Xpoints = [], Ypoints = [], name = ""):
        def f(x, y):
            return (100. * (y - x**2.)**2. + (x - 1.)**2.)
        
        x = np.linspace(-2.048, 2.048, (2.048- -2.048)/step)
        y = copy.copy(x)
        X, Y = np.meshgrid(x, y)
        Z = f(X, Y)
        
        fig = plt.figure()
        cp = plt.contourf(X, Y, Z, cmap=cm.GnBu)
        cp2 = plt.contour(X, Y, Z)
        plt.colorbar(cp)
        plt.xlabel('x1')
        plt.ylabel('x2')
        plt.xlim([-2.048, 2.048])
        plt.ylim([-2.048, 2.048])
        if Xpoints != [] and Ypoints != []:
            plt.scatter(Xpoints, Ypoints, alpha=0.5, marker = '^', c = 'black')
        plt.title('Rosenbrock - ' + name)
        if name == "":
            name = "Fig"
        current_folder = self.cwd + "/Figures/" + name
        print("Saving .. ", current_folder)
        plt.savefig(current_folder)
        plt.close()
        
    def __str__(self):
        output = "\nThis is the Rosenbrock function with {} dimension\n".format(self.dim)
        return output

class Easom(Objective):
    exact = -1.0
    # Two dimentions only
    # the roots should be (pi, pi)
    
    def __init__(self, dim, step):
        super().__init__(dim, step)
        self.indcies = np.arange(1, self.dim+1)
    
    def get_bounds(self):
        self.LB = -100. * self.basic_LB
        self.UB =  100. * self.basic_UB
        return self.LB, self.UB, self.steps
    
    def calculate(self, design_varaible):        
        return -np.cos(design_varaible[0]) * np.cos(design_varaible[1])\
            * np.exp(-(design_varaible[0] - np.pi)**2. - (design_varaible[1] - np.pi)**2.)
    
    def test(self):
        ans = self.calculate(np.ones((1, self.dim)) * 0.0)
        print("The exact answer is {}".format(ans))
        return ans
    
    def plot(self, step = 1., Xpoints = [], Ypoints = [], name = ""):
        # Plot a 2D optimization problem (3D surface)
        line_grid = np.arange(-1., 1., step) * 2.048
        x = np.zeros([line_grid.size, 2])
        z = np.arange(-1., 1., step) * 0.
        x[:, 0] = line_grid
        x[:, 1] = line_grid
        temp = Easom(2)
        for i in range(line_grid.size):
            z[i] = temp.calculate(x[i, :])
        plt.close('all')
        fig = plt.figure()
        plt.plot(x, z)
        plt.title('Easom - ' + name)
        if name == "":
            name = "Fig"
        current_folder = self.cwd + "/Figures/" + name
        print("Saving .. ", current_folder)
        plt.savefig(current_folder)
        plt.close()
    
    def __str__(self):
        output = "\nThis is the Easom function with {} dimension\n".format(self.dim)
        return output

class Griewank(Objective):
    exact = 0.
    
    def __init__(self, dim, step):
        super().__init__(dim, step)
        self.indcies = np.arange(1, self.dim+1)
    
    def get_bounds(self):
        self.LB = -600. * self.basic_LB
        self.UB =  600. * self.basic_UB
        return self.LB, self.UB, self.steps
    
    def calculate(self, design_varaible):        
        return np.sum(design_varaible ** 2. / 4000.) - np.prod(np.cos(design_varaible/np.sqrt(self.indcies))) + 1
    
    def test(self):
        ans = self.calculate(np.ones((1, self.dim)) * 0.0)
        print("The exact answer is {}".format(ans))
        return ans
    
    def plot(self, step = 1., Xpoints = [], Ypoints = [], name = ""):
        def f(x, y):
            return (x ** 2. / 4000. + y ** 2. / 4000.) - (np.cos(x/np.sqrt(1))) * (np.cos(y/np.sqrt(2))) + 1
        
        x = np.linspace(-600., 600., (600.- -600.)/step)
        y = copy.copy(x)
        X, Y = np.meshgrid(x, y)
        Z = f(X, Y)
        
        fig = plt.figure()
        cp = plt.contourf(X, Y, Z, cmap=cm.GnBu)
        cp2 = plt.contour(X, Y, Z)
        plt.colorbar(cp)
        plt.xlabel('x1')
        plt.ylabel('x2')
        plt.xlim([-600., 600.])
        plt.ylim([-600., 600.])
        if Xpoints != [] and Ypoints != []:
            plt.scatter(Xpoints, Ypoints, alpha=0.5, marker = '^', c = 'black')
        plt.title('Griewank - ' + name)
        if name == "":
            name = "Fig"
        current_folder = self.cwd + "/Figures/" + name
        print("Saving .. ", current_folder)
        plt.savefig(current_folder)
        plt.close()
    
    def __str__(self):
        output = "\nThis is the Griewank function with {} dimension\n".format(self.dim)
        return output
    
class Shubert(Objective):
    exact = 0.0
    # only 2D
    def __init__(self, dim, step):
        super().__init__(dim, step)
        self.indcies = np.arange(1, self.dim+1)
    
    def get_bounds(self):
        self.LB = -5.12 * self.basic_LB
        self.UB =  5.12 * self.basic_UB
        return self.LB, self.UB, self.steps
    
    def calculate(self, design_varaible):
        pass
    
    def test(self):
        ans = self.calculate(np.ones((1, self.dim)) * 0.0)
        print("The exact answer is {}".format(ans))
        return ans
    
    def plot(self, step = 1., Xpoints = [], Ypoints = [], name = ""):
        # Plot a 2D optimization problem (3D surface)
        line_grid = np.arange(-1., 1., step) * 2.048
        x = np.zeros([line_grid.size, 2])
        z = np.arange(-1., 1., step) * 0.
        x[:, 0] = line_grid
        x[:, 1] = line_grid
        temp = Griewank(2)
        for i in range(line_grid.size):
            z[i] = temp.calculate(x[i, :])
        plt.close('all')
        fig = plt.figure()
        plt.plot(x, z)
        plt.title('Shubert - ' + name)
        if name == "":
            name = "Fig"
        current_folder = self.cwd + "/Figures/" + name
        print("Saving .. ", current_folder)
        plt.savefig(current_folder)
        plt.close()
    
    def __str__(self):
        output = "\nThis is the Shubert function with {} dimension\n".format(self.dim)
        return output

if __name__ == "__main__":
    
    objective_option = 1
    
    dim = 2
    step_size = 2
    
    if   objective_option == 1: obj = Schwefel(dim, step_size)
    elif objective_option == 2: obj = Rastrigin(dim, step_size)
    elif objective_option == 3: obj = Ackley(dim, step_size)
    elif objective_option == 4: obj = Sphere(dim, step_size)
    elif objective_option == 5: obj = XinSheYang(dim, step_size)
    elif objective_option == 6: obj = XinSheYang2(dim, step_size)
    elif objective_option == 7: obj = XinSheYang4(dim, step_size)
    elif objective_option == 8: obj = Quartic(dim, step_size)
    elif objective_option == 9: obj = Michalewicz(dim, step_size)
    elif objective_option == 10: obj = Rosenbrock(dim, step_size)
    elif objective_option == 11: obj = Easom(dim, step_size) # only 2D
    elif objective_option == 12: obj = Griewank(dim, step_size)
    else: raise Exception('Please choose a valid objective function')
    
    N = 10 # test scatter random points
    
    
    LB, UB, steps  = obj.get_bounds()
    print(LB[0,0])
    Xpoints = LB[0,0] + np.random.rand(N) * (UB[0,0] - LB[0,0])
    Ypoints = LB[0,0] + np.random.rand(N) * (UB[0,0] - LB[0,0])
    
    obj.plot(step = step_size, Xpoints = Xpoints, Ypoints = Ypoints)
