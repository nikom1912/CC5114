@FunctionalInterface
public interface MyFunction<A,B,C> {
    public C apply(A a, B b) throws ArithmeticException;
}
