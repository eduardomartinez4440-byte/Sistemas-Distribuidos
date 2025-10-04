import java.io.*;
import java.net.*;

public class Servidor {
    public static void main(String[] args) {
        int puerto = 5000; // puerto de escucha
        try (ServerSocket serverSocket = new ServerSocket(puerto)) {
            System.out.println("Servidor iniciado en el puerto " + puerto);

            // Esperar conexión de cliente
            Socket socket = serverSocket.accept();
            System.out.println("Cliente conectado: " + socket.getInetAddress());

            // Streams de entrada/salida
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);

            // Leer mensaje del cliente
            String mensajeCliente = in.readLine();
            System.out.println("Cliente dice: " + mensajeCliente);

            // Responder
            String respuesta = "Hola que tal, recibí tu mensaje: " + mensajeCliente;
            out.println(respuesta);

            // Cerrar conexión
            socket.close();
            System.out.println("Conexión cerrada.");

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
