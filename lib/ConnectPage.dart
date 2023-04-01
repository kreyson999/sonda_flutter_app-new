import 'package:flutter/material.dart';
import 'package:flutter_bluetooth_serial/flutter_bluetooth_serial.dart';
import 'package:google_fonts/google_fonts.dart';
import 'package:sonda_projekt/HomePage.dart';

class ConnectPage extends StatefulWidget {
  const ConnectPage({Key? key}) : super(key: key);

  @override
  State<ConnectPage> createState() => _ConnectPageState();
}

class _ConnectPageState extends State<ConnectPage> {
  final Future<BluetoothDevice> _getDevice =
      FlutterBluetoothSerial.instance.getBondedDevices().then((value) {
    // print(value[0].name);
    return value[0];
  });

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        body: Scaffold(
            body: Padding(
      padding: const EdgeInsets.only(left: 20, right: 20, top: 50),
      child: Column(
        mainAxisAlignment: MainAxisAlignment.start,
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Container(
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Text("Sonda",
                    style: GoogleFonts.manrope(
                        fontWeight: FontWeight.bold,
                        fontSize: 32,
                        textStyle: TextStyle(color: const Color(0xff323232)))),
                Text("Centrum Sterowania",
                    style: GoogleFonts.manrope(
                        fontSize: 16,
                        textStyle: TextStyle(color: const Color(0xff575757))))
              ],
            ),
          ),
          FutureBuilder(
            future: _getDevice,
            builder: (context, AsyncSnapshot<BluetoothDevice> snapshot) {
              if (snapshot.connectionState == ConnectionState.waiting) {
                return Padding(
                  padding: const EdgeInsets.only(top: 20),
                  child: CircularProgressIndicator(
                    valueColor:
                        AlwaysStoppedAnimation<Color>(const Color(0xffFF7D40)),
                  ),
                );
              }
              if (snapshot.hasData) {
                print(snapshot.data);
                return HomePage(server: snapshot.data!);
              }
              return Padding(
                padding: const EdgeInsets.only(top: 20),
                child: Text(
                    "Wystąpił błąd, upewnij się, że masz włączone Bluetooth i jesteś zparowany z Sondą!",
                    style: GoogleFonts.manrope(
                        fontSize: 16,
                        textStyle: TextStyle(color: const Color(0xff575757)))),
              );
            },
          ),
        ],
      ),
    )));
  }
}
