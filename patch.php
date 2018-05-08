<?php

class patch {

private $input:
private $output;
private $command;
private $atr;

	public function designated_ouput($input){
		$output = ''; //preventing output fron being placed in an untrusted location
		return $output; //Nullifying it
	}

	public function removing_tags($input){
		$output = strip_tags($input,"put allowed","tags here"); //removes every tag except allowed ones useful for clearing out the script tags
		return $output;
	}

	public function removing_specialchars($input){
		$output = htmlspecialchars($input, ENT_QUOTES); //replaces ", ', <, >, & in the string
		return $output;
	}
	
	public function sanitizing_commands($command){
		$command1 = escapeshellcmd ( $command ); //prevents the attacker from implementing another command in the initial command
		return $command1;
	}

	public function sanitizing_commands($input){
		if( !ctype_alnum ( $input )) { //check for alpha-numerics
			echo "Not a valid input";
			$output = htmlspecialchars($input, ENT_QUOTES);
			return $output;
		}
		
	}

	public function sanitizing_attributes_sql($atr){
		//copy the connection as $mysqli = new mysqli("host", "user", "password", "dbname");
		$atr1 = $mysqli->real_escape_string($atr); //escapes special chars
		return $atr1;
	}
	//use exit() to stop the script wherever required
}
?>
