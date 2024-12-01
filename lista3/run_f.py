import os
import subprocess
import re

wd = os.path.abspath(os.path.dirname(__file__))
os.chdir(wd)

instances_directory = "exercise-c/castle/"
domain_filename = 'domain.pddl'

instances_filenames = os.listdir(instances_directory)
instances_filenames.remove(domain_filename)

patterns = {
    "Plan length": r"Plan length:\s*(\d+)",
    "Plan cost": r"Plan cost:\s*(\d+)",
    "Search time": r"Search time:\s*([\d.]+)s",
    "Expanded states": r"Expanded\s+(\d+)\s+state\(s\)\.",
}

heuristics = ['planopt_ff()', 'ff()']

def main():
    build()
    for instance_filename in instances_filenames:
        for heuristic in heuristics:
            command = [
                "python3",
                "./exercise-c/fast-downward/fast-downward.py",
                os.path.join(instances_directory, domain_filename),
                os.path.join(instances_directory, instance_filename),
                "--search",
                f"eager_greedy([{heuristic}])"
            ]
                
            try:
                print(f"Running: {instance_filename} - { heuristic}")
                result = subprocess.run(command, text=True, capture_output=True, timeout=60)
                output = result.stdout

                if result.returncode != 0:
                    if result.returncode == 12:
                        print("No solution found!")
                    else:
                        print(f"Error running command (returned {result.returncode})")
                        
                        print(f"Stderr: {result.stderr}")
                        print(f"Command: {' '.join(command)}")
                        print()
                        continue  


                
                parsed_data = {}
                for key, pattern in patterns.items():
                    match = re.search(pattern, output)
                    if match:
                        parsed_data[key] = match.group(1)

                for key, _ in parsed_data.items():
                    print(f"{key}", end=', ')
                print()
                for _, value in parsed_data.items():
                    print(f"{value}", end=', ')
                print()
                print()

            except subprocess.TimeoutExpired as e:
                print("Timeout!")
                print()
                continue  



def build():
    build_command = [
            "python3",
            "./exercise-c/fast-downward/build.py",
            "release",
        ]
    try:
        result = subprocess.run(build_command, text=True, capture_output=False, check=True)

        
    except subprocess.CalledProcessError as e:
        print("Error building fast-downward")
        print()
        exit(1)


main()