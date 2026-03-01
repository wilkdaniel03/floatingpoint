import cocotb
import cocotb.triggers
import cocotb.types
import random

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

@cocotb.test()
async def test(dut):
    dut.x1.value = cocotb.types.LogicArray(int_to_bin(random.randint(1,15),4))
    dut.x2.value = cocotb.types.LogicArray(int_to_bin(random.randint(1,15),4))
    await cocotb.triggers.Timer(1,'ns')
    count = 0
    for _ in range(1000):
        x1 = random.randint(1,15)
        x2 = random.randint(1,15)
        expected = (x1 + x2) % 15
        dut.x1.value = cocotb.types.LogicArray(int_to_bin(x1,4))
        dut.x2.value = cocotb.types.LogicArray(int_to_bin(x2,4))
        await cocotb.triggers.Timer(10,'ns')
        if cocotb.types.LogicArray(int_to_bin(expected,4)) == dut.y.value:
            count += 1
        else:
            print("Failed: {} + {} = {}".format(x1,x2,dut.y.value))
    print("Summator test result: {}".format(count))
    # dut.x.value = cocotb.types.LogicArray("1101")
    # await cocotb.triggers.Timer(1,'ns')
    # print("RUNNING... - {} => {}".format(dut.x.value,dut.y.value))
