public class RoboMachine{
	final static int WAITING_COMMAND = 0;
	final static int OVERRUN_COMMAND = 1;
	final static int RECEIVING_COMMAND = 2;
	final static int COMMAND_IS_EXECUTED = 3;
	int state = WAITING_COMMAND;
	public void sendCommand( ){
		switch ( state ){
			case WAITING_COMMAND:
				state = OVERRUN_COMMAND;
				break;
			case OVERRUN_COMMAND:
				break;
			case RECEIVING_COMMAND:
				break;
			case COMMAND_IS_EXECUTED:
				break;
		}
	}
}