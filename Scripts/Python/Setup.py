from SetupVulkan import VulkanConfiguration as VulkanRequirements
import os
import subprocess
import platform

os.chdir('./../')  # Change from Scripts directory to root

VulkanRequirements.Validate()

print("\nUpdating submodules...")
subprocess.call(["git", "submodule", "update", "--init", "--recursive"])


def getPremakeSetupBat(platform):
    print(f"Getting Premake script for system: {platform}")

    if platform == "Windows":
        return "Setup-Windows.bat"
    elif platform == "Linux":
        return "Setup-Linux.bat"
    elif platform == "Darwin":
        return "Setup-macOS.zsh"
    else:
        raise Exception(f"Unknown Platform: {platform}")


scriptPath = os.path.abspath(
    f"./Scripts/Premake/{getPremakeSetupBat(platform.system())}")
print(f"\nRunning Premake ({scriptPath}) ...")
subprocess.call(scriptPath)

print("\nSetup completed!")
