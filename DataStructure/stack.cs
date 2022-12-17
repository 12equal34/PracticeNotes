using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Csharp.DataStructure;

public class Stack<T>
{
    /***********************************
    * Stack<T>
    * |
    * Entry == _top    <== Push(), Pop()
    * |    \
    * T    Entry
    *      |   \
    *      T   Entry
    *          |  \
    *          T   ...
    ***********************************/
    Entry _top;

    public void Push(T data)
    {
        _top = new Entry(_top, data);
    }

    public T Pop()
    {
        if (_top == null)
        {
            throw new InvalidOperationException();
        }
        T result = _top.Data;
        _top = _top.Next;

        return result;
    }

    class Entry
    {   // = {T,Entry{T,Entry{T,...}}}
        public Entry Next { get; set; }
        public T Data { get; set; }

        public Entry(Entry next, T data)
        {
            Next = next;
            Data = data;
        }
    }
}
