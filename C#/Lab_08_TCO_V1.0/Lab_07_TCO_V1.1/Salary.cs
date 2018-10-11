//This file contains a class that represents an Employee on Salary
//Last modified 9/13/17

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_03_TCO_V1._0
{
    [Serializable]
    /// <summary>
    /// Models an Employee that is on Salary
    /// </summary>
    public class Salary : Employee
    {
        //represents a letter grade: 0 = E, 1=D-, 2=D, 3=D+....10=A,11= A+
        const int SALARY_GRADE = 9;
        const int SALARY_HOURS = 6;
        //properties
        double monthly_salary;
        string benefits;
        //methods
        /// <summary>
        /// Constructor for Salary class
        /// </summary>
        /// <param name="s">monthly salary passed in</param>
        public Salary()
        {
            monthly_salary = 0;
            max_credit_hours = SALARY_HOURS;
            qualifying_grade = SALARY_GRADE;
        }
        /// <summary>
        /// Returns the monthly salary for sales employee
        /// </summary>
        /// <returns> monthly salary for employee</returns>
        public double GetMonthlySalary ()
        {
            return monthly_salary;
        }
        /// <summary>
        /// Sets or changes the monthly salary of an employee
        /// </summary>
        /// <param name="s">monthly salary for employee</param>
        private void SetMonthlySalary (double s)
        {
            monthly_salary = s;
        }
        
    }
}
