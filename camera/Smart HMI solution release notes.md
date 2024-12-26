# Smart HMI solution release notes

**V1.1.2**

**Improvements**

1. Upgrade oasis library to v2.2.0 which integrated the fix for the multiple registration issue while the face has partial brightness.
2. Upgrade the VoiceSeeker to v0.6.0.
3. Upgrade the VIT to V4.7.7 RFP release.
4. Upgrade the DSMT coffee machine and elevator Chinese voice model to version 6.
5. Move flexspi clock to pll2 pfd2 to improve the system performance.
6. Add the LED blinking during the resource move of the MSD update.
7. Modify memory map to 7MB of code, 13MB of resources
8. Add Framework source code
9. Add minimal UI interface in bootloader for easier MSD updates.

**V1.1.1**a

**HotFix**

1. Fix database backward compatibility when doing update without a prior mass erase.

**V1.1.0**

**What’s new**
1. Added elevator demo application
2. New camera support MIPI - GC2145
3. Increase flash size to 64MB in order to support 2 applications
4. NXP VIT library for voice recognition capabilities (en/de/cn)
5. Multilingual wake word and prompt responds (only for Cybron, DSMT)
6. Barge-in feature
7. Audio Dump feature for offline audio validation
8. Ivaldi support for mass production flashing
9. On Screen face information for easier debugging
10. Coffee machine
   * Enable WiFi
   * Over the air update via Amazon cloud
11. Image validation in bootloader (disable by default)

**Bug Fix**
1. Memory leak in framework
2. LCD flicker when wake up
3. Database lacks backward compatibility after update. Affects both coffee machine demo and elevator demo.


**Improvements**

1. Improve UI/touch responsiveness
2. Voice recognition accuracy and precision
3. Face recognition accuracy
4. Improve bootup time (from bootloader to first video frame)
5. Change audio prompts for better quality

**List of known issues:**
|Ticket number| Description|
| ----------- | ------------------------------------------------------------ |
| SMA-628     |  Board Blue LED sometimes remains on, other times just blinks|
| SMA-584     |  Elevator Alarm remains on |
| SMA-539     | Coffee machine/ Elevator - false wake up most seen with Chinese |
| SMA-503     | Board can register same user multiple times depending on the lighting condition |
| SMA-462     | Coffee machine board understands STOP as START |

**V1.0.0**

**What’s new**
1. First official version of Smart HMI Solution project.
2. Contains `coffee machine` application with lvgl resources
3. Voice recognition using Cybron/DSMT (en/de/fr/cn)
4. Single RGB camera face recognition