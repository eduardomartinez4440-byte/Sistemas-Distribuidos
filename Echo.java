package client;

import server.EchoObject;  // Importar la clase del servidor directamente

public class Echo {
    private static EchoObject ss;

    public static void main(String[] args) {
        ss = new EchoObject();  // Crear el objeto directamente (sin stub)
        System.out.println(ss.echo("Hola desde el cliente"));
    }
}
