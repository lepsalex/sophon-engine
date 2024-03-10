VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}

IncludeDir["stb"] = "%{wks.location}/Core/Vendor/stb"
IncludeDir["SPDLOG"] = "%{wks.location}/Core/Vendor/spdlog/include"
IncludeDir["GLFW"] = "%{wks.location}/Core/Vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/Core/Vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/Core/Vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/Core/Vendor/glm"
IncludeDir["entt"] = "%{wks.location}/Core/Vendor/entt/include"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"
IncludeDir["VulkanSDKmacOS"] = "%{VULKAN_SDK}/include"
IncludeDir["metalCPP"] = "%{wks.location}/Core/Vendor/metal-cpp"


LibraryDir = {}

LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"

Library = {}

Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["VulkanUtils"] = "%{LibraryDir.VulkanSDK}/VkLayer_utils.lib"

Library["ShaderC_Debug"] = "%{LibraryDir.VulkanSDK}/shaderc_sharedd.lib"
Library["SPIRV_Cross_Debug"] = "%{LibraryDir.VulkanSDK}/spirv-cross-cored.lib"
Library["SPIRV_Cross_GLSL_Debug"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsld.lib"
Library["SPIRV_Tools_Debug"] = "%{LibraryDir.VulkanSDK}/SPIRV-Toolsd.lib"

Library["ShaderC_Release"] = "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"
Library["SPIRV_Cross_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-core.lib"
Library["SPIRV_Cross_GLSL_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsl.lib"


LibraryDirMacOS = {}

LibraryDirMacOS["VulkanSDK"] = "%{VULKAN_SDK}/lib"

LibraryMacOS = {}

LibraryMacOS["Vulkan"]                  = "%{LibraryDirMacOS.VulkanSDK}/libvulkan.1.3.275.dylib"
LibraryMacOS["VulkanUtilsApiDump"]      = "%{LibraryDirMacOS}/libVkLayer_api_dump.dylib"
LibraryMacOS["VulkanUtilsScreenshot"]   = "%{LibraryDirMacOS}/libVkLayer_screenshot.dylib"

LibraryMacOS["ShaderC"] = "%{LibraryDirMacOS.VulkanSDK}/libshaderc_shared.dylib"
LibraryMacOS["SPIRV_Cross"] = "%{LibraryDirMacOS.VulkanSDK}/libspirv-cross-c-shared.dylib"
LibraryMacOS["SPIRV_Cross_GLSL"] = "%{LibraryDirMacOS.VulkanSDK}/libSPIRV-Tools-shared.dylib"
