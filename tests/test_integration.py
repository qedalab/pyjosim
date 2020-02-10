from pyjosim import CliOptions, Input


def josim_cli(args):
    cli = CliOptions(args)
    josim_input = Input(cli.analysis_type, cli.input_type, cli.verbose)
    josim_input.parse_file(cli.cir_file_name)
    parameters = josim_input.parameters

    if len(parameters) > 0:
        parameters.parse()

    josim_input.parse_models()


def test_jtl_basic():
    josim_cli(["./tests/ex_jtl_basic.cir"])
