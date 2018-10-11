// Project Prolog
// Name: Tanner Orndorff
// CS3260 001
// Project: Lab_07
// Date: 10/26/2017 
// Purpose: Practice the principles of OOO by creating a GUI application that creates different types of Employees
//
// I declare that the following code was written by me or provided
// by the instructor for this project. I understand that copying source
// code from any other source constitutes plagiarism, and that I will receive
// a zero on this project if I am found in violation of this policy.
// ---------------------------------------------------------------------------


using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Text.RegularExpressions;

namespace Lab_03_TCO_V1._0
{
    public partial class FrmMain : Form
    { 
        //initiate class level variables
        const string SUCCESS = "Status: Employee Successfully Created";
        const string SUCCESS_R = "Status: Employee Successfully Retrieved";
        const string SUCCESS_S = "Status: Employee Database File Successfully Saved";
        const string SUCCESS_L = "Status: Employee Database File Successfully Loaded";
        const string FAILURE = "Status: Input Data Not Compatible";
        const string DEFAULT = "Status: N/A";
        const string FULL = "Status: Employee List is full";
        const string NOT_FOUND = "Status: Employee Doesn't Exist";
        const string FILE_ERROR = "File Error has occured.";
        const string DUPLICATE_ID = "Status: Employee ID Already In Use.";
        const string NEW_DB = "Status: Please Add Employees To This Database.";
        const string DATE_PATTERN = "^(0[1-9]|1[012])[- /.](0[1-9]|[12][0-9]|3[01])[- /.](19|20)";
        uint i = 0;
        private const int LIST_SIZE = 10;
        //create list of employees 
        BusinessRules list = new BusinessRules();
        FileIO fileIO;

        public FrmMain()
        {
            InitializeComponent();
        }
        /// <summary>
        /// Resets the Gui to the starting view for the Create employee sections 
        /// </summary>
        void ResetGuiCreate()
        {
            //set all textbox fields back to null 
            TxtFirstName.Text = "";
            TxtLastName.Text = "";
            TxtEmpID.Text = "";
            CBxType.Text = "";
            LblStatus.Text = DEFAULT;
        }
        /// <summary>
        /// Resets the Gui aspects of the Retrieve employee section
        /// </summary>
        void ResetGuiRetrieve()
        {
            //set all textbox fields back to null 
            TxtFirstNameR.Text = "";
            TxtLastNameR.Text = "";
            TxtEmpIDR.Text = "";
            TxtTypeR.Text = "";
            LblStatus.Text = DEFAULT;
        }
        /// <summary>
        /// Resets gui course 
        /// </summary>
        void ResetGuiCourse()
        {
            TxtCourseDate.Text = "";
            TxtCourseGrade.Text = "";
            TxtCourseCredits.Text = "";
            TxtCourseID.Text = "";
            RTBxCourseDesc.Text = "";
        }
        /// <summary>
        /// Event handler for the Create Employee button.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void BtnCreate_Click(object sender, EventArgs e)
        {

            //take the value of the employee type
            //convert values ID
            uint id;
            uint.TryParse(TxtEmpID.Text, out id);
            string intPattern = @"^\d{5}";
            Match id_match = Regex.Match(TxtEmpID.Text, intPattern);
            if (i >= LIST_SIZE)
            {
                ResetGuiCreate();
                LblStatus.Text = FULL;
            }
            else if (!id_match.Success && id == 0)
            {
                LblStatus.Text = FAILURE;
            }
            else if (CBxType.Text == "Contract")
            {
                //create contract object and set values 
                Contract employee = new Contract();
                employee.SetEmpID(id);
                employee.SetEmpType(CBxType.Text);
                employee.SetFirstName(TxtFirstName.Text);
                employee.SetLastName(TxtLastName.Text);
                list[employee.GetEmpID()] = employee;
                //clear input fields 
                ResetGuiCreate();
                if (list.set_duplicate_status == true)
                {
                    LblStatus.Text = DUPLICATE_ID;

                }
                else
                {
                    LblStatus.Text = SUCCESS;
                }
            }
            else if (CBxType.Text == "Salary")
            {
                //create Salary object and set values 
                Salary employee = new Salary();
                employee.SetEmpID(id);
                employee.SetEmpType(CBxType.Text);
                employee.SetFirstName(TxtFirstName.Text);
                employee.SetLastName(TxtLastName.Text);
                list[employee.GetEmpID()] = employee;
                //clear input fields 
                ResetGuiCreate();
                if (list.set_duplicate_status == true)
                {
                    LblStatus.Text = DUPLICATE_ID;

                }
                else
                {
                    LblStatus.Text = SUCCESS;
                }
            }
            else if (CBxType.Text == "Hourly")
            {
                //create Hourly object and set values 
                Hourly employee = new Hourly();
                employee.SetEmpID(id);
                employee.SetEmpType(CBxType.Text);
                employee.SetFirstName(TxtFirstName.Text);
                employee.SetLastName(TxtLastName.Text);
                list[employee.GetEmpID()] = employee;
                //clear input fields 
                ResetGuiCreate();
                if (list.set_duplicate_status == true)
                {
                    LblStatus.Text = DUPLICATE_ID;

                }
                else
                {
                    LblStatus.Text = SUCCESS;
                }
            }
            else if (CBxType.Text == "Sales")
            {
                //create Sales object and set values 
                Sales employee = new Sales();
                employee.SetEmpID(id);
                employee.SetEmpType(CBxType.Text);
                employee.SetFirstName(TxtFirstName.Text);
                employee.SetLastName(TxtLastName.Text);
                list[employee.GetEmpID()] = employee;
                //clear input fields 
                ResetGuiCreate();
                if (list.set_duplicate_status == true)
                {
                    LblStatus.Text = DUPLICATE_ID;

                }
                else
                {
                    LblStatus.Text = SUCCESS;
                }
            }
            else
            {
                //Right Employee Type was not entered. Declare failure
                LblStatus.Text = FAILURE;
            }
        }
        /// <summary>
        /// Clears the database being used and allows user to create new file or overwrite one 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void BtnCreateDB_Click(object sender, EventArgs e)
        {
            //reset list values
            list.employeeList = new SortedDictionary<uint, Employee>();
            //display status 
            ResetGuiCreate();
            ResetGuiRetrieve();
            LblStatus.Text = NEW_DB;
        }
        /// <summary>
        /// Loads an existing database from a serialized disk file 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void BtnLoad_Click(object sender, EventArgs e)
        {
            //show open dialog and filter the results to only text files. 
            OpenFileDialog OpenDialog = new OpenFileDialog();
            OpenDialog.Title = "World Wide Wombats";
            OpenDialog.Filter = "Text files (*.txt)|*.txt";
            if (OpenDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {

                //pass in file name to file io to open 
                fileIO = new FileIO(OpenDialog.FileName, list.employeeList);
                //open and read specified file
                fileIO.ReadFileDB();
                //load read contents into list
                list.employeeList = fileIO.employeeList;
                LblStatus.Text = SUCCESS_L;
            }
        }
        /// <summary>
        /// Writes the employee database to a text file. (serialized)
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void BtnSave_Click(object sender, EventArgs e)
        {
            //show open dialog and filter the results to only text files. 
            SaveFileDialog SaveDialog = new SaveFileDialog();
            SaveDialog.Title = "World Wide Wombats";
            SaveDialog.Filter = "Text files (*.txt)|*.txt";
            if (SaveDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                //pass in file name to file io to open and write to it 
                fileIO = new FileIO(SaveDialog.FileName, list.employeeList);
                fileIO.WriteFileDB();
                LblStatus.Text = SUCCESS_S;
            }
        }
        /// <summary>
        /// Event Handler for the Retrieve Employee button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void BtnRetrieve_Click(object sender, EventArgs e)
        {
            //check to see if index number is valid. 
            uint index;
            uint.TryParse(TxtEmpIDR.Text, out index);
            if (index == 0)
            {
                //if object is found by last name
                if (list[TxtEmpIDR.Text] != null)
                {
                    Employee employee = list[TxtEmpIDR.Text];
                    //populate the fields with the data 
                    string first_name = employee.GetFirstName();
                    string last_name = employee.GetLastName();
                    uint emp_id = employee.GetEmpID();
                    string emp_type = employee.GetEmpType();
                    if (emp_id != 0)
                    {
                        TxtFirstNameR.Text = first_name;
                        TxtLastNameR.Text = last_name;
                        TxtEmpIDR.Text = emp_id.ToString();
                        TxtTypeR.Text = emp_type;
                        LblStatus.Text = SUCCESS_R;
                    }
                }
                else
                {
                    ResetGuiRetrieve();
                    LblStatus.Text = NOT_FOUND;
                }
            }
            //get employee object from the list
            else if (list[index] != null)
            {
                Employee employee = list[index];
                //populate the fields with the data 
                string first_name = employee.GetFirstName();
                string last_name = employee.GetLastName();
                uint emp_id = employee.GetEmpID();
                string emp_type = employee.GetEmpType();
                if (emp_id != 0)
                {
                    TxtFirstNameR.Text = first_name;
                    TxtLastNameR.Text = last_name;
                    TxtEmpIDR.Text = emp_id.ToString();
                    TxtTypeR.Text = emp_type;
                    LblStatus.Text = SUCCESS_R;
                }
                else
                {
                    ResetGuiRetrieve();
                    LblStatus.Text = NOT_FOUND;
                }
            }
            else //index number isnt valid
            {
                ResetGuiRetrieve();
                LblStatus.Text = FAILURE;
            }

        }
        /// <summary>
        /// Event handler for add course button. Attaches a course to an employee
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void BtnAddCourse_Click(object sender, EventArgs e)
        {
            
            Regex regex = new Regex(DATE_PATTERN);
            if (regex.IsMatch(TxtCourseDate.Text))
            {
                //check to see if index number is valid. 
                uint index;
                uint.TryParse(TxtEmpIDR.Text, out index);
                //create new course object and store it in the sorted dictionary
                Employee employee = list[index];
                //change grade into integer 
                int grade;
                switch (TxtCourseGrade.Text)
                {
                    case "E":
                        grade = 0;
                        break;
                    case "D-":
                        grade = 1;
                        break;
                    case "D":
                        grade = 2;
                        break;
                    case "D+":
                        grade = 3;
                        break;
                    case "C-":
                        grade = 4;
                        break;
                    case "C":
                        grade = 5;
                        break;
                    case "C+":
                        grade = 6;
                        break;
                    case "B-":
                        grade = 7;
                        break;
                    case "B":
                        grade = 8;
                        break;
                    case "B+":
                        grade = 9;
                        break;
                    case "A-":
                        grade = 10;
                        break;
                    case "A":
                        grade = 11;
                        break;
                    case "A+":
                        grade = 12;
                        break;
                    default:
                        grade = 12;
                        break;
                }
                //change hours int integer
                int hours;
                int.TryParse(TxtCourseCredits.Text, out hours);
                Course course = new Course(TxtCourseID.Text, RTBxCourseDesc.Text, grade, TxtCourseDate.Text, hours);
                //add course object to the employee
                employee[course.GetCourseID()] = course;
            }
            ResetGuiCourse();
            
        }
    }
}
