main: hello.o world.o score.o circle.o
	g++ -g hello.o world.o score.o circle.o -lwt -lwthttp -lboost_signals -lboost_thread

refresh: main
	./a.out --docroot . --http-address localhost --http-port 9090

run: main
	/usr/bin/chromium-browser --app=http://localhost:9090/ &
	./a.out --docroot . --http-address localhost --http-port 9090 --accesslog /dev/null

cgi: hello.o world.o score.o circle.o
	g++ hello.o world.o score.o circle.o -lwt -lwtfcgi -lboost_signals -lboost_thread -o graphs.wt -o ~/public_html/graphs/graphs.wt
