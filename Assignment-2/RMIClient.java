import java.rmi.*;

public class RMIClient
{
    public static void main(String args[])
    {
        try
        {
            Calculator obj =
            (Calculator) Naming.lookup("rmi://localhost/CalculatorService");

            int addition = obj.add(20, 30);
            int subtraction = obj.subtract(50, 20);
            int multiplication = obj.multiply(6, 7);
            int division = obj.divide(40, 5);

            System.out.println("Addition = " + addition);
            System.out.println("Subtraction = " + subtraction);
            System.out.println("Multiplication = " + multiplication);
            System.out.println("Division = " + division);
        }
        catch(Exception e)
        {
            System.out.println(e);
        }
    }
}