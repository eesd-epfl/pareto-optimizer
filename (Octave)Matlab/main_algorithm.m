% The Pareto-like Sequential Sampling Algorithm (PSS)
% Written by Mahmoud S. Shaqfa and Prof. Katrin Beyer
% This is a simple implementation of the algorithm
% The main code was implemented in C++14 and Python.
% This code only solves Schwefel function (you can easily modify it)

function results_struct = main_algorithm
clear; clc; close all; tic; format long;

plot_results = true;
%% Algorithmic parameter-settings
acceptance_rate = 0.95;     % Acceptance probability (alpha)
pop_size = 30;              % population size (beta)
iterations = 50;          % Number of iterations (gamma)

%% The objective function parameters
dim = 5;

LB_val = -512;
UB_val = 512;
exact = 420.9687;
%% Initialize and pre-allocation of memory containers
LB = ones(1, dim) * LB_val; % Lower bounds vector
UB = ones(1, dim) * UB_val; % Upper bounds vector
funval_his = zeros(iterations + 1, 1); % The history of all iterations
funval = zeros(pop_size, 1); % Function evaluations per iteration for all the population memebers
limits_his = zeros(iterations + 1, dim * 2); % The histories of LB and UB

%% Initialize the population - Fast vectorized initial sampling
LB_mat = repmat(LB, pop_size, 1);
UB_mat = repmat(UB, pop_size, 1);
random_pop = rand(pop_size, dim);
population = LB_mat + random_pop .* (UB_mat - LB_mat);

clear LB_mat UB_mat % we don't need them after this stage (clear memory)

% Evaluate the inital population
for i = 1: pop_size
    funval(i) = Schwefel(population(i, :));
end

% Find the current best solution
[~, best_index] = min(funval);
funval_his(1) = funval(best_index);
best_sol = population(best_index, :);
new_solution = true;
%% The core of the algorithm (the critical loop)
for i = 2: iterations + 1
    random_pop = rand(pop_size, dim);
    for j = 1:pop_size
       counter = 1;
       for k = 1: dim
           % Change the prominent domain (a self-adaptive mechanism)
           if new_solution
              deviation = 0.5 * (1 - acceptance_rate) * (1 - (i/iterations)) ...
                  * (UB(k) - LB(k));
           end
           reduced_LB = max([best_sol(k) - deviation, LB(k)]);
           reduced_UB = min([reduced_LB + 2 * deviation, UB(k)]);
           
           % Hold the history of the prominent domain
           limits_his(i, counter) = reduced_LB;
           counter = counter + 1;
           limits_his(i, counter) = reduced_UB;
           counter = counter + 1;
           
           if rand <= acceptance_rate
               % Sample from the prominent domain
               population(j, k) = reduced_LB + random_pop(j, k) ...
                   * (reduced_UB - reduced_LB);
           else
               % Sample from the overall domain
               population(j, k) = LB(k) + random_pop(j, k) ...
                   * (UB(k) - LB(k));
           end
       end
       % Evaluate the solution vector
       funval(j) = Schwefel(population(j, :));    
    end
    % Find the current best value
    if min(funval) <= funval_his(i - 1)
        [~, best_index] = min(funval);
        best_sol = population(best_index, :);
        new_solution = true;
        funval_his(i) = min(funval);
    else
        new_solution = false;
        funval_his(i) = funval_his(i - 1);
    end
    fprintf('\nIteration number %4.0f and best fitness is: %4.10f', i, funval_his(i))
end
time = toc;
fprintf('\n\nThe elapsed time %4.5f min', time / 60)
fprintf('\n\nThe best solution is: \n')
disp(best_sol)

%% Plot the results
disp('Exporting the figures, please wait ...')
if plot_results
    % plot convergence
    f1 = figure;
    plot(1:length(funval_his), funval_his, 'LineWidth', 2)
    xlim([2, length(funval_his)])
    xlabel('Iterations')
    ylabel('Objective evaluation')
    title('Convergence curve')
    grid on
    print(f1, 'convergence', '-r400', '-dpdf')
    
    % plot the prominent domain history
    f2 = figure('visible','off');
    set(f2, 'Position', [0 0 200 20*dim])
    counter = 1;
    for kk = 1:dim
        subplot(ceil(dim/2), 2, kk)
        title(num2str(kk))
        plot(1:length(limits_his(:,1)), limits_his(:, counter), '-r')
        counter = counter + 1;
        hold on
        plot(1:length(limits_his(:,1)), limits_his(:, counter), '-b')
        counter = counter + 1;
        hold on
        plot(1:length(limits_his(:,1)), ...
            ones(1, length(limits_his(:,1)))*exact, '--m')
        xlim([2, length(funval_his)])
        hold off
    end
    saveas(f2,'prominent_domain','pdf')
    print(f2, 'prominent_domain', '-r400', '-dpdf','-fillpage')
end
disp('Done')
%% Saving the final results and vectors
results_struct.time = time;
results_struct.evaluations_history = funval_his;
results_struct.LB_UB_history = limits_his;
end

%% Implement your objective function right here.
function y = Schwefel(design_vector)
% See: https://www.sfu.ca/~ssurjano/schwef.html
y = 418.9829 * length(design_vector) - sum(design_vector .* sin(sqrt(abs(design_vector))));
end