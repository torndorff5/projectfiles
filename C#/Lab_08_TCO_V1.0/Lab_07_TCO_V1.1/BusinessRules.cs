///Business rules class
///Modified by Tanner Orndorff 10.10.17

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_03_TCO_V1._0
{
    [Serializable]
    public class BusinessRules
    {   
     
        /// <summary>
        /// Memeber Variables //////////////////////////////////////////////
        /// </summary>
        public SortedDictionary<uint,Employee> employeeList;
        const string SAMPLE_FIRST_NAME = "Tanner";
        const string SAMPLE_LAST_NAME = "Orndorff";
        public bool set_duplicate_status = false;
        //  Member Functions ////////////////////////////////////////////////
        //constructor
        /// <summary>
        /// Constructor for this Business rules class. Sets employee list to designated List size 
        /// </summary>
        public BusinessRules()
        {
            //initialize employee list 
            employeeList = new SortedDictionary<uint, Employee>();
            Sales sample_emp = new Sales();
            sample_emp.SetFirstName(SAMPLE_FIRST_NAME);
            sample_emp.SetLastName(SAMPLE_LAST_NAME);
            sample_emp.SetEmpID(1);
            employeeList.Add(sample_emp.GetEmpID(), sample_emp);
        }

        //indexer
        /// <summary>
        /// Allows access to add and retrieve objects from employee list. 
        /// </summary>
        /// <param name="indexer">int passed in that locates that employee</param>
        /// <returns></returns>
        public Employee this[uint id]
        {
            get
            {
                try
                {
                    return employeeList[id];
                }
                catch
                {
                    return null;
                }
            }
            set
            {
                try
                {
                    employeeList.Add(id, value);
                }
                catch
                {
                    set_duplicate_status = true;
                }
            }
        }
        /// <summary>
        /// Returns a matching employee with the same last name 
        /// </summary>
        /// <param name="last_name"></param>
        /// <returns></returns>
        public Employee this[string last_name]
        {
            get
            {
                foreach(KeyValuePair<uint,Employee> employee in employeeList)
                {
                    if (employee.Value.GetLastName() == last_name)
                        return employee.Value;
                }
                return null;
            }
        }
    }
}
