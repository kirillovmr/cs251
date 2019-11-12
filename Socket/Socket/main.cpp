#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace boost;

void readLine(asio::ip::tcp::socket &socket) {
    asio::streambuf buffer;
    
    std::size_t n = asio::read_until(socket, buffer, '\r');
    asio::streambuf::const_buffers_type bufs = buffer.data();
    std::string line( asio::buffers_begin(bufs), asio::buffers_begin(bufs)+n);
    
    cout << "Res: " << line << endl;
}

void writeLine(asio::ip::tcp::socket &socket, std::string line) {
    asio::write(socket, asio::buffer(line));
}

void readLine2(asio::ip::tcp::socket &socket) {
    const unsigned char MESSAGE_SIZE = 20;
    char buf[MESSAGE_SIZE];

    asio::read(socket, asio::buffer(buf, MESSAGE_SIZE));
    cout << "Readed: " << buf << endl;
}

struct Handler {
    asio::ip::tcp::socket *m_socket;
    std::string input;
    
    Handler(asio::ip::tcp::socket &socket) {
        m_socket = &socket;
    }
    
    void operator()(system::error_code error) {
        if (!error) {
            cout << "Connected.\n";
            writeLine(*m_socket, "Wassup");
            
            // Shutting down the socket to let the
            // server know that we've sent the whole
            // request.
            m_socket->shutdown(asio::socket_base::shutdown_send);
            
            readLine(*m_socket);
            cin >> input;
        }
        else {
            cout << "Error connecting: " << error.message() << endl;
        }
    }
};

int main(int argc, const char *argv[]) {
    
    if (argc > 1) {
        if (string(argv[1]) == "-c") {
            cout << "Running Client instance" << endl;
            
            
            asio::io_context io_context;
            asio::ip::tcp::socket socket(io_context);
            asio::ip::tcp::endpoint endp = asio::ip::tcp::endpoint(asio::ip::address::from_string(argv[2]), atoi(argv[3]));
            cout << "Connecting to " << endp << endl;
            
            Handler handler(socket);
            socket.async_connect(endp, handler);
            
            // run() method blocks, as long as, at least one pending asynchronous operation.
            // When the last callback of the last pending asynchronous operation is completed,
            // this method returns.
            io_context.run();
            
            // Returning memory to OS
            // But no need to do that. Destructor cares about that
            socket.close();
        }
        
        if (string(argv[1]) == "-s") {
            cout << "Running Server instance" << endl;
            
            asio::io_service ios;
            asio::ip::tcp::endpoint ep(asio::ip::address_v4::any(), atoi(argv[2]));
            
            // Step 3. Creating and opening an acceptor socket.
            asio::ip::tcp::acceptor acceptor(ios, ep.protocol());
            
            boost::system::error_code ec;
            
            // Step 4. Binding the acceptor socket.
            acceptor.bind(ep, ec);
            
            // Handling errors if any.
            if (ec) {
                // Failed to bind the acceptor socket. Breaking execution.
                std::cout << "Failed to bind the acceptor socket."
                    << "Error code = " << ec.value() << ". Message: "
                    << ec.message();

                return ec.value();
            }
            
            // The size of the queue containing the pending connection requests.
            const int BACKLOG_SIZE = 30;
            
            // Step 5. Starting to listen for incoming connection requests.
            acceptor.listen(BACKLOG_SIZE);
            
            cout << "Server running on " << ep << endl;
            
            // Step 6. Creating an active socket.
            asio::ip::tcp::socket sock(ios);
            
            // Step 7. Processing the next connection request and
            //          connecting the active socket to the client.
            acceptor.accept(sock);
            
            cout << sock.remote_endpoint() << " is connected." << endl;
            
            string input;
            cin >> input;
        }
    }
    
    cout << "done" << endl;
    
    return 0;
}
