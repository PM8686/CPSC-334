- created github account
- created repo for 334
- created folder in repo called rasberrypi, added doc ip.md
- enabled SSH on rasberry pi configuration
- rasberrypi password is cpsc334!
- SSH-ed into rasberrypi
ssh student334@10.67.73.14
password: cpsc334!
- generated SSH key


- first write id to file and then upload it to github, make sure it is fired off by system d on .bashrc after the network is connected and user is logged in
- create a system d service that runs the script at the right time

stuff from the teacher:
systemd considerations
- after networking has IP
- run as who?
    - 