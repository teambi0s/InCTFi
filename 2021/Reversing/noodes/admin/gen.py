import random

alphabets = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

def get_even_number():
    rand = random.randint(0, len(alphabets) - 1)
    if rand % 2 == 0:
        return rand
    else:
        return rand - 1
    
def get_odd_number():
    rand = random.randint(0, len(alphabets) - 1)
    if rand % 2 != 0:
        return rand
    else:
        return rand - 1

def get_any_number():
    return random.randint(0, len(alphabets) - 1)

def get_random_file():
    return alphabets[get_any_number()] + alphabets[get_odd_number()]

def get_random_dir():    
    return alphabets[get_any_number()] + alphabets[get_even_number()]

def get_any():
    return alphabets[get_any_number()] + alphabets[get_any_number()]

deleted_files = []
deleted_dirs = []
stack_ctr = 0
changed_attributes = []

def main():
    global stack_ctr
    fin = ""
    for i in range(random.randint(150, 200)):
        rand = get_any_number() % 8
        if rand == 1:
            file = get_random_file()

            if file in deleted_files:
                deleted_files.remove(file)
            
            fin += str(rand)
            fin += file
            stack_ctr = stack_ctr + 1
        elif rand == 2:
            if stack_ctr == 0:
                continue
            stack_ctr = stack_ctr - 1
            fin += str(rand)
        elif rand == 3:
            if stack_ctr == 0:
                continue
            fin += str(rand)
        elif rand == 4:
            file = get_random_file()
            
            if file in deleted_files:
                continue

            deleted_files.append(file)
            fin += str(rand)
            fin += file
        elif rand == 5:
            file = get_any()
            if file not in changed_attributes:
                changed_attributes.append(file)

                fin += str(rand)
                fin += file
        elif rand == 6:
            dirt = get_random_dir()
            if dirt in deleted_dirs:
                continue

            deleted_dirs.append(dirt)
            fin += str(rand)
            fin += dirt
        elif rand == 7:
            dirt = get_random_dir()
            
            if dirt not in deleted_dirs:
                continue
            deleted_dirs.remove(dirt)
            fin += str(rand)
            fin += dirt
    fin += "8"
    print(fin)

if __name__ == "__main__":
    main()