const ws = new WebSocket("ws://192.168.4.1/ws");

const settingsButton = document.getElementById('settingsBtn');
const saveButton = document.getElementById('saveBtn');

const startButton = document.getElementById('startBtn');
const resetButton = document.getElementById('resetBtn');

const voltageDisplay = document.getElementById('voltage');
const currentDisplay = document.getElementById('current');
const powerDisplay = document.getElementById('power');
const capacityDisplay = document.getElementById('capacity');
const energyDisplay = document.getElementById('energy');

let display = false;

const modal = document.getElementById('exampleModal');

modal.addEventListener('shown.bs.modal', () => {
    saveButton.focus();
    saveButton.addEventListener('click', saveSettings);
});

startButton.addEventListener('click', () => {
    startButton.classList.toggle('btn-success');
    startButton.classList.toggle('btn-warning');

    startButton.innerText =  startButton.classList.contains('btn-warning') ? 'Pause' : 'Start';
});

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
        'event': 'saveSettings',
        'payload': {
            'uvlimit': [false, 0],
            'ovlimit': [false, 0],
            'ovclimit': [false, 0],
            'ovplimit': [false, 0]
        }
    };

    let n = 0;
    for(const setting in settings){
        settings[setting][0] = limitStates[n].checked;
        settings[setting][1] = parseFloat(limits[n].value);
        n = n + 1;
    }
    console.log(settings);

    const settingSuccess = document.getElementById('settingsSuccess');

    try {
        ws.send(JSON.stringify(settings));

        settingSuccess.classList.add('alert-success');
        settingSuccess.classList.remove('alert-danger');
        settingSuccess.innerText = 'Settings saved successfully.';
    } catch (error) {
        console.log(error);

        settingSuccess.classList.add('alert-danger');
        settingSuccess.classList.remove('alert-success');
        settingSuccess.innerText = 'Settings could not be saved.';
    } finally {
        settingSuccess.classList.remove('visually-hidden');
    
        setTimeout(() => {
            settingSuccess.classList.add('visually-hidden');
        }, 5000);
    }
    
    
}

const handleInput = () => {
    const numberInputs = document.querySelectorAll('input[type="number"]');
  
    for (const input of numberInputs) {
      input.addEventListener('input', (event) => {
        if(event.target.value !== ''){
            if(isNaN(event.target.value)){
                event.target.value = 0;
            } else{
                if (parseFloat(event.target.value) < 0) {
                    event.target.value = 0;
                }

                if(event.target.classList.contains('voltageSetting')){
                    if(parseFloat(event.target.value) > 50.0){
                        event.target.value = 50.0;
                    }
                } else if(event.target.classList.contains('currentSetting')){
                    if(parseFloat(event.target.value) > 100.0){
                        event.target.value = 100.0;
                    }
                } else if(event.target.classList.contains('powerSetting')){
                    if(parseInt(event.target.value) > 5000){
                        event.target.value = 5000;
                    } 
                }
            }
        }
      });
    }
};

handleInput();

// settingsButton.addEventListener('click', toggleSettings);