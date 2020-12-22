using System;
using System.Collections.Generic;
using System.Diagnostics;

namespace Lab_06
{
    class Program
    {
        static List<IRouteAlgorithm> GetAntsAlgorithms(Map map)
        {
            var routeAlgorithms = new List<IRouteAlgorithm>();
            var q = AntsAlgorithm.CalculateQ(map);

            for (double alpha = 0; alpha < 1; alpha += 0.1)
            {
                double beta = 1 - alpha;
                for (double rho = 0; rho < 1; rho += 0.25)
                {
                    routeAlgorithms.Add(new AntsAlgorithm(1000, alpha, beta, q, rho));
                }
            }

            return routeAlgorithms;
        }

        static void Main(string[] args)
        {
            //Map(@"C:\Users\mad-m\source\repos\BMSTU\AnalysisAlgorithms\Lab_06\src\Lab_06\data\map1.txt");
            var map = new Map(9, 10);
            Console.WriteLine(map);

            var routeAlgorithms = new List<IRouteAlgorithm>();
            routeAlgorithms.Add(new BruteForceAlgorithm());
            routeAlgorithms.AddRange(GetAntsAlgorithms(map));

            foreach (var routeAlgorithm in routeAlgorithms)
            {
                var res = routeAlgorithm.GetRoute(map);
                Console.WriteLine(routeAlgorithm.GetType().Name);
                Console.WriteLine("Path: {0}", res);
                Console.WriteLine("Distance: {0}", res.Distance);
                Console.WriteLine();
            }
            Console.WriteLine();

            /*int samples = 1;
            var clock = new Stopwatch();
            foreach (var routeAlgorithm in routeAlgorithms)
            {
                clock.Restart();
                for (int i = 0; i < samples; i++)
                {
                    clock.Start();
                    routeAlgorithm.GetRoute(map);
                    clock.Stop();
                }
                var avgTime = clock.ElapsedTicks / (double)samples;
                Console.WriteLine($"{routeAlgorithm.GetType().Name, -20} time work: {avgTime} ticks");
            }*/
        }
    }
}
