use reqwest::blocking::Client;
use rocket::form::Form;
use rocket::get;
use rocket::routes;
use rocket::serde::json::Json;
use serde::{Deserialize, Serialize};

#[derive(Serialize, Deserialize, Debug)]
struct WeatherResponse {
    name: String,
    temp: f32,
    description: String,
    // Expand for desired data
}

#[get("/weather?city=<city_name>")]
fn get_weather(city_name: Form<String>) -> Result<Json<WeatherResponse>, String> {
    let api_key = "YOUR_OPENWEATHERMAP_API_KEY";
    let url = format!(
        "https://api.openweathermap.org/data/2.5/weather?q={}&appid={}",
        city_name.into_inner(),
        api_key
    );

    let client = Client::new();
    let response = client.get(url).send().map_err(|e| e.to_string())?;

    if response.status().is_success() {
        let weather_data: WeatherResponse = response.json().map_err(|e| e.to_string())?;
        Ok(Json(weather_data))
    } else {
        Err("Weather data not found".to_string())
    }
}

#[rocket::launch]
fn rocket() -> _ {
    rocket::build().mount("/", routes![get_weather])
}

fn main() {
    rocket();
}
