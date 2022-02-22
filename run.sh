echo "Compiling...";
clang++ -Wall -Werror -Wextra -std=c++98 -D NS=0 main.cpp -o test_ft;
clang++ -Wall -Werror -Wextra -std=c++98 -D NS=1 main.cpp -o test_stl;
echo "Done.";
echo "Running for diff...";
./test_ft 123456 > test_ft.output;
./test_stl 123456 > test_stl.output;
diff test_ft.output test_stl.output > diff.output;
echo "Done."
echo "diff.output (should be empty): "
cat diff.output
echo "Testing speed..."
echo "FT:"
time ./test_ft 123456 > /dev/null
echo "STL:"
time ./test_stl 123456 > /dev/null
echo "Done."