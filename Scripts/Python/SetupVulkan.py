import os
import sys
import platform
import subprocess
from pathlib import Path

from io import BytesIO
from urllib.request import urlopen

class VulkanConfiguration:
    requiredVulkanVersion = "1.3."
    installVulkanVersion = "1.3.275.0"
    vulkanDirectory = "./Core/Vendor/VulkanSDK"

    @classmethod
    def Validate(cls):
        if (not cls.CheckVulkanSDK()):
            print("Vulkan SDK not installed correctly.")
            return

        if (not cls.CheckVulkanSDKDebugLibs()):
            print("\nNo Vulkan SDK debug libs found. Install Vulkan SDK with debug libs.")
            print("Debug configuration disabled.")

    @classmethod
    def CheckVulkanSDK(cls):
        vulkanSDK = os.environ.get("VULKAN_SDK")
        if (vulkanSDK is None):
            print("\nYou don't have the Vulkan SDK installed! Please install from https://vulkan.lunarg.com/sdk/home")
            return False
        else:
            print(f"\nLocated Vulkan SDK at {vulkanSDK}")

        if (cls.requiredVulkanVersion not in vulkanSDK):
            print(f"You don't have the correct Vulkan SDK version! Please install from https://vulkan.lunarg.com/sdk/home (Engine requires {cls.requiredVulkanVersion})")
            return False

        print(f"Correct Vulkan SDK located at {vulkanSDK}")
        return True

    @classmethod
    def CheckVulkanSDKDebugLibs(cls):
        vulkanSDK = os.environ.get("VULKAN_SDK")
        shadercdLib = Path(f"{vulkanSDK}/{cls.GetVulkanLibDirForPlatform(platform.system())}")

        print(f"Checking for SDK Debug Libs at {shadercdLib}")

        return shadercdLib.exists()

    @classmethod
    def GetVulkanLibDirForPlatform(cls, platform):
        if platform == "Windows":
            return "Lib/shaderc_sharedd.lib"
        elif platform == "Linux":
            return "lib/shaderc_sharedd.lib"
        elif platform == "Darwin":
            return "Frameworks/vulkan.framework"
        else:
            raise Exception(f"Unknown Platform: {platform}")

if __name__ == "__main__":
    VulkanConfiguration.Validate()
