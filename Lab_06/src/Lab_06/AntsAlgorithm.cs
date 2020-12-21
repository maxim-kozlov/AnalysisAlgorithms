using System;
using System.Collections.Generic;
using System.Text;

namespace Lab_06
{
    public class AntsAlgorithm : IRouteAlgorithm
    {
        public AntsAlgorithm(int maxTime, double alpha, double beta, double q, double pho)
        {
            MaxTime = maxTime;
            Alpha = alpha;
            Beta = beta;
            Q = q;
            Pho = pho;
        }

        public int MaxTime { get; set; }
        public double Alpha { get; set; }
        public double Beta { get; set; }
        public double Q { get; set; }
        public double Pho { get; set; }


        public Path GetRoute(Map map)
        {
            Random r = new Random();
            Path shortest = new Path(null, map);

            int count = map.N;
            double[,] pher = InitPheromone(0.1, count);

            for (int time = 0; time < MaxTime; time++)
            {
                var ants = InitAnts(map);
                for (int i = 0; i < count - 1; i++)
                {
                    double[,] deltaPher = InitPheromone(0, count);
                    foreach (var ant in ants)
                    {
                        int curTown = ant.LastVisited();

                        double sum = 0;
                        for (int town = 0; town < count; town++)
                        {
                            if (!ant.IsVisited(town))
                            {
                                double tau = pher[curTown, town];
                                double eta = 1 / map[curTown, town];
                                sum += Math.Pow(tau, Alpha) * Math.Pow(eta, Beta);
                            }
                        }

                        double check = r.NextDouble();
                        int newTown = 0;
                        for (; check > 0; newTown++)
                        {
                            if (!ant.IsVisited(newTown))
                            {
                                double tau = pher[curTown, newTown];
                                double eta = 1 / map[curTown, newTown];
                                double chance = Math.Pow(tau, Alpha) * Math.Pow(eta, Beta) / sum;
                                check -= chance;
                            }
                        }
                        newTown--;
                        ant.VisitTown(newTown);
                        deltaPher[curTown, newTown] += Q / map[curTown, newTown];
                    }
                    for (int k = 0; k < count; k++)
                        for (int t = 0; t < count; t++)
                            pher[k, t] = (1 - Pho) * pher[k, t] + deltaPher[k, t];
                }
                foreach (var ant in ants)
                {
                    ant.VisitTown(ant.Start);
                    if (ant.GetDistance() < shortest.Distance)
                        shortest = ant.Path;
                }
            }

            return shortest;
        }

        private List<Ant> InitAnts(Map map)
        {
            var ants = new List<Ant>(map.N);
            for (int i = 0; i < map.N; i++)
                ants.Add(new Ant(map, i));
            return ants;
        }

        private double[,] InitPheromone(double num, int size)
        {
            double[,] phen = new double[size, size];
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    phen[i, j] = num;
            return phen;
        }
    }
}
