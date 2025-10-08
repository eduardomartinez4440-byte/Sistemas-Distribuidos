package server;

import rmi.EchoInt;

public class EchoObject implements EchoInt {
    public String echo(String msg) {
        return "Server: " + msg;
    }
}
