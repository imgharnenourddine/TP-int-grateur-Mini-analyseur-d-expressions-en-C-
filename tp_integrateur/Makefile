CC      = gcc
STD     = -std=c11 -Wall -Wextra -Wpedantic -Werror
SAN     = -fsanitize=address,undefined -fno-omit-frame-pointer -g -O1

.PHONY: all test bench clean
all: test

test:
	$(CC) $(STD) $(SAN) test_stack.c  stack_array.c -o t_stack_array
	$(CC) $(STD) $(SAN) test_stack.c  stack_list.c  -o t_stack_list
	$(CC) $(STD) $(SAN) test_queue.c  queue_circ.c  -o t_queue_circ
	$(CC) $(STD) $(SAN) test_queue.c  queue_list.c  -o t_queue_list
	$(CC) $(STD) $(SAN) test_deque.c  deque_circ.c  -o t_deque_circ
	$(CC) $(STD) $(SAN) test_deque.c  deque_dll.c   -o t_deque_dll
	$(CC) $(STD) $(SAN) test_expr.c expr.c stack_array.c queue_circ.c -o t_expr_array
	$(CC) $(STD) $(SAN) test_expr.c expr.c stack_list.c  queue_list.c -o t_expr_list
	$(CC) $(STD) $(SAN) test_sliding_max.c sliding_max.c deque_circ.c -o t_sliding_circ
	$(CC) $(STD) $(SAN) test_sliding_max.c sliding_max.c deque_dll.c  -o t_sliding_dll
	$(CC) $(STD) $(SAN) test_round_robin.c round_robin.c queue_circ.c -o t_rr_circ
	$(CC) $(STD) $(SAN) test_round_robin.c round_robin.c queue_list.c -o t_rr_list
	$(CC) $(STD) $(SAN) recursion_demo.c stack_array.c -o t_recursion
	./t_stack_array && ./t_stack_list
	./t_queue_circ  && ./t_queue_list
	./t_deque_circ  && ./t_deque_dll
	./t_expr_array  && ./t_expr_list
	./t_sliding_circ && ./t_sliding_dll
	./t_rr_circ && ./t_rr_list
	./t_recursion
	$(CC) $(STD) $(SAN) test_stack_fixed.c -o t_stack_fixed
	$(CC) $(STD) $(SAN) test_palindrome.c palindrome.c stack_array.c queue_circ.c -o t_pal_array
	$(CC) $(STD) $(SAN) test_palindrome.c palindrome.c stack_list.c  queue_list.c -o t_pal_list
	$(CC) $(STD) $(SAN) test_eval_paren.c eval_paren.c stack_array.c -o t_ep_array
	$(CC) $(STD) $(SAN) test_eval_paren.c eval_paren.c stack_list.c  -o t_ep_list
	./t_stack_fixed && ./t_pal_array && ./t_pal_list && ./t_ep_array && ./t_ep_list

bench:
	$(CC) $(STD) -O2 -DIMPL_NAME='"array"' bench.c stack_array.c queue_circ.c -o bench_array
	$(CC) $(STD) -O2 -DIMPL_NAME='"list"'  bench.c stack_list.c  queue_list.c -o bench_list
	./bench_array
	./bench_list

clean:
	rm -f t_* bench_array bench_list
