from pyjosim import CliOptions, Input, Matrix, Simulation, Output


def josim_cli(args):
    cli = CliOptions(args)
    josim_input = Input(cli.analysis_type, cli.input_type, cli.verbose)
    josim_input.parse_file(cli.cir_file_name)
    parameters = josim_input.parameters

    if len(parameters) > 0:
        parameters.parse()

    josim_input.parse_models()

    netlist = josim_input.netlist
    netlist.expand_subcircuits()
    netlist.expand_maindesign()

    josim_input.identify_simulation()

    matrix = Matrix(josim_input)
    simulation = Simulation(josim_input, matrix)
    output = Output(josim_input, matrix, simulation)


def test_jtl_basic():
    josim_cli(["./tests/ex_jtl_basic.cir"])
