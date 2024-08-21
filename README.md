# AW-MAC-Simulation
This is a simple protocol simulation code for Media Access Control (MAC) layer. I write it just for fun and hope that I can use some oop mind in this tiny project.

Well, I should introduce my project. It's a simulation infrastration for MAC(Media Access Control) communication protocol. Because I learn about communication simulation and I build this simple infra for fun.

In this project I set sevral mac nodes attaching with their net layer. The net layer can receive data from application layer and give it to mac layer, which is the "mac nodes" I just said. Then mac layer run its protocol and finally send this message to its bufferToPhysical. This means other nodes can receive this message! I also set a messageQueue to manage these messages which are sent to bufferToPhysical by mac nodes. The messageQueue will do run() and storage and forward these message to mac nodes' bufferFromPhysical. Once a mac node's bufferFromPhysical is set a message, this means one mac node has receive messages from other mac node.

OK I know it's simple and my discription is full of chaos. I'll back here and modify this documentation. I'll try my half best ^_^. Because I have little time.
