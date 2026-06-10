import 'package:flutter/material.dart';
import './../import/weather_api.dart';
import './../import/weather_model.dart';
import 'package:lottie/lottie.dart';

class WeatherPage extends StatefulWidget {
  const WeatherPage({super.key});
  @override
  State<WeatherPage> createState() => WeatherState();
}

class WeatherState extends State<WeatherPage> {
  //apikey
  final weatherApi = WeatherApi('f355ee2e5f0b39a6b3a6006b58efb239');
  Weather? weather;

  //fetch weather
  fetchWeather() async {
    //get current city
    String cityName = await weatherApi.getCurrentCity();
    try {
      final weatherRecived = await weatherApi.getWeather(cityName);
      setState(() {
        weather = weatherRecived;
      });
    } catch (error) {
      // ignore: avoid_print
      print(error);
    }
  }

  //weathehr animations functions
  String getWeatherAnimation(String? condition) {
    if (condition == null) return "assets/loading.json";

    switch (condition.toLowerCase()) {
      case 'clouds':
      case 'mist':
      case 'smoke':
      case 'haze':
      case 'dust':
      case 'fog':
        return 'assets/cloud.json';
      case 'rain':
      case 'drizzle':
      case 'shower rain':
        return 'assets/thunder.json';
      case 'clear':
        return 'assets/sunny.json';
      default:
        return 'assets/sunny.json';
    }
  }

  //intial state
  @override
  void initState() {
    super.initState();
    fetchWeather();
  }

  //end
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        backgroundColor: const Color.fromARGB(255, 112, 128, 233),
        elevation: 0,
        title: const Text('Weather App'),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            //cityname
            Text(weather?.cityName ?? '...loading city'),
            //animation
            Lottie.asset(getWeatherAnimation(weather?.mainCondition)),
            //temprature
            Text('${weather?.temp.round()}°C'),
            //condition
            Text(weather?.mainCondition ?? "")
          ],
        ),
      ),
    );
  }
}
