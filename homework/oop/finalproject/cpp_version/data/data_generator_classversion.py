import random
import os
import sys
import re

# 文件路径
testfile = "testoutput.txt"
user_file = "user_data.txt"
ruku_package_file = "contained_package_data.txt"
daishou_package_file = "package_daishou_data.txt"
out_package_file = "package_out_data.txt"
worker_file = "worker_data.txt"

user_count = 10
ruku_package_count = 550
daishou_package_count = 30
out_package_count = 30
worker_count = 10


class Generate:

    def __init__(self, user_count, ruku_package_count, daishou_package_count,
                 out_package_count, worker_count):
        self.user_count = user_count
        self.ruku_package_count = ruku_package_count
        self.daishou_package_count = daishou_package_count
        self.out_package_count = out_package_count
        self.worker_count = worker_count

        # 初始化数据
        self.chinese_surnames = [
            "王", "李", "张", "刘", "陈", "杨", "赵", "黄", "周", "吴"
        ]
        self.chinese_names = ["伟", "芳", "娜", "敏", "静", "丽", "强", "磊", "军", "洋"]
        self.english_first_names = [
            "James", "Mary", "John", "Patricia", "Robert", "Jennifer",
            "Michael", "Linda", "William", "Elizabeth"
        ]
        self.english_last_names = [
            "Smith", "Johnson", "Williams", "Brown", "Jones", "Garcia",
            "Miller", "Davis", "Rodriguez", "Martinez"
        ]
        self.company_names = ["SF", "YG", "JD"]
        self.tel = [
            "183", "188", "177", "135", "136", "137", "138", "139", "150",
            "151", "152", "153", "155", "156", "157", "158", "159", "130",
            "131", "132", "133", "134", "185", "186", "187", "180", "181",
            "182", "189"
        ]
        self.contianer = {"A": 0, "B": 0, "C": 0, "D": 0, "E": 0}

        # 生成数据
        self.special_user = ("wwr", "wwr123", "wwrpassword", 1, 0, 0,
                             "18312345678")
        self.user = self.generate_user(self.user_count)
        self.ruku_package = self.generate_ruku_package(self.ruku_package_count,
                                                       self.user)
        self.daishou_package = self.generate_daishou_package(
            self.daishou_package_count, self.user)
        self.out_package = self.generate_out_package(self.out_package_count,
                                                     self.user)
        self.worker = self.generate_worker(self.worker_count)

    def generate_chinese_name(self):
        surname = random.choice(self.chinese_surnames)
        name = random.choice(self.chinese_names)
        return surname + name

    def generate_english_name(self):
        first_name = random.choice(self.english_first_names)
        last_name = random.choice(self.english_last_names)
        return first_name + last_name

    def generate_names(self, count):
        names = []
        for _ in range(count):
            if random.choice([True, False]):
                names.append(self.generate_chinese_name())
            else:
                names.append(self.generate_english_name())
        return names

    def generate_user(self, count):
        users = []
        users.append(self.special_user)
        for i in range(1, count):
            name = self.generate_chinese_name()
            account = name + str(random.randint(100, 999))
            password = "password" + str(random.randint(100000, 999999))
            user_id = i + 1
            num_ji = random.randint(0, 100)
            num_qu = random.randint(0, 100)
            tel_num = random.choice(self.tel) + str(
                random.randint(10000000, 99999999))
            users.append(
                (name, account, password, user_id, num_ji, num_qu, tel_num))
        return users

    def generate_ruku_package(self, count, user):
        ruku_packages = []
        for i in range(1, count):
            weight = round(random.uniform(0.1, 50.0), 2)
            if i <= 50:
                volume = round(random.uniform(0.1, 80.0), 2)
            else:
                volume = round(random.uniform(80.0, 120.0), 2)
            name = "name"
            if i <= 10:
                shoujianren_tel = self.special_user[6]
            else:
                shoujianren_tel = random.choice(user)[6]
                while shoujianren_tel == self.special_user[6]:
                    shoujianren_tel = random.choice(user)[6]

            while True:
                in_address = random.randint(1, 5)
                out_address = random.randint(1, 5)
                if in_address != out_address:
                    break

            if random.choice([True, False]):
                state = 0
            else:
                state = random.choice(user)[3]

            if 0 < volume <= 20:
                contianer_code = "A"
            elif 20 < volume <= 40:
                contianer_code = "B"
            elif 40 < volume <= 60:
                contianer_code = "C"
            elif 60 < volume <= 80:
                contianer_code = "D"
            else:
                contianer_code = "E"
            if contianer_code == "E": state = 0
            self.contianer[contianer_code] += 1
            code = contianer_code + str(self.contianer[contianer_code])
            company = random.choice(self.company_names)
            id = company + "0" + str(in_address) + str(out_address) + str(
                random.randint(100, 999))
            time = 1740970266 + random.randint(-10000, 10000)
            ruku_packages.append(
                (weight, volume, name, shoujianren_tel, code, out_address,
                 in_address, state, id, company, time, i-1))
        return ruku_packages

    def generate_daishou_package(self, count, user):
        daishou_packages = []
        for i in range(count):
            weight = round(random.uniform(0.1, 50.0), 2)
            volume = round(random.uniform(0.1, 100.0), 2)
            name = "name"
            while True:
                shoujianren_tel = random.choice(user)[6]
                jijianren_tel = random.choice(user)[6]
                if shoujianren_tel != jijianren_tel:
                    break

            while True:
                in_address = random.randint(1, 5)
                out_address = random.randint(1, 5)
                if in_address != out_address:
                    break

            state = 0
            code = "NULL"
            company = random.choice(self.company_names)
            id = company + "0" + str(in_address) + str(out_address) + str(
                random.randint(100, 999))
            time = 1740970266 + random.randint(-10000, 10000)
            daishou_packages.append(
                (weight, volume, name, shoujianren_tel, code, out_address,
                 in_address, state, id, company, time))
        return daishou_packages

    def generate_out_package(self, count, user):
        out_packages = []
        for i in range(count):
            weight = round(random.uniform(0.1, 50.0), 2)
            volume = round(random.uniform(0.1, 100.0), 2)
            name = "name"
            while True:
                shoujianren_tel = random.choice(user)[6]
                jijianren_tel = random.choice(user)[6]
                if shoujianren_tel != jijianren_tel:
                    break

            while True:
                in_address = random.randint(1, 5)
                out_address = random.randint(1, 5)
                if in_address != out_address:
                    break

            state = 1
            while True:
                out_name = random.choice(user)[0]
                in_name = random.choice(user)[0]
                if out_name != in_name:
                    break
            cost = random.randint(1, 100)
            hurry_ornot = random.choice([0, 3])
            company = random.choice(self.company_names)
            id = company + random.choice(
                ["0", "1"]) + str(in_address) + str(out_address) + str(
                    random.randint(100, 999))
            out_packages.append(
                (weight, volume, name, shoujianren_tel, jijianren_tel,
                 out_address, in_address, out_name, in_name, cost, state, id,
                 company, hurry_ornot))
        return out_packages

    def generate_worker(self, count):
        workers = []
        for i in range(count):
            name = self.generate_chinese_name()
            account = f"{i+1:03}"
            password = "password" + str(random.randint(100000, 999999))
            workers.append((name, account, password))
        return workers

    def write_user(self, users, file_path):
        with open(file_path, "w", encoding="utf-8") as file:
            for user in users:
                file.write(" ".join(map(str, user)) + "\n")

    def write_ruku_package(self, ruku_packages, file_path):
        with open(file_path, "w", encoding="utf-8") as file:
            for ruku_package in ruku_packages:
                file.write(" ".join(map(str, ruku_package)) + "\n")

    def write_daishou_package(self, daishou_packages, file_path):
        with open(file_path, "w", encoding="utf-8") as file:
            for daishou_package in daishou_packages:
                file.write(" ".join(map(str, daishou_package)) + "\n")

    def write_out_package(self, out_packages, file_path):
        with open(file_path, "w", encoding="utf-8") as file:
            for out_package in out_packages:
                file.write(" ".join(map(str, out_package)) + "\n")

    def write_worker(self, workers, file_path):
        with open(file_path, "w", encoding="utf-8") as file:
            for worker in workers:
                file.write(" ".join(map(str, worker)) + "\n")


if __name__ == "__main__":
    os.chdir(os.path.dirname(os.path.abspath(sys.argv[0])))
    generator = Generate(user_count, ruku_package_count, daishou_package_count,
                         out_package_count, worker_count)
    # generator.write_user(generator.user, os.path.join("data", user_file))
    generator.write_ruku_package(generator.ruku_package,
                                 ruku_package_file)
    # generator.write_out_package(generator.out_package,
    #                             os.path.join("data", out_package_file))
    # generator.write_daishou_package(generator.daishou_package,
    #                                 os.path.join("data", daishou_package_file))
    # generator.write_worker(generator.worker, os.path.join("data", worker_file))
