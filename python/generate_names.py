import random

# 中文名字列表
chinese_surnames = ["王", "李", "张", "刘", "陈", "杨", "赵", "黄", "周", "吴"]
chinese_names = ["伟", "芳", "娜", "敏", "静", "丽", "强", "磊", "军", "洋"]

# 英文名字列表
english_first_names = ["James", "Mary", "John", "Patricia", "Robert", "Jennifer", "Michael", "Linda", "William", "Elizabeth"]
english_last_names = ["Smith", "Johnson", "Williams", "Brown", "Jones", "Garcia", "Miller", "Davis", "Rodriguez", "Martinez"]

def generate_chinese_name():
    surname = random.choice(chinese_surnames)
    name = random.choice(chinese_names)
    return surname + name

def generate_english_name():
    first_name = random.choice(english_first_names)
    last_name = random.choice(english_last_names)
    return first_name + " " + last_name

def generate_names(count):
    names = []
    for _ in range(count):
        if random.choice([True, False]):
            names.append(generate_chinese_name())
        else:
            names.append(generate_english_name())
    return names

if __name__ == "__main__":
    names = generate_names(800)
    for name in names:
        print(name)
