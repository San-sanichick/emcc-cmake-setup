# kill -9 $(ps -A | grep python | awk '{print $1}')

if type python &> /dev/null;
then
    python server.py
else
    python3 server.py
fi