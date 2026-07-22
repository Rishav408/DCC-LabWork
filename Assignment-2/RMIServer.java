import java.rmi.*;
import java.rmi.registry.*;

public class RMIServer
{
    public static void main(String args[])
    {
        try
        {
            Calculator obj = new CalculatorImpl();

            LocateRegistry.createRegistry(1099);

            Naming.rebind("CalculatorService", obj);

            System.out.println("RMI Server Ready");
        }
        catch(Exception e)
        {
            System.out.println(e);
        }
    }
}