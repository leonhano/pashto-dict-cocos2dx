using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace TrimTest
{
    class Program
    {
        static void Main(string[] args)
        {
               //string test = "افغان $afg̠hān $Afghan$ a citizen of Afghanistan$$$$$$$";               
               //string trimTest = ReplaceAllCharaters(test, " $", "$"); 
// 
// 
            string filename = "D:\\Code\\Mobile\\cocos2d-x-2.2.3\\projects\\PashtoDictionary\\Resources\\Pashto_English_Data\\part1.csv";
            string outputFilename = "D:\\Code\\Mobile\\cocos2d-x-2.2.3\\projects\\PashtoDictionary\\Resources\\Pashto_English_Data\\part1_filtered.csv";
            List<string> sourceList = ReadAllLines(filename);
            List<string> outList = new List<string>();
            foreach (string src in sourceList)
            {
                string filteredStr = ReplaceAllCharaters(src, " $", "$");
                filteredStr = ReplaceAllCharaters(filteredStr, " $", "$");
                filteredStr = ReplaceAllCharaters(filteredStr, " $", "$");
                outList.Add(filteredStr);
            }

            Console.WriteLine("write lines: " + outList.Count);

            File.WriteAllLines(outputFilename, outList);
            
            //Console.WriteLine(trimTest);

            // Suspend the screen.
            Console.ReadLine();
        }

        static List<string> ReadAllLines(string filename)
        {
            int counter = 0;
            string line;

            List<string> lineList = new List<string>();

            // Read the file and display it line by line.
            System.IO.StreamReader file =
               new System.IO.StreamReader(filename);
            while ((line = file.ReadLine()) != null)
            {
                //Console.WriteLine(line);
                lineList.Add(line);
                counter++;
            }

            file.Close();

            Console.WriteLine("read lines: " + counter);

            // Suspend the screen.
            //Console.ReadLine();
            return lineList;
        }

        static string ReplaceAllCharaters(string source, string oldStr, string replacedStr)
        {
            string newStr = source;

            while (newStr.Contains(oldStr))
            {
                newStr = newStr.Replace(oldStr, replacedStr);
            }
            return newStr;
        }
    }
}
