window.onload = function() {
	window.socket = WebSocketConnect(); // Connect to the websocket
	
	// bool
	var user_login = false; // bool
	var update_available = false; // bool; Whether or not there's an update available
	var recovery_mode = false; // bool; Determine if the user is in recovery mode
	var show_menu = false; // bool; Whether or not the user menu is being shown
	
	// JSON
	window.user_json; // json array containing user settings
	window.page_json; // json array for populating the page
	
	// int
	var entered_pin; // int
	
	/*
		Buttons (UI elements)
	*/
	var pin_button = document.getElementById("pinbutton");
	var option_button = document.getElementById("optionbutton");
	var menu_button = document.getElementById("menubutton");
	var start_button = document.getElementById("startbutton");
	var stop_button = document.getElementById("stopbutton");
	var update_button = document.getElementById("updatebutton");
	
	/*
		Links
	*/
	var recovery_link = document.getElementById("recoverylink");
	
	/*
		Visual elements (pop-up's, menu's)
	*/
	var update_screen = document.getElementById("update-message");
	var login_screen = document.getElementById("login");
	var overlay = document.getElementById("black-overlay");
	var navbar = document.getElementById("navbar");
	var temp = document.getElementById("temperaturefield");
	var time = document.getElementById("timefield");
	var state = document.getElementById("statusfield");
	
	/*
		Input elements
	*/
	var pin_field = document.getElementById("pinfield");
	
	// Check if the user is logged in
	if(user_login == false) {
		navbar.style.display = "none";
		login_screen.style.display = "block";
	}
	
	recovery_link.onclick = function() {
		document.getElementById("recoveryprompt").style.display = "block";
		recovery_mode = true;
	};
	
	// Perform function when the pin button is pressed
	pin_button.onclick = function() {
		entered_pin = pin_field.value;
		
		if(recovery_mode == true) {
			var pin_code = 01189998819991197253; // Emergency services phone number
		} else {
			var pin_code = window.user_json.pin; // The pin code is simply the user pin
		}
		
		if(pin_code == entered_pin) {			
			user_login = true;
			check_update_status();
			
			// Set default value for time input fields
			document.getElementById("duration").value = "00:00";
			
			navbar.style.display = "block"; // Show the menu
			overlay.style.display = "none"; // Hide the black overlay
			document.body.style.overflow = "scroll"; // Show the scrollbar
			login_screen.style.display = "none"; // Hide the login screen
		} else {
			user_login = false;
		}
	};
	
	// Perform function when the menu button is pressed
	menu_button.onclick = function() {
		if(show_menu == false) {
			document.getElementById("user_menu").style.display = "block";
			document.getElementById(window.user_json.recovery).checked = true;
			show_menu = true;
		} else {
			document.getElementById("user_menu").style.display = "none";
			show_menu = false;
		}
	};
	
	option_button.onclick = function() {
		var new_pin = document.getElementById("newpinfield").value;
		
		// Check if the pin is at least 4 characters long and a number
		if((new_pin.length != 4 || isNaN(new_pin) == true) && new_pin) {
			alert("Pin moet bestaan uit 4 getallen");
		} else {
			if(document.getElementById("continue").checked == true) { // Check if the first radio button is checked
				save_settings(new_pin, "continue");
			} else { // If not, the only other option must be selected
				save_settings(new_pin, "cancel");
			}
			recovery_mode = false;
			document.getElementById("user_menu").style.display = "none";
			show_menu = false;
		}
	}
	
	// Perform function when start button is pressed
	start_button.onclick = function() {
		// Get the selected washingprogram
		var was_dropdown = document.getElementById("wasprogrammas");
		var was_selected = was_dropdown.options[was_dropdown.selectedIndex].label;
		
		// Get the selected temperature
		var temp_dropdown = document.getElementById("temperaturen");
		var temp_selected = temp_dropdown.options[temp_dropdown.selectedIndex].value;
		
		var delay_value = document.getElementById("duration").value; // Get the selected time until start of program
		var time = delay_value.split(":"); // Split the time by the : delimiter
		var delay = (parseInt(time[0]) * 60) + parseInt(time[1]); // Get the amount of minutes and convert them to integers, then add them up
		
		// Send a start command to the websocket, along with a few parameters
		var json = {"request" : "StartWashingProgram", 
						"Parameters" : {
							"Program" : was_selected,
							"Temperature" : temp_selected,
							"Delay" : delay
						}
				   };
		window.socket.send(JSON.stringify(json));
	}
	
	// Perform function when stop button is pressed
	stop_button.onclick = function() {
		
		// Send a start command to the websocket, along with a few parameters
		var json = {"request" : "StopWashingProgram"};
		window.socket.send(JSON.stringify(json));
	}
	
	// Perform function when update button is pressed
	update_button.onclick = function() {
		update_screen.style.display = "none";
		// Perform an update (read update file, place into wasprogramma's array and tell the user a new program has been added)
		
		// Send a start command to the websocket, along with a few parameters
		var json = {"request" : "StartWashingProgram"};
		window.socket.send(JSON.stringify(json));
	}
}

/*
	Send a request to save the user settings
	
	@param pin The pincode of the user
	@param recovery The user's selected recovery method
*/
function save_settings(pin, recovery) {
	if(!pin) { pin = window.user_json.pin; } // If the new_pin is empty, fill it with the current pin number
	
	// Send a start command to the websocket, along with a few parameters
	var json = {"request" : "UpdateUser", 
					"Parameters" : {
						"Pin" : pin, 
						"RecoveryMethod" : recovery
					}
			   };
	window.socket.send(JSON.stringify(json));
}

/*
	Populate the webpage with values obtained from the server
	Call this function only after the server has replied with a JSON array
*/
function populate_wasprogrammas() { 
	var was_dropdown = document.getElementById("wasprogrammas");

	for(var i = 0; i < window.page_json.length; i++) {
		var option = document.createElement("option");
		
		option.textContent = window.page_json[i][0]; // Fill the text content of the dropdown
		option.label = window.page_json[i][0].replace(' was', ''); // Set a label so the start command can send a name that does not contain spaces
		option.value = i; // Give the option an ID that can be used to populate the temperature dropdown
		
		was_dropdown.appendChild(option);
	}
	
	populate_temp(); // Initial call to populate_temp to fill the dropdown (since onchange doesn't get called on intial load)
}

/*
	Populate the temperature dropdown list by fetching the current value from the wasprogramma dropdown
*/
function populate_temp() {
	var was_dropdown = document.getElementById("wasprogrammas");
	var temp_dropdown = document.getElementById("temperaturen");
	
	// Empty the temperature dropdown so it can be populated again
	while(temp_dropdown.hasChildNodes()) {
		temp_dropdown.removeChild(temp_dropdown.lastChild);
	}
	
	/*
		Loop through the temperatures for each washing program and generate option fields for them
	*/
	for(var i = 0; i < window.page_json[was_dropdown.value][1].length; i++) {
		var option = document.createElement("option");
		
		option.innerHTML = window.page_json[was_dropdown.value][1][i] + "&deg;C"; // Set text for the dropdown to the number with a Celcius symbol
		option.value = window.page_json[was_dropdown.value][1][i];
		
		temp_dropdown.appendChild(option);
	}
}

/*
	Function to connect to the websocket and show message based on results
*/
function WebSocketConnect() {
	if ("WebSocket" in window) {
		ws = new WebSocket("ws://" + widow.location.hostname + "10.10.0.10:2222");
		ws.onopen = function(evt) { 
			console.log("connection open");
			
			var json = {"request" : "FetchUserSettings"};
			window.socket.send(JSON.stringify(json)); // Request the user settings from the server
			
			json = {"request" : "FetchWashingProgram"};
			window.socket.send(JSON.stringify(json)); // Request the list of washing programs from the server
		};
		ws.onclose = function(evt) { console.log("Connection closed with code: " + evt.code); }
		ws.onmessage = function(evt) { process_message(evt); }
		ws.onerror = function(evt) { console.log("websocket error: " + evt); }
		return ws;
	} else {
		alert("WebSocket NOT supported by your Browser!");
	}

}

/*
	Process the message recieved from the websocket, and fill the JSON arrays if required
*/
function process_message(message) {
	var json = JSON.parse(message.data);
	console.log(json);
	
	switch(json.response) {
		case "FetchUserSettings":
			window.user_json = json.settings;
			break;
		case "FetchWashingProgram":
			window.page_json = json.settings;
			
			break;
		case "UpdateAvailable":
			break;
		case "SettingsSaved":
			break;
		case "WashStarted":
			// Change state
			state.innerHTML = "Er is momenteel een wastaak bezig";
			break;
		case "WashStopped":
			// Change state
			state.innerHTML = "Er is momenteel geen wastaak bezig";
			
			// Set temperature and time to 0
			time.innerHTML = "00:00";
			temp.innerHTML = "0&deg;C";
			break;
		case "Temperature":
			time.innerHTML = "";
			break;
		case "Time":
			time.innerHTML = "";
			break;
		default: 
			console.log("Warning: Unknown message received: " + message);
			break;
	}
}

function check_update_status() {
	// Send a signal to (or recieve from) the websocket to check if there is an update available
	// If so, set update_available to true
	
	console.log("check_update_status()");
	//update_available = true;
}
