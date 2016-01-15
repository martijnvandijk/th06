window.onload = function() {
	window.ws = WebSocketConnect(); // Connect to the websocket
	
	/*
		Values
	*/
	var user_login = false; // bool
	var update_available = true;
	var show_menu = false; // bool
	window.user_json; // json array containing user settings
	window.page_json; // json array for populating the page
	var entered_pin; // int
	
	/*
		Buttons
	*/
	var pin_button = document.getElementById("pinbutton");
	var option_button = document.getElementById("optionbutton");
	var menu_button = document.getElementById("menubutton");
	var start_button = document.getElementById("startbutton");
	var stop_button = document.getElementById("stopbutton");
	var update_button = document.getElementById("updatebutton");
	
	/*
		Visual elements
	*/
	var update_screen = document.getElementById("update-message");
	var login_screen = document.getElementById("login");
	var overlay = document.getElementById("black-overlay");
	var navbar = document.getElementById("navbar");
	
	/*
		Input elements
	*/
	var pin_field = document.getElementById("pinfield");
	
	loadJSON("js/usersettings.json"); // Load the user settings	
	
	if(user_login == false) {	
		navbar.style.display = "none";
		login_screen.style.display = "block";
	}
	
	pin_button.onclick = function() {
		entered_pin = pin_field.value;
		
		if(window.user_json.pin == entered_pin) {
			loadJSON("js/wasprogrammas.json"); // After the user has successfully logged in, populate the webpage with data from the "wasprogramma" file
			
			user_login = true;
			
			navbar.style.display = "block"; // Show the menu
			overlay.style.display = "none"; // Hide the black overlay
			document.body.style.overflow = "scroll"; // Show the scrollbar
			login_screen.style.display = "none"; // Hide the login screen
		} else {
			user_login = false;
		}
	};
	
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
		
		if((new_pin.length != 4 || isNaN(new_pin) == true) && new_pin) {
			alert("Pin moet bestaan uit 4 getallen");
		} else {
			if(document.getElementById("continue").checked == true) { // Check if the first radio button is checked
				save_settings(new_pin, "continue");
			} else { // If not, the only other option must be selected
				save_settings(new_pin, "cancel");
			}
		}
	}
	
	start_button.onclick = function() {
		// Get the selected washingprogram
		var was_dropdown = document.getElementById("wasprogrammas");
		var was_selected = was_dropdown.options[was_dropdown.selectedIndex].text;
		
		// Get the selected temperature
		var temp_dropdown = document.getElementById("temperaturen");
		var temp_selected = temp_dropdown.options[temp_dropdown.selectedIndex].value;
		
		// Get the selected time until start of program
		var duration_value = document.getElementById("duration").value;
		console.log(duration_value);
		
		// Start the washing program 
		// window.websocket.send("start_wash");
		
		// Parse reply; show to use that the program has been started
	}
	
	stop_button.onclick = function() {
		console.log("stop clicked");
		// Stop the washing program 
		// window.websocket.send("stop_wash");
		
		// Parse reply; show to use that the program has been stopped
	}
	
	update_button.onclick = function() {
		update_screen.style.display = "none";
		// Perform an update (read update file, place into wasprogramma's array and tell the user a new program has been added)
	}
}

/*
	POST to save_settings.php to save the user settings
*/
function save_settings(pin, recovery) {
	// Save user settings 
	// window.websocket.send("save_pin / save_recovery");
	
	if(!pin) { pin = window.user_json.pin; } // If the new_pin is empty, fill it with the current pin number
	
	// Write as json to file
	var new_settings = '{"pin" : "'+ pin +'", "recovery" : "'+ recovery +'"}';
	
	$.ajax({
		type: "POST",
		url: "../save_settings.php",
		data: {data:new_settings},
		dataType: 'json',
		success: function(response) {
			console.log("Success");
		}, error: function(data) {
			console.log("Error");
		},
	});
}

/*
	Populate the webpage with values obtained from the "wasprogrammas" file
	Uses JSON
*/
function fetch_wasprogrammas() { 
	// Retrieve wasprogramma's from the websocket
	// window.websocket.send("fetch_wash");
	
	var was_dropdown = document.getElementById("wasprogrammas");

	for(var i = 0; i < window.page_json.length; i++) {
		var option = document.createElement("option");
		
		option.textContent = window.page_json[i][0];
		option.value = i;
		
		was_dropdown.appendChild(option);
	}
	
	// Initial call to populate_temp to fill the dropdown (since onchange doesn't have to be called)
	populate_temp();
}

/*
	Populate the temperature dropdown list by fetching the current value from the wasprogramma dropdown
*/
function populate_temp() {
	var was_dropdown = document.getElementById("wasprogrammas");
	var temp_dropdown = document.getElementById("temperaturen");
	
	while(temp_dropdown.hasChildNodes()) {
		temp_dropdown.removeChild(temp_dropdown.lastChild);
	}
	
	/*
		Loop through the temperatures for each washing program and generate option fields for them
	*/
	for(var i = 0; i < window.page_json[was_dropdown.value][1].length; i++) {
		var option = document.createElement("option");
		
		option.innerHTML = window.page_json[was_dropdown.value][1][i] + "&deg;C";
		option.value = window.page_json[was_dropdown.value][1][i];
		
		temp_dropdown.appendChild(option);
	}
}

/*
	Custom function to load JSON from a file
*/
function loadJSON(path) {
	// Retrieve usersettings from the websocket
	// window.websocket.send("fetch_user");

    var xhr = new XMLHttpRequest();
	
    xhr.onreadystatechange = function() {
		if(xhr.readyState == 4 && xhr.status == 200) {
			var jsonArray = JSON.parse(xhr.responseText);
			if(path == "js/usersettings.json") {
				window.user_json = jsonArray;
				console.log(jsonArray);
			} else if(path == "js/wasprogrammas.json") {
				window.page_json = jsonArray;
				fetch_wasprogrammas();
			}
		}
	};
	
	// Fetch the file with timestamp in milliseconds as a nocache parameter to trick apache into thinking it's a completely new file
	xhr.open("GET", path+"?nocache="+(new Date()).getTime(), true);
	xhr.send();
}

function WebSocketConnect() {
	if ("WebSocket" in window) {
		ws = new WebSocket("ws://10.10.0.10:2222");
		ws.onopen = function(evt) { console.log("connection open"); };
		ws.onclose = function(evt) { console.log("connection closed"); };
		ws.onmessage = function(evt) {  };
		ws.onerror = function(evt) { console.log("websocket error: " + evt.data); };
		
		return ws;
	} else {
		alert("WebSocket NOT supported by your Browser!");
	}
}