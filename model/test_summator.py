import cocotb
import cocotb.triggers
import cocotb.types
import random
import utils

@cocotb.test()
async def test(dut):
    for _ in range(1000):
        x1 = random.randint(1,15)
        x2 = random.randint(1,15)
        expected = (x1 + x2) % 16
        expected_bin = cocotb.types.LogicArray(utils.int_to_bin(expected,4))
        dut.a.value = cocotb.types.LogicArray(utils.int_to_bin(x1,4))
        dut.b.value = cocotb.types.LogicArray(utils.int_to_bin(x2,4))
        await cocotb.triggers.Timer(10,'ns')
        if dut.y.value != expected_bin:
            print("Summator Test Failed: {} + {} = {}. expecting {}".format(x1,x2,dut.y.value,expected_bin))
        assert dut.y.value == cocotb.types.LogicArray(utils.int_to_bin(expected,4))
