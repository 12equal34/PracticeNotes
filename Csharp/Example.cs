using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Csharp;

namespace Csharp.DataStructure
{
    namespace Example
    {
        class Stack
        {
            public static void Ex1()
            {
                var s = new DataStructure.Stack<int>();
                s.Push(1);  // {1}
                s.Push(10); // {1,10}
                s.Push(100);// {1,10,100}
                Console.WriteLine(s.Pop()); // {1,10}
                Console.WriteLine(s.Pop()); // {1}
                Console.WriteLine(s.Pop()); // {}
            }
        }
    }
}

namespace Csharp.Algorithm
{
    namespace Example
    {

    }
}


namespace Csharp.CommonExample
{
    
}