//This file contains a class that represents an Employee 
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
    /// Models an Employee at World-Wide Wombats 
    /// </summary>
    public abstract class Employee
    {
        //properties
        //emp_id 
        uint emp_id;
        //emp_type 
        string emp_type;
        //first_name
        string first_name;
        //last_name
        string last_name{ get; set; }
        //department name
        string department_name { get; set; }
        //title
        string title { get; set; }
        //start date
        DateTime start_date { get; set; }
        //benefits
        string benefits { get; set; }

        //the max credit hours that the company will pay for each employee.
        public int max_credit_hours;
        public int qualifying_grade;
        SortedDictionary<string, Course> courseDirectory;
        public bool duplicate_status = false; //tells whether or not an employee has already taken a school course 
        //methods
        //get emp_id
        public uint GetEmpID()
        {
            return emp_id;
        }
        //set emp_id
        public void SetEmpID(uint i)
        {
            emp_id = i;
        }
        //get emp_type
        public string GetEmpType()
        {
            return emp_type;
        }
        //set emp_type
        public void SetEmpType(string t)
        {
            emp_type = t;
        }
        //get first_name
        public string GetFirstName()
        {
            return first_name;
        }
        //set first_name
        public void SetFirstName(string f)
        {
            first_name = f;
        }
        //get last_name
        public string GetLastName()
        {
            return last_name;
        }
        //set last_name 
        public void SetLastName(string l)
        {
            last_name = l;
        }
        /// <summary>
        /// Indexer for the employee class - dictionary of courses taken. retrieve or add course to employee object 
        /// </summary>
        /// <param name="course_id">the id of the course to look up</param>
        /// <returns>the course object </returns>
        public Course this[string course_id]
        {
            get
            {
                try
                {
                    return courseDirectory[course_id];
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
                    courseDirectory.Add(course_id, value);
                }
                catch
                {
                    duplicate_status = true;
                }
            }
        }
        /// <summary>
        /// Calculates how many credits the company will pay for this employee
        /// </summary>
        /// <returns>the amount of credits the company will pay for for that semester </returns>
        public int EduBenniesCalc()
        {
            int credit_count = 0;//counts to total qualifying credits to be paid for
            //check the grade of every course to see if it qualifies
            foreach (KeyValuePair<string,Course> course in courseDirectory)
            {
                //if course grade is better or equal to qualifying grade
                if(course.Value.GetCourseGrade() >= qualifying_grade)
                {
                    credit_count = credit_count + course.Value.GetCreditHours();
                }
            }
            //if credit count is bigger than the max or equal, return max 
            if (credit_count >= max_credit_hours)
            {
                return max_credit_hours;
            }
            //if credit count is less than the max, return the  lower credit count 
            else
                return credit_count;
        }
    }
}
