//Cs file for the FILEIO class.
//Modified by Tanner Orndorff
//10/24/17

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

namespace Lab_03_TCO_V1._0
{
    [Serializable]
    public class FileIO: Object, IFileAccess
    {
        //member variable
        public SortedDictionary<uint, Employee> employeeList { get; set; }
        string filename;
        StreamWriter w;
        StreamReader r;
        Stream f;
        //member functions 
        /// <summary>
        /// Constructor 
        /// </summary>
        /// <param name="fname">name of file that we wish to work with/absolute path</param>
        /// <param name="EmployeeDB"></param>
        public FileIO(string fname, SortedDictionary<uint, Employee> employeeDB)
        {
            filename = fname;
            employeeList = employeeDB;
        }
        /// <summary>
        /// Writes the contents of sorted dictionary to an open file. FILE MUST BE SUCCESSFULLY OPENED 
        /// </summary>
        public void WriteFileDB()
        {
            //open file
            OpenFileDB();
            //serialize data
            
            BinaryFormatter binform = new BinaryFormatter();
            
            binform.Serialize(f, employeeList);
        
            //write to file??
            w = new StreamWriter(f);
            foreach(KeyValuePair<uint,Employee> employee in employeeList)
            {
                w.WriteLine(employee);
            }
            //close file 
            CloseFileDB();
            
        }
        /// <summary>
        /// Takes the Data from the file and stores it into the Employee Database 
        /// </summary>
        public void ReadFileDB()
        {
            //open file
            OpenFileDB();
            //read data
            r = new StreamReader(f);
            //deserialize data
            BinaryFormatter binform = new BinaryFormatter();
            //store into employeelist 
            employeeList = (SortedDictionary < uint, Employee > )binform.Deserialize(f);
            //close file
            CloseFileDB();
        }
        /// <summary>
        /// opens file passed into this class (filename in folder / absolute path)
        /// </summary>
        public void OpenFileDB()
        {
            f = File.Open(filename, FileMode.OpenOrCreate);
            //f = new FileStream(filename, FileMode.OpenOrCreate);
           
        }
        /// <summary>
        /// Closes the file passed into this class by name
        /// </summary>
        public void CloseFileDB()
        {
            if (f != null)
            {
                f.Close();
                f.Dispose();
            }
        }
        
    }
}
