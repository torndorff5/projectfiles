//File contains a Class that represents a Contracted Employee
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
    /// Models an Employee working on contract. 
    /// </summary>
    public sealed class Contract : Employee
    {
        //properties
        //contract amount
        double contract_amount;
        //duration (months)
        int monthly_duration;
        //methods
        //constructor
        /// <summary>
        /// Constructor that takes 0 arguments. 
        /// </summary>
        public Contract()
        {
            contract_amount = 0;
            monthly_duration = 0;
        }
        /// <summary>
        /// Constructor for Contract class
        /// </summary>
        /// <param name="c">Amount of pay agreed on in contract</param>
        /// <param name="d">Monthly duration of contract</param>
        public Contract(double c, int d)
        {
            contract_amount = c;
            monthly_duration = d;
        }
        //get/set
        /// <summary>
        /// Returns the amount of money in Employee Contract
        /// </summary>
        /// <returns>money in employee contract</returns>
        public double GetContractAmount()
        {
            return contract_amount;
        }
        /// <summary>
        /// Changes the contract amount for a Contract Employee
        /// </summary>
        /// <param name="c">new contract amount</param>
        private void SetContractAmount(double c)
        {
            contract_amount = c;
        }
        /// <summary>
        /// Returns the Monthly duration of an employee contract
        /// </summary>
        /// <returns>monthly duration of contract</returns>
        public int GetMonthlyDuration()
        {
            return monthly_duration;
        }
        /// <summary>
        /// Changes the monthly duration of Employee Contract
        /// </summary>
        /// <param name="d">new monthly duration of contract</param>
        private void SetMonthlyDuration(int d)
        {
            monthly_duration = d;
        }
        /// <summary>
        /// Calculates the amount of money made by Contract Employee per month over the period of the contract.
        /// </summary>
        /// <returns>Amount of money per month made by employee over contract period</returns>
        public double PayCalc()
        {
            double total_pay = contract_amount / monthly_duration;
            return total_pay;
        }
    }
}
