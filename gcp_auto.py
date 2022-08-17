import os, sys, time
import argparse
from distutils.dir_util import copy_tree
from shutil import copyfile, copytree, copy
import shutil
import os.path
import glob
import gitlab


if __name__ == "__main__":
    """Parses arguments and performs compilation of apps"""
 
    ROOT_PATH=os.getcwd()
    os.system("cp  " +ROOT_PATH +"/patches/iot_gcp.patch iot-device-sdk-embedded-c/")
    #os.system("mv  " +ROOT_PATH +"/files/t2 iot-device-sdk-embedded-c/src/bsp/platform")

    # clone GCP-sdk from GitHub
    #os.system("git clone https://github.com/GoogleCloudPlatform/iot-device-sdk-embedded-c.git")  
    time.sleep(2)

    os.chdir("iot-device-sdk-embedded-c/")   
    print(ROOT_PATH +"/iot-device-sdk-embedded-c")
    #remove the git init from tuya-sdk
    #os.system(" rm -rf .git") 

    os.chdir("../")
    os.system("cp  " +ROOT_PATH +"/patches/0001-iot_gcp_changes.patch iot-device-sdk-embedded-c/")

    os.chdir(ROOT_PATH +"/iot-device-sdk-embedded-c")
    # Apply patch file to gcp-sdk
    #cmd_path = "git apply iot_gcp.patch"
    cmd_path = "git am < iot_gcp.patch"
    os.system(cmd_path)

    os.chdir("../")
    # Rename iot-device-sdk-embedded-c to gcp-iot-link-sdk
    os.system("mv iot-device-sdk-embedded-c gcp-iot-link-sdk")  
    # Move gcp-iot-link-sdk to src folder
    os.chdir("gcp-iot-link-sdk/")  
    cmd_path = " mv * ../"
    os.system(cmd_path)
    os.chdir("../")
    time.sleep(1)
    #cmd = "make"
    #os.system(cmd)
    os.system("rm -rf gcp-iot-link-sdk")
    os.system("mkdir data")
    
     

    # Copy switch_demo example from gcp-iot-link-sdk/examples/ to src directory 
    #os.system("cp -R gcp-iot-link-sdk/examples/switch_demo_non_qrcode  .")


    # Generate elf using make command
    os.system("make")
    
    

