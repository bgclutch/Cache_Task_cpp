import random
import time

random.seed(time.time())
test_num = 10

for cur_num in range (1, test_num + 1):
    new_file = f"input_files/test_{cur_num:02}.in"

    cache_size = random.randint(100, 3000)
    elems_number = random.randint(100000, 300000)

    file_input = str(cache_size) + " " + str(elems_number) + "\n"

    with open(new_file, 'w') as file:

        for _ in range (elems_number):
            file_input += str(int(random.gauss(100000, 1000))) + " "
        file.write(file_input)
