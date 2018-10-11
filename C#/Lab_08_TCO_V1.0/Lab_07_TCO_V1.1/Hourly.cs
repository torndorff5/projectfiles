//This file contains a class that represents an Hourly Employee
//Last modified 9/13/17

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_03_TCO_V1._0
{
    [Serializable]
    ///
    public sealed class Hourly : Employee
    {
        const int HOURLY_GRADE = 8;
        const int HOURLY_HOURS = 1;
        const int OVERTIME_HOURS = 40;
        //properties
        //payrate
        double pay_rate;
        double overtime_pay_rate;
        //number of hours 
        double num_hours;
        //methods
        //constructor
        /// <summary>
        /// Constructor that takes no arguments
        /// </summary>
        public Hourly()
        {
            pay_rate = 0;
            num_hours = 0;
            overtime_pay_rate = 0;
            max_credit_hours = HOURLY_HOURS;
            qualifying_grade = HOURLY_GRADE;
        }
        /// <summary>
        /// Constructor for Hourly Employeee class
        /// </summary>
        /// <param name="p">hourly payrate for employee</param>
        /// <param name="h">number of hours worked by employee per month</param>
        public Hourly(double p, double h)
        {
            pay_rate = p;
            num_hours = h;
        }
        //get/set
        /// <summary>
        /// Returns the pay rate for hourly employee
        /// </summary>
        /// <returns>pay rate for hourly employee</returns>
        public double GetPayRate ()
        {
            return pay_rate;
        }
        /// <summary>
        /// CHanges pay rate for hourly employee
        /// </summary>
        /// <param name="p">pay rate for Hourly Employee</param>
        private void SetPayRate (double p)
        {
            pay_rate = p;
        }
        /// <summary>
        /// Returns number of hours worked per month by an Hourly Employee
        /// </summary>
        /// <returns>number of hours worked per month</returns>
        public double GetNumHours ()
        {
            return num_hours;
        }
        /// <summary>
        /// Changes the number of hours worked per month by an Hourly Employee
        /// </summary>
        /// <param name="h">number of hours worked per month</param>
        private void SetNumHours (double h)
        {
            num_hours = h;
        }
        //paycalc
        /// <summary>
        /// Calculates the amount of money an Hourly Employee will make in a month. 
        /// </summary>
        /// <returns>total pay for a given month based on the number of hours worked and pay rate. </returns>
        public double PayCalc()
        {
            double total_pay;
            if (num_hours > OVERTIME_HOURS)
            {
                num_hours = num_hours - OVERTIME_HOURS;
                total_pay = (num_hours * overtime_pay_rate) + (OVERTIME_HOURS * pay_rate);
            }
            else
                total_pay = num_hours * pay_rate;
            return total_pay;
        }
    }
}
