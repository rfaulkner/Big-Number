
//
//  big_number.cpp
//
//  Class that implements a BigNumber representation.
//
//  Created by Ryan Faulkner on 4/16/13.
//  Copyright (c) 2013. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;


class BigNumber {

    public:

        BigNumber()
        {
            this->digits = NULL;
            this->size = 0;
            this->is_neg = false;
        }

        BigNumber(const BigNumber& bn)
        {
            this->digits = new int[bn.get_size()];
            this->size = bn.get_size();
            this->is_neg = bn.is_negative_number();
            this->digits = bn.get_digits_copy();
        }

        BigNumber(int dim) {
            this->digits = new int[dim];
            this->size = dim;
            this->is_neg = false;
            for (int i = 0; i < dim; i++) this->digits[i] = 0;
        }

        BigNumber(int dim, long val) {
            int i;

            this->digits = new int[dim];
            this->size = dim;
            this->is_neg = false;
            for (i = 0; i < dim; i++) {
                this->digits[i] = val % 10;
                val /= 10;
            }
        }

        ~BigNumber() { delete[] this->digits; }

        /*
        * Prints the number
        */
        void print() const {
            for (int i = this->size - 1; i >= 0; i--) cout << this->digits[i];
            cout << endl;
        }

        bool is_negative_number() const { return this->is_neg; }
        int get_size() const { return this->size; }
        int get_digit(int index) const { return this->digits[index]; }
        int get_most_significant_digit() const
        {
            for (int i = this->size - 1; i >= 0; i--)
                if (digits[i] > 0)
                    return i;
             return 0;
        }
        int* get_digits_copy() const
        {
            int* digits_cp = new int[this->size];
            for (int i = 0; i < this->size; i++)
                digits_cp[i] = this->digits[i];
            return digits_cp;
        }

        BigNumber & operator=(const BigNumber &rhs)
        {
            // Check for self-assignment!
            if (this == &rhs)
                return *this;

            delete[] this->digits;

            this->size = rhs.get_size();
            this->digits = rhs.get_digits_copy();
            this->is_neg = rhs.is_negative_number();

            return *this;
        }

        /*
         * Adds this big number by the arg - size of operands
         */
        BigNumber & operator+=(const BigNumber& other)
        {
            int i, new_val, carry = 0;

            // TODO - throw exception instead
            if (this->size != other.get_size())
            {
                cout << "BigNumber::operator+ - Mismatched sizes." << endl;
                return *(new BigNumber(1,0));
            }

            for (i=0; i < this->size; i++)
            {
                new_val = digits[i] + other.get_digit(i) + carry;

                this->digits[i] = new_val % 10;
                if (new_val >= 10)
                    carry = new_val / 10;
                else
                    carry = 0;
            }

            // TODO - throw exception instead
            if (carry > 0)
                cout << "BigNumber::operator- - Overflow." << endl;

            return *this;
        }

        /*
         * Adds this big number by the arg - size of operands
         */
        BigNumber & operator-=(const BigNumber& other)
        {
            int i, new_val;
            int this_msd = this->get_most_significant_digit();
            int other_msd = other.get_most_significant_digit();
            bool this_larger = true;
            int last_idx = this->size - 1;
            int* digits_cp = other.get_digits_copy();

            int *large_ref, *small_ref;

            // TODO - throw exception instead
            if (this->size != other.get_size())
            {
                cout << "BigNumber::operator- - Mismatched sizes." << endl;
                return *(new BigNumber(1,0));
            }

            // Determine which is larger
            if (other_msd > this_msd)
                this_larger = false;
            else if (other_msd == this_msd)
                for (i = this_msd; i >= 0; i--)
                {
                    if (this->digits[i] < digits_cp[i])
                    {
                        this_larger = false;
                        this->is_neg = true;
                        break;
                    }
                    else if (this->digits[i] > digits_cp[i])
                        break;
                }

            // Set refs
            if (this_larger)
            {
                large_ref = this->digits;
                small_ref = digits_cp;
            }
            else
            {
                small_ref = this->digits;
                large_ref = digits_cp;
            }

            // Perform subtraction
            for (i = 0; i < this->size-1; i++)
            {

                new_val = large_ref[i] - small_ref[i];

                // need to borrow?
                if (new_val < 0)
                {
                    large_ref[i] = new_val + 10;
                    large_ref[i+1] -= 1;
                }
                else
                    large_ref[i] = new_val;
            }

            new_val = large_ref[last_idx] - small_ref[last_idx];
            large_ref[last_idx] = new_val;

            if (large_ref != this->digits)
                for (i = 0; i < this->size; i++)
                    this->digits[i] = large_ref[i];
            delete[] digits_cp;

            return *this;
        }

        /*
         * Multiplies this big number by the arg
         */
        BigNumber & operator*=(const int &other) {

            int i, new_val, carry = 0;

            for (i=0; i < this->size; i++) {
                new_val = digits[i] * other + carry;
                this->digits[i] = new_val % 10;
                if (new_val >= 10)
                    carry = new_val / 10;
                else
                    carry = 0;
            }

            return *this;
        }

         const BigNumber operator+(const BigNumber &other) const {
            BigNumber result = *this;
            result += other;
            return result;
         }

         const BigNumber operator-(const BigNumber &other) const {
            BigNumber result = *this;
            result -= other;
            return result;
         }

        const BigNumber operator*(const int &other) const {
            BigNumber result = *this;
            result *= other;
            return result;
        }

    private:
        int* digits;
        int size;
        bool is_neg;
};
