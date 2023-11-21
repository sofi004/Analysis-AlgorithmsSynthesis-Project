
project: project.cpp
	g++ project.cpp -o project 

run: project teste.in
	@./project < teste.in
