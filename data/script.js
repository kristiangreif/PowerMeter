const ws = new WebSocket("ws://192.168.4.1/ws");

const settingsButton = document.getElementById('settingsBtn');
const saveButton = document.getElementById('saveBtn');

const voltageDisplay = document.getElementById('voltage');
const currentDisplay = document.getElementById('current');
const powerDisplay = document.getElementById('power');
const capacityDisplay = document.getElementById('capacity');
const energyDisplay = document.getElementById('energy');

let display = false;

const toggleSettings = () => {
    const settingsForm = document.getElementById('settingsForm');

    display = !display;
    if (display) {
        if (settingsForm.classList.contains('d-none')) {
            settingsForm.classList.remove('d-none');   
        }
    } else {
        settingsForm.classList.add('d-none'); 
    }
}

ws.onopen = () => {
    alert('Connection Established');
    saveButton.addEventListener('click', saveSettings);
};

ws.onmessage = (evt) => {
    const readings = JSON.parse(evt.data);
    
    voltageDisplay.innerHTML = readings['voltage'];
    currentDisplay.innerHTML = readings['current'];
    powerDisplay.innerHTML = readings['power'];
    capacityDisplay.innerHTML = readings['capacityAh'];
    energyDisplay.innerHTML = readings['capacityWh'];
};

const saveSettings = () => {
    const limitStates = document.getElementsByClassName('limitEnabled');
    const limits = document.getElementsByClassName('limit');

    let settings = {
        'uvlimit': [false, 0],
        'ovlimit': [false, 0],
        'ovclimit': [false, 0],
        'ovplimit': [false, 0]
    };

    let n = 0;
    for(const setting in settings){
        settings[setting][0] = limitStates[n].checked;
        settings[setting][1] = parseFloat(limits[n].value);
        n = n + 1;
    }

    ws.send(JSON.stringify(settings));
}

settingsButton.addEventListener('click', toggleSettings);