using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_03_TCO_V1._0
{
    /// <summary>
    /// IFileAccess interface for interaction with files 
    /// </summary>
    interface IFileAccess
    {
        void WriteFileDB();
        void ReadFileDB();
        void OpenFileDB();
        void CloseFileDB();
        SortedDictionary<uint, Employee> employeeList { get; set; }
        
    }
}
