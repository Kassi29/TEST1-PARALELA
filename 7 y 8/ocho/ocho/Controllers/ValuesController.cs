using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using System.Data;

namespace ocho.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class CalculadoraController : ControllerBase
    {
        [HttpGet("evaluar")]
        public ActionResult<string> Evaluar(string expresion)
        {
            if (string.IsNullOrWhiteSpace(expresion))
            {
                return BadRequest("La expresión no puede estar vacía.");
            }

            // Elimina espacios en blanco de la expresión
            expresion = expresion.Replace(" ", "");

            // Verifica si hay una división por cero
            if (ContainsDivisionByZero(expresion))
            {
                return BadRequest("Error: División por cero.");
            }

            try
            {
                var resultado = new DataTable().Compute(expresion, null);
                return Convert.ToString(resultado);
            }
            catch (EvaluateException)
            {
                return BadRequest("Expresión inválida.");
            }
            catch (Exception ex)
            {
                return BadRequest($"Error: {ex.Message}");
            }
        }

        private bool ContainsDivisionByZero(string expresion)
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
