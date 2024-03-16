import http.server
import socketserver
import os


PORT = 5000

directory = os.path.join(os.path.dirname(__file__), "test")
os.chdir(directory)

handler = http.server.SimpleHTTPRequestHandler
httpd = socketserver.TCPServer(("", PORT), handler)

print("Serving on " + str(PORT))

httpd.serve_forever()