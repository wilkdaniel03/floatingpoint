import pathlib
import os
import cocotb_tools.runner

runner = cocotb_tools.runner.get_runner("verilator")
rtl_dir = pathlib.Path(os.getcwd())
sources = [ rtl_dir / "rtl" / "summator.v" ]
runner.build(sources=sources,hdl_toplevel="summator")
runner.test(hdl_toplevel="summator",test_module="test_summator")
