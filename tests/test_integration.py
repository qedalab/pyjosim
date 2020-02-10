from pyjosim import CliOptions, Input

def test_jtl_basic():
    cli = CliOptions(["./tests/ex_jtl_basic.cir"])
    josim_input = Input(cli.analysis_type, cli.input_type, cli.verbose)
    josim_input.parse_file(cli.cir_file_name)
