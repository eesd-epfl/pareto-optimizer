//
// Created by shaqfa on 06/12/2019.
//

#include "objective.h"

  /////////////////////////////////////////////////////
 ///               Schwefel Function               ///
/////////////////////////////////////////////////////

RealVec& schwefel::eval(RealVec& solution, Real& w1, Real& w2) {
    Real obj = 0.; Real pnlt = 0.;
    for(auto&& s: solution)
        obj += 418.9829 - s * sin(pow(std::abs(s),0.5));
    static RealVec ans(2);
    ans[0] = obj; ans[1] = pnlt;
    penalize(ans, w1, w2);
    return ans;
}
void schwefel::penalize(RealVec& answer, Real& w1, Real& w2) {answer[0] *= pow(w1*(1 + answer[1]), w2);}
RealVec schwefel::get_bounds(){return RealVec{-500., 500.};}

  /////////////////////////////////////////////////////
 ///               Schwefel Function               ///
/////////////////////////////////////////////////////

RealVec& mod_schwefel::eval(RealVec& solution, Real& w1, Real& w2) {
    Real obj = 0.; Real pnlt = 0.;
    for(auto&& s: solution)
        obj += - s * sin(pow(std::abs(s),0.5));
    static RealVec ans(2);
    ans[0] = obj; ans[1] = pnlt;
    penalize(ans, w1, w2);
    return ans;
}
void mod_schwefel::penalize(RealVec& answer, Real& w1, Real& w2) {answer[0] *= pow(w1*(1 + answer[1]), w2);}
RealVec mod_schwefel::get_bounds(){return RealVec{-500., 500.};}


  /////////////////////////////////////////////////////
 ///               Sphere Function                 ///
/////////////////////////////////////////////////////

RealVec& sphere::eval(RealVec& solution, Real& w1, Real& w2) {
    Real obj = 0.; Real pnlt = 0.;
    for(auto&& s: solution)
        obj += pow(s,2.);
    static RealVec ans(2);
    ans[0] = obj; ans[1] = pnlt;
    penalize(ans, w1, w2);
    return ans;
}
void sphere::penalize(RealVec& answer, Real& w1, Real& w2) {answer[0] *= pow(w1*(1 + answer[1]), w2);}
//RealVec sphere::get_bounds(){return RealVec{-5.12, 5.12};}
RealVec sphere::get_bounds(){return RealVec{-100., 100.};}

  /////////////////////////////////////////////////////
 ///               Sum Squares Function            ///
/////////////////////////////////////////////////////

RealVec& sum_squares::eval(RealVec& solution, Real& w1, Real& w2) {
    Real obj = 0.; Real pnlt = 0., counter = 1.;
    for(auto&& s: solution)
        obj += pow(s,2.) *  counter, counter++;
    static RealVec ans(2);
    ans[0] = obj; ans[1] = pnlt;
    penalize(ans, w1, w2);
    return ans;
}
void sum_squares::penalize(RealVec& answer, Real& w1, Real& w2) {answer[0] *= pow(w1*(1 + answer[1]), w2);}
RealVec sum_squares::get_bounds(){return RealVec{-10., 10.};}

  /////////////////////////////////////////////////////
 ///           Chung Reynolds Function             ///
/////////////////////////////////////////////////////

RealVec& chung_reynolds::eval(RealVec& solution, Real& w1, Real& w2) {
    Real obj = 0.; Real pnlt = 0.;
    for(auto&& s: solution)
        obj += pow(s,2.);
    static RealVec ans(2);
    ans[0] = std::pow(obj, 2.); ans[1] = pnlt;
    penalize(ans, w1, w2);
    return ans;
}
void chung_reynolds::penalize(RealVec& answer, Real& w1, Real& w2) {answer[0] *= pow(w1*(1 + answer[1]), w2);}
RealVec chung_reynolds::get_bounds(){return RealVec{-100., 100.};}

  /////////////////////////////////////////////////////
 ///               Rosenbrock Function             ///
/////////////////////////////////////////////////////

RealVec& rosenbrock::eval(RealVec& solution, Real& w1, Real& w2){
    Real obj = 0.; Real pnlt = 0.;
    for(UInt i = 0; i < solution.size()-1; ++i)
        obj += (100. * std::pow(solution[i+1] - std::pow(solution[i], 2.), 2.))
                + std::pow((solution[i] - 1), 2.);
    static RealVec ans(2);
    ans[0] = obj; ans[1] = pnlt;
    penalize(ans, w1, w2);
    return ans;
}
void rosenbrock::penalize(RealVec& answer, Real& w1, Real& w2) {answer[0] *= pow(w1*(1 + answer[1]), w2);}
RealVec rosenbrock::get_bounds() {return RealVec{-5.12, 5.12};}

  /////////////////////////////////////////////////////
 ///               Griewank Function               ///
/////////////////////////////////////////////////////

RealVec& griewank::eval(RealVec& solution, Real& w1, Real& w2){
    Real obj; Real pnlt = 0.;
    Real sum = 0., prod = 1.; Real counter = 1.;
    for(auto&& s: solution)
        sum += std::pow(s, 2.), prod *= std::cos(s / std::sqrt((Real)counter)), counter++;
    obj = sum/4000. - prod + 1.;
    static RealVec ans(2);
    ans[0] = obj; ans[1] = pnlt;
    penalize(ans, w1, w2);
    return ans;
}
void griewank::penalize(RealVec& answer, Real& w1, Real& w2) {answer[0] *= pow(w1*(1 + answer[1]), w2);}
RealVec griewank::get_bounds() {return RealVec{-600., 600.};}

  /////////////////////////////////////////////////////
 ///               Ackley Function                 ///
/////////////////////////////////////////////////////

RealVec& ackley::eval(RealVec& solution, Real& w1, Real& w2){
    Real obj = 0.; Real pnlt = 0.;
    Real sum1 = 0., sum2 = 0.;
    for(auto&& s: solution)
        sum1 += std::pow(s, 2.), sum2 += std::cos(2. * PI * s);
    obj =  -20. * std::exp(-0.2 * std::sqrt(sum1 / (Real)solution.size()))
            -std::exp(sum2 / (Real) solution.size()) + 20. + std::exp(1.);
    static RealVec ans(2);
    ans[0] = obj; ans[1] = pnlt;
    penalize(ans, w1, w2);
    return ans;
}
void ackley::penalize(RealVec& answer, Real& w1, Real& w2) {answer[0] *= pow(w1*(1 + answer[1]), w2);}
RealVec ackley::get_bounds() {return RealVec{-32.768, 32.768};}

  /////////////////////////////////////////////////////
 ///               Schwefel2.22 Function           ///
/////////////////////////////////////////////////////

RealVec& schwefel2_22::eval(RealVec& solution, Real& w1, Real& w2){
    Real obj = 0.; Real pnlt = 0.;
    Real sum = 0., prod = 0.;
    for(auto&& s: solution)
        sum += std::abs(s), prod *= std::abs(s);
    obj = sum + prod;
    static RealVec ans(2);
    ans[0] = obj; ans[1] = pnlt;
    penalize(ans, w1, w2);
    return ans;
}
void schwefel2_22::penalize(RealVec& answer, Real& w1, Real& w2) {answer[0] *= pow(w1*(1 + answer[1]), w2);}
RealVec schwefel2_22::get_bounds() {return RealVec{-10., 10.};}

  /////////////////////////////////////////////////////
 ///               Schwefel2.21 Function           ///
/////////////////////////////////////////////////////

RealVec& schwefel2_21::eval(RealVec& solution, Real& w1, Real& w2){
    Real obj = 0.; Real pnlt = 0.;
    Real max = 0.;
    for(auto&& s: solution)
        (std::abs(s) > max) ? (max = abs(s)) : (max);
    obj = max;
    static RealVec ans(2);
    ans[0] = obj; ans[1] = pnlt;
    penalize(ans, w1, w2);
    return ans;
}
void schwefel2_21::penalize(RealVec& answer, Real& w1, Real& w2) {answer[0] *= pow(w1*(1 + answer[1]), w2);}
RealVec schwefel2_21::get_bounds() {return RealVec{-100., 100.};}

  /////////////////////////////////////////////////////
 ///               Michalewicz Function            ///
/////////////////////////////////////////////////////

RealVec& michalewicz::eval(RealVec& solution, Real& w1, Real& w2){
    Real obj = 0.; Real pnlt = 0.; UInt counter = 1;
    for(auto&& s: solution)
        obj -= std::sin(s) * std::pow(std::sin(counter * std::pow(s, 2.) / PI), 2.0 * 10), counter++;
    static RealVec ans(2);
    ans[0] = obj; ans[1] = pnlt;
    penalize(ans, w1, w2);
    return ans;
}
void michalewicz::penalize(RealVec& answer, Real& w1, Real& w2) {answer[0] *= pow(w1*(1 + answer[1]), w2);}
RealVec michalewicz::get_bounds() {return RealVec{-0., PI};}

  /////////////////////////////////////////////////////
 ///               Rastrangin Function             ///
/////////////////////////////////////////////////////

RealVec& rastrangin::eval(RealVec& solution, Real& w1, Real& w2){
    Real obj = 0.; Real pnlt = 0.;
    for(auto&& s: solution)
        obj += std::pow(s, 2.) - 10. * std::cos(2. * PI * s);
    obj += 10. * (Real) solution.size();
    static RealVec ans(2);
    ans[0] = obj; ans[1] = pnlt;
    penalize(ans, w1, w2);
    return ans;
}
void rastrangin::penalize(RealVec& answer, Real& w1, Real& w2) {answer[0] *= pow(w1*(1 + answer[1]), w2);}
RealVec rastrangin::get_bounds() {return RealVec{-5.12, 5.12};}

  /////////////////////////////////////////////////////
 ///               Shubert Function                ///
/////////////////////////////////////////////////////

RealVec& shubert::eval(RealVec& solution, Real& w1, Real& w2){
    Real obj = 0.; Real pnlt = 0.;
    Real ans1, ans2 = 1.;
    for(auto&& s : solution) {
        ans1 = 0.;
        for (UInt i = 1; i < 6; ++i)
            ans1 += (Real) i * std::cos(((Real) i + 1.) * s + (Real) i);
        ans2 *= ans1;
    }
    obj += ans2;
    static RealVec ans(2);
    ans[0] = obj; ans[1] = pnlt;
    penalize(ans, w1, w2);
    return ans;
}
void shubert::penalize(RealVec& answer, Real& w1, Real& w2) {answer[0] *= pow(w1*(1 + answer[1]), w2);}
RealVec shubert::get_bounds() {return RealVec{-5.12, 5.12};}

  /////////////////////////////////////////////////////
 ///               De Jong 5 Function              ///
/////////////////////////////////////////////////////

RealVec& dejong5::eval(RealVec& solution, Real& w1, Real& w2){
    Real obj; Real pnlt = 0.;
    Real ans1 = 0.;
    for(int i = -2; i < 3; ++i)
        for(int j = -2; j < 3; ++j)
            ans1 += 1.0 / ( 5 * ((Real)i + 2.) + (Real)j + 3. + std::pow((solution[0] - 16. * (Real)j), 6.) +
                    std::pow((solution[1] - 16. *(Real)i), 6.));
    obj = 1./((1./500.) + ans1);
    static RealVec ans(2);
    ans[0] = obj; ans[1] = pnlt;
    penalize(ans, w1, w2);
    return ans;
}
void dejong5::penalize(RealVec& answer, Real& w1, Real& w2) {answer[0] *= pow(w1*(1 + answer[1]), w2);}
RealVec dejong5::get_bounds() {return RealVec{-65.536, 65.536};}

  /////////////////////////////////////////////////////
 ///               Six hump camel Function         ///
/////////////////////////////////////////////////////

RealVec& six_hump_camel::eval(RealVec& solution, Real& w1, Real& w2){
    Real obj; Real pnlt = 0.;
    obj = 4. * std::pow(solution[0], 2.) - 2.1 * std::pow(solution[0], 4.)
            + 1./3. *  std::pow(solution[0], 6.) + solution[0] * solution[1] -
            4. * std::pow(solution[1], 2.) +  4. * std::pow(solution[1], 4.);
    static RealVec ans(2);
    ans[0] = obj; ans[1] = pnlt;
    penalize(ans, w1, w2);
    return ans;
}
void six_hump_camel::penalize(RealVec& answer, Real& w1, Real& w2) {answer[0] *= pow(w1*(1 + answer[1]), w2);}
RealVec six_hump_camel::get_bounds() {return RealVec{-5., 5.};}

  /////////////////////////////////////////////////////
 ///               zakharov Function               ///
/////////////////////////////////////////////////////

RealVec& zakharov::eval(RealVec& solution, Real& w1, Real& w2){
    Real obj, sum1 = 0., sum2 = 0., pnlt = 0., counter = 1.;
    for(auto&& s: solution)
        sum1 += std::pow(s, 2.), sum2 += 0.5 * counter * s, counter++;
    obj = sum1 + std::pow(sum2, 2.) + std::pow(sum2, 4.);
    static RealVec ans(2);
    ans[0] = obj; ans[1] = pnlt;
    penalize(ans, w1, w2);
    return ans;
}
void zakharov::penalize(RealVec& answer, Real& w1, Real& w2) {answer[0] *= pow(w1*(1 + answer[1]), w2);}
RealVec zakharov::get_bounds() {return RealVec{-5., 10.};}

  /////////////////////////////////////////////////////
 ///            Goldstein Price Function           ///
/////////////////////////////////////////////////////

RealVec& goldstein::eval(RealVec& solution, Real& w1, Real& w2){
    Real obj, pnlt = 0.;
    obj = (1. + std::pow(solution[0] + solution[1] + 1., 2.) * (19. - 14. * solution[0] +
            3. * std::pow(solution[0], 2.) - 14. * solution[1] +
            6. * solution[0] * solution[1] + 3.*std::pow(solution[1], 2.))) *
            (30. + std::pow(2.*solution[0] - 3.* solution[1],2.) * (18. - 32. * solution[0] + 12. *
            std::pow(solution[0], 2.) + 48.*solution[1] - 36.*solution[0] * solution[1] +
            27. * std::pow(solution[1], 2.)));

    static RealVec ans(2);
    ans[0] = obj; ans[1] = pnlt;
    penalize(ans, w1, w2);
    return ans;
}
void goldstein::penalize(RealVec& answer, Real& w1, Real& w2) {answer[0] *= pow(w1*(1 + answer[1]), w2);}
RealVec goldstein::get_bounds() {return RealVec{-2., 2.};}

//********************* Engineering problems *********************

  /////////////////////////////////////////////////////
 ///               Gear Train design problem       ///
/////////////////////////////////////////////////////

RealVec& gear_design::eval(RealVec& solution, Real& w1, Real& w2){
    Real obj; Real pnlt = 0.;
    obj = std::pow(((1./6.931) - ((solution[2] * solution[1])/ (solution[0] * solution[3]))), 2.);
    static RealVec ans(2);
    ans[0] = obj; ans[1] = pnlt;
    penalize(ans, w1, w2);
    return ans;
}
void gear_design::penalize(RealVec& answer, Real& w1, Real& w2) {answer[0] *= pow(w1*(1 + answer[1]), w2);}
RealVec gear_design::get_bounds() {return RealVec{12., 60.};}

  /////////////////////////////////////////////////////
 ///          Three-bar truss design problem       ///
/////////////////////////////////////////////////////

RealVec& three_bar_truss::eval(RealVec& solution, Real& w1, Real& w2){
    Real obj; Real pnlt = 0.;
    Real l = 100., P = 2., sigma = 2.;
    Real g1, g2, g3;
    // Objective function
    obj = l * (2. * std::sqrt(2.) * solution[0] + solution[1]);
    // Apply constraints
    g1 = ((std::sqrt(2.) * solution[0] + solution[1]) / (std::sqrt(2.)
            * std::pow(solution[0], 2.) + 2. * solution[0] * solution[1])) * P - sigma;
    g2 = (solution[1] / (std::sqrt(2.) * std::pow(solution[0], 2.)
            + 2. * solution[0] * solution[1])) * P - sigma;
    g3 = (1./ (std::sqrt(2.) * solution[1] + solution[0])) * P - sigma;
    if (g1 > 0.)
        pnlt += g1;
    else if (g2 > 0.)
        pnlt += g2;
    else if (g3 > 0.)
        pnlt += g3;
    static RealVec ans(2);
    ans[0] = obj; ans[1] = pnlt;
    penalize(ans, w1, w2);
    return ans;
}
void three_bar_truss::penalize(RealVec& answer, Real& w1, Real& w2) {answer[0] *= pow(w1*(1 + answer[1]), w2);}
RealVec three_bar_truss::get_bounds() {return RealVec{0., 1.};}

  /////////////////////////////////////////////////////
 ///        Cantilever beam design problem         ///
/////////////////////////////////////////////////////

RealVec& cantilever_beam_design::eval(RealVec& solution, Real& w1, Real& w2){
    Real obj; Real pnlt = 0.;
    Real g1;
    // Objective function
    obj = 0.0624 * (solution[0] + solution[1] + solution[2] + solution[3] + solution[4]);
    // Apply constraints
    g1 = 61./(std::pow(solution[0], 3.)) + 37./(std::pow(solution[1], 3.))
            + 19./(std::pow(solution[2], 3.)) + 7./(std::pow(solution[3], 3.)) +
            1./(std::pow(solution[4], 3.)) - 1.;
    if (g1 > 0.)
        pnlt += g1;
    static RealVec ans(2);
    ans[0] = obj; ans[1] = pnlt;
    penalize(ans, w1, w2);
    return ans;
}
void cantilever_beam_design::penalize(RealVec& answer, Real& w1, Real& w2) {answer[0] *= pow(w1*(1 + answer[1]), w2);}
RealVec cantilever_beam_design::get_bounds() {return RealVec{0.01, 100.};}