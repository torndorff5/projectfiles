using System;
using Lab_03_TCO_V1._0;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace UnitTestLab_07
{
    [TestClass]
    public class UnitTestLab_07
    {
        const string TEST_FIRST_NAME = "Tanner";
        const string TEST_LAST_NAME = "Orndorff";
        /// <summary>
        /// Tests the index functions of the Business Rules Class 
        /// </summary>
        [TestMethod]
        public void IndexerTest()
        {
            //arrange
            BusinessRules test = new BusinessRules();
            //act/
            Sales example = new Sales();
            example.SetFirstName(TEST_FIRST_NAME);
            example.SetLastName(TEST_LAST_NAME);
            example.SetEmpID(0);
            test[0] = example;
            //assert that this example and the one stored is the same. 
            Assert.AreEqual(test[0].GetFirstName(), test[1].GetFirstName());
            Assert.AreEqual(test[0].GetLastName(), test[1].GetLastName());

        }
        /// <summary>
        /// Tests to see if indexer can handle a null 
        /// </summary>
        [TestMethod]
        public void NullIndexerTest()
        {
            //arrange 
            BusinessRules test = new BusinessRules();

            //act. //if no error it means that index can't search a null reference 
            if (test[0] == null)
                test[0] = test[1];
        }
    }
}
