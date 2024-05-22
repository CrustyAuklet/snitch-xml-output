import argparse
import subprocess
import pathlib
from approvaltests import verify, Options

# pylint: disable = no-name-in-module
from approvaltests.namer.cli_namer import CliNamer
from approvaltests.scrubbers.scrubbers import create_regex_scrubber
from approvaltests.reporters.python_native_reporter import PythonNativeReporter


def parse_arguments() -> (str, pathlib.Path, pathlib.Path):
    parser = argparse.ArgumentParser(description="Compare Snitch XML output to Catch2")
    parser.add_argument("test_name", type=str, help="test name")
    parser.add_argument("build_dir", type=pathlib.Path, help="path to test binaries")
    parser.add_argument("data_dir", type=pathlib.Path, help="path to output data")
    args = parser.parse_args()
    return args.test_name, args.build_dir, args.data_dir


def test_xml_output():
    test_name, build_dir, data_path = parse_arguments()
    snitch_test = build_dir / f'{test_name}_snitch.exe'
    catch2_test = build_dir / f'{test_name}_catch2.exe'

    print(f'Comparing output for {test_name}:")')
    print(f'  Snitch: {snitch_test}')
    print(f'  Catch2: {catch2_test}')
    print(f'  Data: {data_path}')

    data_path.mkdir(parents=True, exist_ok=True)
    test_path_prefix = data_path / test_name

    time_scrubber = create_regex_scrubber(r'durationInSeconds=\"[\d\.e\-\+]+\"',
                                          "durationInSeconds=<TIME>")
    name_scrubber = create_regex_scrubber(r'Catch2TestRun name="[\w\d\._-]+"',
                                          f'Catch2TestRun name="{test_name}"')
    rng_scrubber = create_regex_scrubber(r'rng-seed="\d+"',
                                         f'rng-seed="<SEED>"')
    version_scrubber = create_regex_scrubber(r'catch2-version=".+>',
                                             f'catch2-version="<VERSION>"')

    # output catch2 to the data directory
    catch2_output = subprocess.run([catch2_test, "-r", "xml", "-d", "true"], stdout=subprocess.PIPE)
    catch2_output = catch2_output.stdout.decode()
    catch2_output = time_scrubber(catch2_output)
    catch2_output = name_scrubber(catch2_output)
    catch2_output = rng_scrubber(catch2_output)
    catch2_output = version_scrubber(catch2_output)

    with open(f'{test_path_prefix}.approved.txt', 'w+') as f:
        f.write(catch2_output)

    snitch_result = subprocess.run([snitch_test, "-r", "xml"], stdout=subprocess.PIPE)

    verify(snitch_result.stdout.decode(),
           # reporter=PythonNativeReporter(),
           namer=CliNamer(test_id=test_path_prefix),
           options=Options().add_scrubber(time_scrubber)
                            .add_scrubber(name_scrubber)
                            .add_scrubber(rng_scrubber)
                            .add_scrubber(version_scrubber))
    print(f"Test Passed: {snitch_test}")


if __name__ == "__main__":
    test_xml_output()
