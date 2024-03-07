from SetupVulkan import VulkanConfiguration as VulkanRequirements
import os
import subprocess
import platform

os.chdir('./../')  # Change from Scripts directory to root

VulkanRequirements.Validate()

print("\nUpdating submodules...")
subprocess.call(["git", "submodule", "update", "--init", "--recursive"])


def getPremakeSetupBat(system):
    print(f"Getting Premake script for system: {system}")

    if system == "Windows":
        return "Setup-Windows.bat"
    elif system == "Linux":
        return "Setup-Linux.bat"
    elif system == "Darwin":
        return "Setup-macOS.sh"
    else:
        raise Exception("Unknown Platform: {platform}")


scriptPath = os.path.abspath(
    f"./Scripts/Premake/{getPremakeSetupBat(platform.system())}")
print(f"\nRunning Premake ({scriptPath}) ...")
subprocess.call(scriptPath)

print("\nSetup completed!")
