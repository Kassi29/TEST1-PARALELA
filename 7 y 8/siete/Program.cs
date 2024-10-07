using System;
using System.Data;
using System.Text.RegularExpressions;

namespace Calculadora
{
    class Program
    {
        static void Main(string[] args)
        {
            string input;
            double result;

            while (true)
            {
                Console.WriteLine("Calculadora - Ingrese una expresión (ej. 3 + 4 * 2) o presione 'k' para salir:");
                input = Console.ReadLine();

                if (input == "k")
                {
                    break;
                }

                try
                {
                    result = EvaluarExpresion(input);
                    Console.WriteLine($"Resultado: {result}");
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"Error: {ex.Message}");
                }
            }
        }

        static double EvaluarExpresion(string expresion)
        {
            // Elimina espacios en blanco
            expresion = expresion.Replace(" ", "");

            // Verifica si hay una división por cero
            if (ContainsDivisionByZero(expresion))
            {
                throw new Exception("Error: División por cero.");
            }

            // Evalúa la expresión, primero resolviendo potencias
            expresion = ResolvePotencias(expresion);

            // Evalúa la expresión restante
            var resultado = new DataTable().Compute(expresion, null);
            return Convert.ToDouble(resultado);
        }

        private static string ResolvePotencias(string expresion)
        {
            // Busca patrones de potencias (ej. 2^3) y los resuelve
            var regex = new Regex(@"(\d+(\.\d+)?)\^(\d+(\.\d+)?)");
            while (regex.IsMatch(expresion))
            {
                expresion = regex.Replace(expresion, match =>
                {
                    double baseNum = Convert.ToDouble(match.Groups[1].Value);
                    double exponent = Convert.ToDouble(match.Groups[3].Value);
                    double power = Math.Pow(baseNum, exponent);
                    return power.ToString();
                });
            }
            return expresion;
        }

        private static bool ContainsDivisionByZero(string expresion)
        {
            // Busca patrones de división por cero
            string[] tokens = expresion.Split(new[] { '+', '-', '*', '/' }, StringSplitOptions.RemoveEmptyEntries);
            for (int i = 0; i < tokens.Length; i++)
            {
                if (i > 0 && expresion[expresion.IndexOf(tokens[i - 1]) + tokens[i - 1].Length] == '/')
                {
                    if (tokens[i] == "0")
                    {
                        return true; // Encontró una división por cero
                    }
                }
            }
            return false;
        }
    }
}
