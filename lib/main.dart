import 'package:flutter/material.dart';
import 'package:sonda_projekt/ConnectPage.dart';

void main() => runApp(new ExampleApplication());

class ExampleApplication extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(home: ConnectPage());
  }
}
