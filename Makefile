#partest: partitions_list.o partitions_list_test.o vector_helper.o
#			g++ -o partest partitions_list.o partitions_list_test.o vector_helper.o

fb: partitions_list.o main.o vector_helper.o
			g++ -o fb partitions_list.o main.o vector_helper.o

partitions_list.o: partitions_list.cpp partitions_list.h edmonds_optimum_branching.hpp edmonds_optimum_branching_impl.hpp stl_helpers.h graph_def.h dfs_helpers.h combination_helpers.h
			g++ -c -I/usr/local/boost_1_42_0 partitions_list.cpp
			
#partitions_list_test.o: partitions_list_test.cpp partitions_list.h vector_helper.h stl_helpers.h graph_def.h dfs_helpers.h combination_helpers.h
#			g++ -c -I/usr/local/boost_1_42_0 partitions_list_test.cpp

main.o: main.cpp combination_helpers.h graph_def.h
			g++ -c -I/usr/local/boost_1_42_0 main.cpp
				
vector_helper.o: vector_helper.h vector_helper.cpp
			g++ -c -I/usr/local/boost_1_42_0 vector_helper.cpp
			
clean: 
	rm  partitions_list.o main.o vector_helper.o 