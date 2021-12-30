# create service
sc create MyService binPath="FULLPATH TO SampleService.exe" DisplayName="MY SERVICE!!!"

# set service to autostart
sc config MyService start=auto

# start/stop service with:
net stop MyService
net start MyService

# delete service with:
sc delete MyService

NOTE: these commands require administrator privileges