import java.rmi.*;
import java.rmi.server.*;

public class CalculatorImpl extends UnicastRemoteObject
        implements Calculator
{
    public CalculatorImpl() throws RemoteException
    {
        super();
    }

    public int add(int a, int b)
    {
        return a + b;
    }

    public int subtract(int a, int b)
    {
        return a - b;
    }

    public int multiply(int a, int b)
    {
        return a * b;
    }

    public int divide(int a, int b)
    {
        return a / b;
    }
}