/*
Simple C# Serial Number validation.
Console.

Compile:
    $ csc serial.cs
Run:
    $ skeleton
*/

using System;

namespace LearnNetCode
{
    class Skeleton
    {
        static bool check(string order, string serial)
        {
            if (serial.Length != 15)
                return false;

            if (order.Length != 6)
                return false;
            
            if (serial.Substring(0, 3) != "SAP")
                return false;

            if (Int32.Parse(serial.Substring(3, 4)) < Int32.Parse(serial.Substring(5,4)))
                return false;

            if (Int32.Parse(serial.Substring(7, 4)) != 1337)
                return false;

            if (Int32.Parse(order.Substring(2,4)) + 15 != Int32.Parse(serial.Substring(11,4)))
                return false;
            
            return true;
        }

        static void Main(string[] args)
        {
            Console.Write("Masukkan kode order: ");
            string order = Console.ReadLine();
            Console.Write("Masukkan serial: ");
            string serial = Console.ReadLine();

            if (check(order, serial))
            {
                Console.WriteLine("Serial diterima");
            } else {
                Console.WriteLine("Serial ditolak");
            }
        }
    }
}