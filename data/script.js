const ws = new WebSocket("ws://192.168.4.1/ws");

const settingsButton = document.getElementById('settingsBtn');

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
};

ws.onmessage = (evt) => {
    alert('Message');
};

settingsButton.addEventListener('click', toggleSettings);