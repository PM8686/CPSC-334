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
- created bash script in rasberrypi/bash_ip


- created systemd unit file called /etc/systemd/system/IPupload.service
    - https://docs.redhat.com/en/documentation/red_hat_enterprise_linux/8/html-single/using_systemd_unit_files_to_customize_and_optimize_your_system/index#proc_creating-custom-unit-files_assembly_working-with-systemd-unit-files
    - add after network connected functionality (https://unix.stackexchange.com/questions/126009/cause-a-script-to-execute-after-networking-has-started)
    - had to enable permissions/ownership of bash_ip file through "chmod 744 bash_ip"

