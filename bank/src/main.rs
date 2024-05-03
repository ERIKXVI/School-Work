use iced::{
    button, Alignment, Application, Button, Column, Command, Element, Settings, Size, Text,
    WindowSettings,
};

#[derive(Default)]
pub struct Counter {
    value: i32,
    increment_button_state: button::State,
    decrement_button_state: button::State,
}

#[derive(Debug, Clone, Copy)]
pub enum Message {
    Increment,
    Decrement,
}

impl Application for Counter {
    type Executor = iced::executor::Default;
    type Message = Message;
    type Flags = ();

    fn new(_flags: ()) -> (Counter, Command<Message>) {
        (Counter::default(), Command::none())
    }

    fn title(&self) -> String {
        String::from("Counter")
    }

    fn update(&mut self, message: Message) -> Command<Message> {
        match message {
            Message::Increment => self.value += 1,
            Message::Decrement => self.value -= 1,
        }

        Command::none()
    }

    fn view(&mut self) -> Element<Message> {
        let increment_button = Button::new(&mut self.increment_button_state)
            .text("Increment")
            .on_press(Message::Increment);

        let decrement_button = Button::new(&mut self.decrement_button_state)
            .text("Decrement")
            .on_press(Message::Decrement);

        Column::new()
            .push(increment_button)
            .push(decrement_button)
            .push(Text::new(self.value.to_string()))
            .align_items(Alignment::Center) // Center the buttons horizontally
            .into()
    }
}

fn main() -> iced::Result {
    Counter::run(Settings {
        window: WindowSettings {
            size: Size::new(800.0, 600.0), // Set the window size to 800x600
            resizable: false,              // Make the window not resizable
            ..Default::default()
        },
        ..Default::default()
    })
}
