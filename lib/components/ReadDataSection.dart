import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:google_fonts/google_fonts.dart';
import 'package:ionicons/ionicons.dart';
import 'package:sonda_projekt/components/DataTile.dart';

class ReadDataSection extends StatefulWidget {
  final double phValue;
  final Function readSensorsData;
  const ReadDataSection(
      {Key? key, required this.phValue, required this.readSensorsData})
      : super(key: key);

  @override
  State<ReadDataSection> createState() => _ReadDataSectionState();
}

class _ReadDataSectionState extends State<ReadDataSection> {
  @override
  Widget build(BuildContext context) {
    return Column(
      mainAxisAlignment: MainAxisAlignment.start,
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        Row(
          mainAxisAlignment: MainAxisAlignment.spaceBetween,
          children: [
            Text("Czujniki:",
                style: GoogleFonts.manrope(
                    fontWeight: FontWeight.bold,
                    fontSize: 24,
                    textStyle: TextStyle(color: const Color(0xff323232)))),
            IconButton(
                onPressed: () => widget.readSensorsData(),
                icon: Icon(Ionicons.refresh))
          ],
        ),
        Column(
          children: [
            DataTile(
                data: "${widget.phValue}",
                title: "Czujnik PH",
                icon: CupertinoIcons.thermometer,
                isPrimary: true),
            SizedBox(height: 12),
            DataTile(
                data: "16*C",
                title: "Temperatura wody",
                icon: CupertinoIcons.thermometer,
                isPrimary: false),
          ],
        )
      ],
    );
  }
}
