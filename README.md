# rza2m_face_detection_demo

Face Detection Demo with [RZ/A2M](https://www.renesas.com/eu/en/products/microcontrollers-microprocessors/rz-cortex-a-mpus/rza2m-high-speed-embedded-ai-based-image-processing-microprocessors-dynamically-reconfigurable-processor)  

<p align="center"> 
	<img src="https://github.com/renesas-rz/rza2m_face_detection_demo/blob/master/face_detection_demo.jpg" alt="">
	<img src="https://github.com/renesas-rz/rza2m_face_detection_demo/blob/master/face_detection_concept.jpg" alt="">
</p>

In the demo, we connect the Sony IMX219 CMOS sensor through MIPI interface, input a 1280x720 resolution image, and use DRP in RZ/A2M to perform Simple ISP processing and image scaling processing on the input image, and then run a light and efficient mask face detection model. It can achieve detect speed of 30FPS in the face detection mode, and a detection speed of 20FPS in the mode of distinguishing whether to wear a mask. 

Finally, the result is shown on a display (HDMI monitor).


### Supported platforms:

1. [RZ/A2M Evaluation Board Kit](https://www.renesas.com/eu/en/products/microcontrollers-microprocessors/rz-cortex-a-mpus/rza2m-evaluation-kit-rza2m-evaluation-kit)  
   [e²studio](https://www.renesas.com/eu/en/software-tool/e-studio) project name: “rza2m_face_detection_freertos_gcc_evk”  
   ([e²studio User’s Manual: Getting Started Guide / RZ Family](https://www.renesas.com/eu/en/document/mat/e-studio-integrated-development-environment-users-manual-getting-started-renesas-mcu-rz-family?language=en&r=488826))

2. [Gadget Renesas board “GR-MANGO”](https://www.renesas.com/eu/en/products/gadget-renesas/boards/gr-mango)  
   [e²studio](https://www.renesas.com/eu/en/software-tool/e-studio) project name: “rza2m_face_detection_freertos_gcc_grmango”  
   ([e²studio for GR-MANGO](https://github.com/renesas-rz/rza2m_face_detection_demo/blob/master/rza2m_face_detection_freertos_gcc_grmango/doc/EPSD-IMB-20-0107-02_RZA2M_SoftwarePackage_for_GR-MANGO_Development_Environment_Construction.pdf); [GR-MANGO 'hands-on'](https://github.com/renesas-rz/rza2m_face_detection_demo/blob/master/rza2m_face_detection_freertos_gcc_grmango/doc/EPSD-IMB-20-0106-01_RZA2M_SoftwarePackage_for_GR-MANGO_Hands_on_Training.pdf))


### Key features:

**MIPI 1280x720 camera input.**

**Only use RZ/A2M internal 4MB memory.**

**Support face detection & mask detection.**

**Face Detection performance: 30fps**

**Face + Mask Detection performance: 15fps.**

([DRP](https://www.renesas.com/eu/en/application/technologies/drp)).



### More:

Please check the 
[Application Note](https://github.com/renesas-rz/rza2m_face_detection_demo/blob/master/rza2m_face_detection_freertos_gcc_evk/doc/RZA2M_FaceDetection_demo_ApplicationNote_20210830.pdf)
for more details.

Please contact your local Renesas Sales representative in case you like to get more information about [RZ/A2M](https://www.renesas.com/eu/en/products/microcontrollers-microprocessors/rz-cortex-a-mpus/rza2m-high-speed-embedded-ai-based-image-processing-microprocessors-dynamically-reconfigurable-processor), [DRP](https://www.renesas.com/eu/en/application/technologies/drp)

## Q&A
Please contact us below if you have any questions.　
&nbsp;[Q&A Forum](https://renesasrulz.com/rz/rz-a2m-drp/f/rz-a2m-and-drp-forum)  

