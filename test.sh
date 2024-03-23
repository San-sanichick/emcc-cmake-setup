# kill -9 $(ps -A | grep python | awk '{print $1}')

if type python &> /dev/null;
then
    # python server.py
    python -m http.server 5000 --directory test
else
    # python3 server.py
    python3 -m http.server 5000 --directory test
fi