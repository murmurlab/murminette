#!/usr/bin/env bash
set -euo pipefail

echo "Starting get_next_line tests... $2"
cd "$2"

# Compile and run tests across multiple BUFFER_SIZE values
buffer_sizes=(1 2 3 4 5 6 7 8 9 10 11 13 17 21 16 42 51 127 255 1024 10000000)

declare -a tests_in
declare -a tests_out
declare -a test_lens

# Helper to build repeated characters
repeat_chars() {
    local ch="$1"; local count="$2"; local out=""
    for _ in $(seq 1 "$count"); do out+="$ch"; done
    printf "%s" "$out"
}

# Original tests
tests_in+=( $'0000000000000000000000000000000000000000000000000000
aaaaaaaaaaaaaa
bbb
cccccccccccccccccccc
1
yyyy
yyyyyyyyyyyyyyy
y
y

xxxx' )
tests_out+=( $'0000000000000000000000000000000000000000000000000000
aaaaaaaaaaaaaa
bbb
cccccccccccccccccccc
1
yyyy
yyyyyyyyyyyyyyy
y
y

xxxx(null)
(null)' )
test_lens+=( 13 )

tests_in+=( $'a' )
tests_out+=( $'a(null)' )
test_lens+=( 2 )

# Additional edge-case tests

# 3) Empty input
tests_in+=( $'' )
tests_out+=( $'(null)' )
test_lens+=( 1 )

# 4) Single newline
tests_in+=( $'\n' )
tests_out+=( $'\n(null)' )
test_lens+=( 2 )

# 5) Single char with trailing newline
tests_in+=( $'a\n' )
tests_out+=( $'a\n(null)' )
test_lens+=( 2 )

# 6) Two lines with final newline
tests_in+=( $'abc\ndef\n' )
tests_out+=( $'abc\ndef\n(null)' )
test_lens+=( 3 )

# 7) Two lines without final newline
tests_in+=( $'abc\ndef' )
tests_out+=( $'abc\ndef(null)' )
test_lens+=( 3 )

# 8) Multiple empty lines
tests_in+=( $'\n\n\n' )
tests_out+=( $'\n\n\n(null)' )
test_lens+=( 4 )

# 9) Very long line without newline (500 x)
long500=$(repeat_chars x 500)
tests_in+=( "$long500" )
tests_out+=( "$long500(null)" )
test_lens+=( 2 )

# 10) Exactly 42 chars with newline
exact42=$(repeat_chars x 42)$'\n'
tests_in+=( "$exact42" )
tests_out+=( $(repeat_chars x 42)$'\n(null)' )
test_lens+=( 2 )

# 11) Exactly 42 chars without newline
exact42_no_nl=$(repeat_chars x 42)
tests_in+=( "$exact42_no_nl" )
tests_out+=( $(repeat_chars x 42)$'(null)' )
test_lens+=( 2 )

# 12) Line exactly BUFFER_SIZE-1 chars with newline
exact41=$(repeat_chars y 41)$'\n'
tests_in+=( "$exact41" )
tests_out+=( $(repeat_chars y 41)$'\n(null)' )
test_lens+=( 2 )

# 13) Line exactly BUFFER_SIZE+1 chars with newline
exact43=$(repeat_chars z 43)$'\n'
tests_in+=( "$exact43" )
tests_out+=( $(repeat_chars z 43)$'\n(null)' )
test_lens+=( 2 )

# 14) Multiple consecutive newlines at different positions
tests_in+=( $'start\n\n\nmiddle\n\n\nend' )
tests_out+=( $'start\n\n\nmiddle\n\n\nend(null)' )
test_lens+=( 8 )

# 15) Very long line with newline (1000 chars)
long1000=$(repeat_chars a 1000)$'\n'
tests_in+=( "$long1000" )
tests_out+=( $(repeat_chars a 1000)$'\n(null)' )
test_lens+=( 2 )

# 16) Mix of short and long lines
tests_in+=( $'short\nvery_long_line_'$(repeat_chars x 200)$'\nmedium_line\na\n' )
tests_out+=( $'short\nvery_long_line_'$(repeat_chars x 200)$'\nmedium_line\na\n(null)' )
test_lens+=( 5 )

# 17) Only spaces and tabs
tests_in+=( $'   \n\t\t\n \t \n' )
tests_out+=( $'   \n\t\t\n \t \n(null)' )
test_lens+=( 4 )

# 18) Special characters
tests_in+=( $'line1!@#$%^&*()\nline2<>?:"{}\n' )
tests_out+=( $'line1!@#$%^&*()\nline2<>?:"{}\n(null)' )
test_lens+=( 3 )

# 19) Alternating single char and newline
tests_in+=( $'a\nb\nc\nd\ne\n' )
tests_out+=( $'a\nb\nc\nd\ne\n(null)' )
test_lens+=( 6 )

# 20) Line with exactly BUFFER_SIZE*2 chars
exact84=$(repeat_chars m 84)$'\n'
tests_in+=( "$exact84" )
tests_out+=( $(repeat_chars m 84)$'\n(null)' )
test_lens+=( 2 )

# 21) Line with exactly BUFFER_SIZE*3 chars
exact126=$(repeat_chars n 126)$'\n'
tests_in+=( "$exact126" )
tests_out+=( $(repeat_chars n 126)$'\n(null)' )
test_lens+=( 2 )

# 22) Multiple reads beyond EOF
tests_in+=( $'single_line\n' )
tests_out+=( $'single_line\n(null)
(null)
(null)' )
test_lens+=( 4 )

# 23) Lines with different lengths in sequence
tests_in+=( $'1\n22\n333\n4444\n55555\n' )
tests_out+=( $'1\n22\n333\n4444\n55555\n(null)' )
test_lens+=( 6 )

# 24) Very long line without newline (10000 chars) - stress test
long10000=$(repeat_chars b 10000)
tests_in+=( "$long10000" )
tests_out+=( "$long10000(null)" )
test_lens+=( 2 )

output_path="./outputs/"
leaks_path="./leaks/"
mkdir -p "$output_path" "$leaks_path"
for bs in "${buffer_sizes[@]}"; do

	(
		# echo "====================="
		# echo "BUFFER_SIZE=$bs"
		# echo "Compiling test harness..."
		cc -g "$1" -I. get_next_line.c get_next_line_utils.c -D BUFFER_SIZE="$bs" -o test_"BUFFER_SIZE=$bs" &> /dev/null
		for ((i=0; i<${#tests_in[@]}; i++)); do
			(
				echo "---------------------"
				echo "Test $((i+1)):"
				echo "---------------------"
				out=$(echo -en "${tests_in[i]}" | valgrind --leak-check=full ./test_"BUFFER_SIZE=$bs" 0 "${test_lens[i]}" 2>"${leaks_path}BUFFER_SIZE=$bs"_$i\_results.txt)
				echo "Input:"
				expected="${tests_out[i]}"
				if [ "$out" == "$expected" ]; then
					echo "Test $((i+1)) passed."
				else
					echo "Test $((i+1)) failed."
					echo "Expected output:"
					echo -e ">>>$expected<<<"
					echo "Actual output:"
					echo -e ">>>$out<<<"
				fi

				if grep -q "All heap blocks were freed -- no leaks are possible" "${leaks_path}BUFFER_SIZE=$bs"_$i\_results.txt; then
					echo "No memory leaks detected."
					rm "${leaks_path}BUFFER_SIZE=$bs"_$i\_results.txt
				else
					echo "Memory leaks detected! See ${leaks_path}BUFFER_SIZE=$bs"_$i\_results.txt" for details."
				fi
			)
		done >"${output_path}BUFFER_SIZE=$bs"_results.txt
		rm ./test_"BUFFER_SIZE=$bs"
		if grep -q "failed" "${output_path}BUFFER_SIZE=$bs"_results.txt || \
			grep -q "SIGSEGV" "${output_path}BUFFER_SIZE=$bs"_results.txt || \
			grep -q "Invalid" "${output_path}BUFFER_SIZE=$bs"_results.txt || \
			grep -q "Memory leaks detected" "${output_path}BUFFER_SIZE=$bs"_results.txt; then
			echo "FAILED: ${output_path}BUFFER_SIZE=${bs}_results.txt"
		else
			echo "All tests passed for BUFFER_SIZE=$bs"
			rm "${output_path}BUFFER_SIZE=$bs"_results.txt
		fi
	)&
done

wait
