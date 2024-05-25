#SCRIPT is to re run the application when it dies
#Process name
processName="arete_CHARGING_SERVER"
#Command to start new process
commandToRun="./"$processName
continueLoop=1
AppInstanceCount=0
#Infinite loop for app restart
while [ continueLoop==1 ];
do
	if ps -ef | grep -v grep | grep "$processName"
	then
		echo "Process $processName is Running !!"
	else
		echo "Process $processName not there. So creating new instance !!"
		AppInstanceCount=$((AppInstanceCount+1))
		$commandToRun
	fi
	sleep 1
done
	echo "No of Instances created for the process $processName is: $AppInstanceCount"
exit 0
