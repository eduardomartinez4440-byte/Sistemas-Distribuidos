import java.io.*;
import java.net.*;
import java.util.Scanner;

public class ClienteEntero {
    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Uso: java ClienteEntero <IP_servidor> <puerto>");
            return;
        }

        String ipServidor = args[0];
        int puerto = Integer.parseInt(args[1]);

        try (Socket socket = new Socket(ipServidor, puerto);
             DataOutputStream out = new DataOutputStream(socket.getOutputStream());
             DataInputStream in = new DataInputStream(socket.getInputStream());
             Scanner sc = new Scanner(System.in)) {

            System.out.println("Conectado al servidor " + ipServidor + ":" + puerto);

            int numero;
            do {
                System.out.print("Escribe un número (0 para salir): ");
                numero = sc.nextInt();

                // Enviar número al servidor en network byte order
                out.writeInt(Integer.reverseBytes(numero));

                if (numero != 0) {
                    // Recibir respuesta del servidor
                    int respuesta = Integer.reverseBytes(in.readInt());
                    System.out.println("Servidor respondió: " + respuesta);
                }

            } while (numero != 0);

            System.out.println("Conexión finalizada.");

        } catch (IOException e) {
            System.out.println("Error de conexión: " + e.getMessage());
        }
    }
}
