import pathlib
import os
import cocotb_tools.runner

runner = cocotb_tools.runner.get_runner("verilator")
rtl_dir = pathlib.Path(os.getcwd())
sources = [ rtl_dir / "rtl" / "summator.v", rtl_dir / "rtl" / "main.v" ]
runner.build(sources=sources,hdl_toplevel="main")
runner.test(hdl_toplevel="main",test_module="test_main")
