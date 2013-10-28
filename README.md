Big-Number
==========

Implements a C++ class that allows you to create integers of arbitrary size.  This data structure can be
handy when you want to avoid overflow and has proven a handy way to solve project Euler [1] problems.

[1] http://projecteuler.net

Example
-------

The following code snippet illustrates basic usage:

    #include <iostream>
    #include "helper/big_number.cpp"

    using namespace std;


    int main() {
    
        BigNumber fn(1000, 1);
        BigNumber fn_minus_1(1000, 1);

        long count = 3;
        
        // Compute successive Fibonacci sequence values until one is
        // found with 1000 digits.  Report the result.
        while (1)
        {
            fn = fn - fn_minus_1;
            fn_minus_1 = fn + fn_minus_1;
            fn = fn_minus_1 * 2 - fn;
        
            if (fn.get_digit(999) > 0)
                break;
        
            count++;
        }
    
        fn.print();
        cout << "The " << count << " term of the fibonacci sequence is the first to contain at least 1000 digits." << endl;
    
        return 0;
    }

If we add this code to the file fib.cpp compile then run we get:

    ~rfaulk$ g++ -Wall fib.cpp -o fib
    ~rfaulk$ ./fib
    1070066266382758936764980584457396885083683896632151665013235203375314520604694040621889147582489792657804694888177591957484336466672569959512996030461262748092482186144069433051234774442750273781753087579391666192149259186759553966422837148943113074699503439547001985432609723067290192870526447243726117715821825548491120525013201478612965931381792235559657452039506137551467837543229119602129934048260706175397706847068202895486902666185435124521900369480641357447470911707619766945691070098024393439617474103736912503231365532164773697023167755051595173518460579954919410967778373229665796581646513903488154256310184224190259846088000110186255550245493937113651657039447629584714548523425950428582425306083544435428212611008992863795048006894330309773217834864543113205765659868456288616808718693835297350643986297640660000723562917905207051164077614812491885830945940566688339109350944456576357666151619317753792891661581327159616877487983821820492520348473874384736771934512787029218636250627816
    
    The 4781 term of the fibonacci sequence is the first to contain at least 1000 digits.

