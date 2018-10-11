using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_03_TCO_V1._0
{
    public class Course
    {
        //properties
        string course_ID;
        string course_description;
        int course_grade;
        string course_date;
        int credit_hours;
        //member functions
        /// <summary>
        /// Constructor for course class. 
        /// </summary>
        /// <param name="id">string id "CS3250"</param>
        /// <param name="desc">written description of course</param>
        /// <param name="grade">number 0 - 11. represents E, D-, D, D+, C-....A, A+</param>
        /// <param name="date">format of MM/DD/YYYY</param>
        /// <param name="hours">integer that represents credit hours of class </param>
        public Course(string id, string desc, int grade, string date, int hours)
        {
            //initiate each of the member variables passed into the constructor 
            course_ID = id;
            course_description = desc;
            course_grade = grade;
            course_date = date;
            credit_hours = hours;
        }
        //getters for each member variable
        public string GetCourseID()
        {
            return course_ID;
        }
        public string GetCourseDescription()
        {
            return course_description;
        }
        public int GetCourseGrade()
        {
            return course_grade;
        }
        public string GetCourseDate()
        {
            return course_date;
        }
        public int GetCreditHours()
        {
            return credit_hours;
        }
        //setters for each member variable 
        void SetCourseID(string id)
        {
            course_ID = id;
        }
        void SetCourseDescription(string desc)
        {
            course_description = desc;
        }
        void SetCourseGrade(int grade)
        {
            course_grade = grade;
        }
        void SetCourseDate(string date)
        {
            course_date = date;
        }
        void SetCreditHours(int hours)
        {
            credit_hours = hours;
        }
    }
}
