using System;

namespace Lab_06
{
    class Program
    {
        static void Main(string[] args)
        {
            var routeAlgorithms = new IRouteAlgorithm[]
            {
                new BruteForceAlgorithm(),
                new AntsAlgorithm(30, 0.8, 0.2, 4, 0.1)
            };

            int n = 4; //Convert.ToInt32(Console.ReadLine());

            var map = new Map(@"C:\Users\mad-m\source\repos\BMSTU\AnalysisAlgorithms\Lab_06\src\Lab_06\data\map2.txt");
            Console.WriteLine(map);

            foreach (var routeAlgorithm in routeAlgorithms)
            {
                var res = routeAlgorithm.GetRoute(map);
                Console.WriteLine("Path: {0}", res);
                Console.WriteLine("Distance: {0}", res.Distance);
            }
        }
    }
}
