import java.rmi.*;
import java.util.*;

public class RMIClient
{
    public static void main(String args[])
    {
        try
        {
            Calculator obj =
            (Calculator) Naming.lookup("rmi://localhost/CalculatorService");

            Scanner input = new Scanner(System.in);

            System.out.println("Choose an operation:");
            System.out.println("1. Addition");
            System.out.println("2. Subtraction");
            System.out.println("3. Multiplication");
            System.out.println("4. Division");
            System.out.print("Enter your choice (1-4): ");
            int choice = input.nextInt();

            System.out.print("Enter first number: ");
            int a = input.nextInt();

            System.out.print("Enter second number: ");
            int b = input.nextInt();

            int result = 0;

            switch (choice)
            {
                case 1:
                    result = obj.add(a, b);
                    System.out.println("Addition = " + result);
                    break;
                case 2:
                    result = obj.subtract(a, b);
                    System.out.println("Subtraction = " + result);
                    break;
                case 3:
                    result = obj.multiply(a, b);
                    System.out.println("Multiplication = " + result);
                    break;
                case 4:
                    result = obj.divide(a, b);
                    System.out.println("Division = " + result);
                    break;
                default:
                    System.out.println("Invalid choice!");
            }
        }
        catch(Exception e)
        {
            System.out.println(e);
        }
    }
}