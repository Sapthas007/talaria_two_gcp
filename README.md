# Google Cloud IoT Device SDK Embedded C on InnoPhase Talaria TWO Platform

## Table of Contents

- [Introduction](#introduction)
- [Getting Started with the SDK](#get-started)
- [Overview of Sample Application](#sample-app)

## Introduction

<a name="introduction"></a>

[GCP IoT Device SDK Embedded-C Release](git clone https://github.com/GoogleCloudPlatform/iot-device-sdk-embedded-c.git --recurse-submodules) is ported on Talaria TWO Software Development Kit as per the porting guidelines.

Using this, the users can now start developing exciting [ultra-low power IoT solutions on Talaria TWO family of devices](https://innophaseinc.com/talaria-technology-details/), utilizing the power of the Google cloud IoT Core platform and its services.

More information on google-cloud-iot-device-sdk-embedded-C can be found here:
[git clone https://github.com/GoogleCloudPlatform/iot-device-sdk-embedded-c.git --recurse-submodules)

API Documentation and other details specific to GCP IoT Device SDK Embedded C release tag V3.1.5 can be found here:
[https://googlecloudplatform.github.io/iot-device-sdk-embedded-c/api/html/]

## Getting Started with the SDK

<a name="get-started"></a>

### Cloning the 'iot_gcp' repository
- Create a new folder in any place and clone the 'iot_gcp' repo using below command
``` bash
git clone --recursive https://github.com/Sapthas007/iot_gcp.git
```
> This repo uses [Git Submodules](https://git-scm.com/book/en/v2/Git-Tools-Submodules) for it's dependencies. The option '--recursive' is required to clone git submodule repos needed by 'iot_gcp' repo.


### Compiling the GCP IoT SDK and the Sample App
- After the clone is complete as described in previous step, run the python script using the following command `python3 gcp_auto.py`.
- It will applty the patch and generate the elf files in the output directory. 


### Programming the Dev-Kits
**Follow Application Note provided with the Talaria TWO SDK at the path `<sdk_path>/apps/iot_gcp` for further details on programming certs, keys and executable binaries on Talaria TWO based EVB-A boards and running the Sample Applications / verifying the expected outputs using the Debug Console and GCP Web Console.**

### Folder Structure of the 'iot_gcp' repository
The repo `iot_gcp` has the below directories/files:

- directory `iot-device-sdk-embedded-c-master`- Contains the Google cloud IoT Device SDK Embedded-C Release.
- directory `patches` - Contains patch file `iot_gcp.patch` for goole IoT Device for Talaria TWO compatibility.
- directory `files`- Its ‘Platform Adaptation Layer’ and contains Talaria TWO Platform specific porting needed to adapt to Google IoT SDK.
- directory `data`: Provides the sample rootFS folder structure to be used while programming the GCP certs and keys to EVB-A for iot_gcp Sample Application.
- file `Makefile`- Takes care of making the Sample App executable binaries and GCP iot sdk libraries using GCP IoT SDK source files, Sample App source files.

## Overview of Sample Applications

<a name="iot_core_mqtt_client"></a>

Sample Applications ported to the Talaria TWO Platform can be found in the path `/examples/iot_core_mqtt_client`.
A brief overview of these apps is provided in this section.

Follow Application Note provided with the Talaria TWO SDK at the path `<sdk_path>/apps/iot_gcp` for further details on programming certs, keys and executable binaries on Talaria TWO based EVB-A boards and running the Sample Applications / verifying the expected outputs using the Debug Console and GCP Web Console.
 
### iot_core_mqtt_client
This example takes the parameters from the  T2 boot arguments and establishes a connection to the Google CLoud IoT Platform.
Then it subscribes and publishes to the topics provided as bootArgs subscribe_topic and publish_topic.

If all the certs/keys are correct, in the T2 Console you should see alternate QoS0 and QoS1 messages being published to 'publish_topic' by the application in a loop.

GCP IoT Console->Test page can be used to subscribe to '/devices/atest-dev/commands/#' (or T2's 'publish_topic' provided as the bootArg to App) to observe the messages published by the App.

GCP IoT Console->Test page can be used to publish the message to '/devices/atest-dev/state'(or T2's 'subscribe_topic' provided as the bootArg to App), and T2 App will receive the
messages and they will be seen on T2 Console.

JSON formatted text as shown below should be used for publishing to T2.
```
 {
 "Hello From Innophase T2"
 }
```

The application takes in the ssid, passphrase, iotc_project_id, iotc_publish_topic, iotc_publish_message, and iotc_device_path as must provide bootArgs.

Certs and keys are stored in rootFS and read from app specific paths defined in the sample code.



