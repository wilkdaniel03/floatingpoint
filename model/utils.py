def int_to_bin(input: int, n: int) -> str:
    data = input
    res = ""
    while data != 0:
        if data % 2 == 1:
            res += '1'
        else:
            res += '0'
        data = data >> 1
    for _ in range(n - len(res)):
        res += '0'
    return res[::-1]
