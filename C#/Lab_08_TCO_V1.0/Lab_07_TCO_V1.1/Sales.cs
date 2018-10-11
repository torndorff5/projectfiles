//This file contains a class that represents a Sales Employee
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
    public sealed class Sales : Salary
    {
        const int SALES_GRADE = 6;
        const int SALES_HOURS = 3;
        //properties
        //commision rate
        double commision_rate;
        //grossSales (monthly)
        double gross_sales;
        //methods 
        //constructor 
        /// <summary>
        /// Constructor that takes no arguments. 
        /// </summary>
        public Sales()
        {
            commision_rate = 0;
            gross_sales = 0;
            max_credit_hours = SALES_HOURS;
            qualifying_grade = SALES_GRADE;
        }
        /// <summary>
        /// Constructor for Sales - Salary - Employee class
        /// </summary>
        /// <param name="r">commision rate</param>
        /// <param name="s">gross monthly sales</param>
        public Sales(double r, double s)
        {
            commision_rate = r;
            gross_sales = s;
        }
        //get/set
        /// <summary>
        /// Returns the current commision rate for Sales Employee
        /// </summary>
        /// <returns>current commision rate</returns>
        public double GetCommisionRate()
        {
            return commision_rate;
        }
        /// <summary>
        /// Changes the commision rate for a Sales Employee
        /// </summary>
        /// <param name="r">new commision rate</param>
        private void SetCommisionRate(double r)
        {
            commision_rate = r;
        }
        /// <summary>
        /// Returns the gross sales for the month for a Sales Employee
        /// </summary>
        /// <returns>gross sales for the month</returns>
        public double GetGrossSales()
        {
            return gross_sales;
        }
        /// <summary>
        /// Changes the gross sales for the month for a Sales Employee
        /// </summary>
        /// <param name="s">new gross sales</param>
        private void SetGrossSales(double s)
        {
            gross_sales = s;
        }
        //commision calc
    }
}
