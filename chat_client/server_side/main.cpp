#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <deque>
#include <list>
#include <set>
#include <memory>

using boost::asio::ip::tcp;

typedef std::deque<std::string> chat_message_queue;

class chat_participant
{
public:
    virtual ~chat_participant() {}
    virtual void deliver(const std::string& msg) = 0;
    std::string username;
};

typedef std::shared_ptr<chat_participant> chat_participant_ptr;

class chat_room
{
public:
    void join(chat_participant_ptr participant)
    {
        participants_.insert(participant);
        std::for_each(recent_msgs_.begin(), recent_msgs_.end(),
            boost::bind(&chat_participant::deliver, participant, _1));
        print_participants();
    }

    void leave(chat_participant_ptr participant)
    {
        participants_.erase(participant);
        print_participants();
    }

    void deliver(const std::string& msg)
    {
        recent_msgs_.push_back(msg);
        while (recent_msgs_.size() > max_recent_msgs)
            recent_msgs_.pop_front();

        std::for_each(participants_.begin(), participants_.end(),
            boost::bind(&chat_participant::deliver, _1, boost::ref(msg)));
    }

    void print_participants()
    {
        std::cout << "Connected users:\n";
        for (const auto& participant : participants_)
        {
            std::cout << participant->username << "\n";
        }
    }

private:
    std::set<chat_participant_ptr> participants_;
    enum { max_recent_msgs = 100 };
    chat_message_queue recent_msgs_;
};

class chat_session : public chat_participant, public std::enable_shared_from_this<chat_session>
{
public:
    chat_session(boost::asio::io_service& io_service, chat_room& room)
        : socket_(io_service),
        room_(room)
    {
    }

    tcp::socket& socket()
    {
        return socket_;
    }

    void start()
    {
        room_.join(shared_from_this());
        boost::asio::async_read_until(socket_, input_buffer_, "\n",
            boost::bind(&chat_session::handle_read, shared_from_this(),
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }

    void deliver(const std::string& msg)
    {
        bool write_in_progress = !message_queue_.empty();
        message_queue_.push_back(msg);
        if (!write_in_progress)
        {
            boost::asio::async_write(socket_,
                boost::asio::buffer(message_queue_.front() + "\n"),
                boost::bind(&chat_session::handle_write, shared_from_this(),
                    boost::asio::placeholders::error));
        }
    }

    void handle_read(const boost::system::error_code& error, size_t bytes_transferred)
    {
        if (!error)
        {
            std::string msg;
            std::istream is(&input_buffer_);
            std::getline(is, msg);
            if (username.empty())
            {
                username = msg;
            }
            else
            {
                room_.deliver(msg);
            }
            boost::asio::async_read_until(socket_, input_buffer_, "\n",
                boost::bind(&chat_session::handle_read, shared_from_this(),
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
        }
        else
        {
            room_.leave(shared_from_this());
        }
    }

    void handle_write(const boost::system::error_code& error)
    {
        if (!error)
        {
            message_queue_.pop_front();
            if (!message_queue_.empty())
            {
                boost::asio::async_write(socket_,
                    boost::asio::buffer(message_queue_.front() + "\n"),
                    boost::bind(&chat_session::handle_write, shared_from_this(),
                        boost::asio::placeholders::error));
            }
        }
        else
        {
            room_.leave(shared_from_this());
        }
    }

private:
    tcp::socket socket_;
    chat_room& room_;
    boost::asio::streambuf input_buffer_;
    chat_message_queue message_queue_;
};

typedef boost::shared_ptr<chat_session> chat_session_ptr;

class chat_server
{
public:
    chat_server(boost::asio::io_service& io_service,
        const tcp::endpoint& endpoint)
        : io_service_(io_service),
        acceptor_(io_service, endpoint)
    {
        start_accept();
    }

    void start_accept()
    {
        chat_session_ptr new_session(new chat_session(io_service_, room_));
        acceptor_.async_accept(new_session->socket(),
            boost::bind(&chat_server::handle_accept, this, new_session,
                boost::asio::placeholders::error));
    }

    void handle_accept(chat_session_ptr session,
        const boost::system::error_code& error)
    {
        if (!error)
        {
            boost::asio::post(io_service_,
                boost::bind(&chat_session::start, session));
            start_accept();
        }
    }

    void start_session(chat_session_ptr session)
    {
        session->start();
        start_accept();
    }

private:
    boost::asio::io_service& io_service_;
    tcp::acceptor acceptor_;
    chat_room room_;
};

int main(int argc, char* argv[])
{
    try
    {
        if (argc < 2)
        {
            std::cerr << "Usage: chat_server <port> [<port> ...]\n";
            return 1;
        }

        boost::asio::io_service io_service;
        boost::asio::io_service::work work(io_service);  // Add this line

        std::list<chat_server> servers;
        for (int i = 1; i < argc; ++i)
        {
            tcp::endpoint endpoint(tcp::v4(), std::atoi(argv[i]));
            servers.emplace_back(io_service, endpoint);
            std::cout << "Server is running on " << endpoint << "\n";
        }

        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}