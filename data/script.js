let voltageChart = null;
let currentChart = null;
let powerChart = null;
let capacityAhChart = null;
let capacityWhChart = null;

(async function () {
	voltageChart = new Chart(document.getElementById("voltageChart"), {
		type: "line",
		data: {
			labels: [
				"2023-03-01T08:00:00",
				"2023-03-01T08:00:01",
				"2023-03-01T08:00:02",
				"2023-03-01T08:01:03",
				"2023-03-01T08:01:04",
				"2023-03-01T08:01:05",
				"2023-03-01T08:10:02",
			],
			datasets: [
				{
					label: "My First Dataset",
					data: [65, 59, 80, 81, 56, 55, 40],
					fill: false,
					borderColor: "rgb(75, 192, 192)",
					tension: 0.01,
				},
			],
		},
		options: {
			plugins: {
				legend: {
					display: false, // Remove the legend
				},
			},

			scales: {
				x: {
					grid: {
						color: "rgb(110, 110, 110)", // Set gridline color to white
					},

					ticks: {
						color: "white", // Set tick color to white
					},

					title: {
						display: true,
						text: "Time", // Add title to x-axis
						color: "white",
					},

					type: "time",
					time: {
						unit: "minute",
						displayFormats: {
							day: "HH:mm:ss",
						},
					},
				},
				y: {
					grid: {
						color: "rgb(110, 110, 110)", // Set gridline color to white
					},
					ticks: {
						color: "white", // Set tick color to white
					},
					// title: {
					//     display: true,
					//     text: 'Voltage [V]', // Add title to x-axis
					//     color: 'white'
					// },
					beginAtZero: true,
				},
			},
		},
	});

	currentChart = new Chart(document.getElementById("currentChart"), {
		type: "line",
		data: {
			labels: [
				"2023-03-01T08:00:00",
				"2023-03-01T08:00:01",
				"2023-03-01T08:00:02",
				"2023-03-01T08:01:03",
				"2023-03-01T08:01:04",
				"2023-03-01T08:01:05",
				"2023-03-01T08:10:02",
			],
			datasets: [
				{
					label: "My First Dataset",
					data: [65, 59, 80, 81, 56, 55, 40],
					fill: false,
					borderColor: "rgb(234, 41, 86)",
					tension: 0.1,
				},
			],
		},
		options: {
			plugins: {
				legend: {
					display: false, // Remove the legend
				},
			},

			scales: {
				x: {
					grid: {
						color: "rgb(110, 110, 110)", // Set gridline color to white
					},

					ticks: {
						color: "white", // Set tick color to white
					},

					title: {
						display: true,
						text: "Time", // Add title to x-axis
						color: "white",
					},
					type: "time",
					time: {
						unit: "minute",
						displayFormats: {
							day: "HH:mm:ss",
						},
					},
				},
				y: {
					grid: {
						color: "rgb(110, 110, 110)", // Set gridline color to white
					},
					ticks: {
						color: "white", // Set tick color to white
					},
					// title: {
					//     display: true,
					//     text: 'Voltage [V]', // Add title to x-axis
					//     color: 'white'
					// },
					beginAtZero: true,
				},
			},
		},
	});

	powerChart = new Chart(document.getElementById("powerChart"), {
		type: "line",
		data: {
			labels: [
				"2023-03-01T08:00:00",
				"2023-03-01T08:00:01",
				"2023-03-01T08:00:02",
				"2023-03-01T08:01:03",
				"2023-03-01T08:01:04",
				"2023-03-01T08:01:05",
				"2023-03-01T08:10:02",
			],
			datasets: [
				{
					label: "My First Dataset",
					data: [65, 59, 80, 81, 56, 55, 40],
					// fill: {
					// 	target: "origin",
					// 	above: "rgba(34, 206, 111, 0.19)", // Area will be red above the origin
					// },
					borderColor: "rgb(34, 206, 111)",
					tension: 0.1,
				},
			],
		},
		options: {
			plugins: {
				legend: {
					display: false, // Remove the legend
				},
			},

			scales: {
				x: {
					grid: {
						color: "rgb(110, 110, 110)", // Set gridline color to white
					},

					ticks: {
						color: "white", // Set tick color to white
					},

					title: {
						display: true,
						text: "Time", // Add title to x-axis
						color: "white",
					},
					type: "time",
					time: {
						unit: "minute",
						displayFormats: {
							day: "HH:mm:ss",
						},
					},
				},
				y: {
					grid: {
						color: "rgb(110, 110, 110)", // Set gridline color to white
					},
					ticks: {
						color: "white", // Set tick color to white
					},
					// title: {
					//     display: true,
					//     text: 'Voltage [V]', // Add title to x-axis
					//     color: 'white'
					// },
					beginAtZero: true,
				},
			},
		},
	});

	capacityAhChart = new Chart(document.getElementById("capacityAhChart"), {
		type: "line",
		data: {
			labels: [
				"2023-03-01T08:00:00",
				"2023-03-01T08:00:01",
				"2023-03-01T08:00:02",
				"2023-03-01T08:01:03",
				"2023-03-01T08:01:04",
				"2023-03-01T08:01:05",
				"2023-03-01T08:10:02",
			],
			datasets: [
				{
					label: "My First Dataset",
					data: [65, 59, 80, 81, 56, 55, 40],
					fill: {
						target: "origin",
						above: "rgba(227, 166, 34, 0.19)", // Area will be red above the origin
					},
					borderColor: "rgb(227, 166, 34)",
					tension: 0.1,
				},
			],
		},
		options: {
			plugins: {
				legend: {
					display: false, // Remove the legend
				},
			},

			scales: {
				x: {
					grid: {
						color: "rgb(110, 110, 110)", // Set gridline color to white
					},

					ticks: {
						color: "white", // Set tick color to white
					},

					title: {
						display: true,
						text: "Time", // Add title to x-axis
						color: "white",
					},
					type: "time",
					time: {
						unit: "minute",
						displayFormats: {
							day: "HH:mm:ss",
						},
					},
				},
				y: {
					grid: {
						color: "rgb(110, 110, 110)", // Set gridline color to white
					},
					ticks: {
						color: "white", // Set tick color to white
					},
					// title: {
					//     display: true,
					//     text: 'Voltage [V]', // Add title to x-axis
					//     color: 'white'
					// },
					beginAtZero: true,
				},
			},
		},
	});

	capacityWhChart = new Chart(document.getElementById("capacityWhChart"), {
		type: "line",
		data: {
			labels: [
				"2023-03-01T08:00:00",
				"2023-03-01T08:00:01",
				"2023-03-01T08:00:02",
				"2023-03-01T08:01:03",
				"2023-03-01T08:01:04",
				"2023-03-01T08:01:05",
				"2023-03-01T08:10:02",
			],
			datasets: [
				{
					label: "My First Dataset",
					data: [65, 59, 80, 81, 56, 55, 40],
					fill: {
						target: "origin",
						above: "rgba(117, 34, 206, 0.19)", // Area will be red above the origin
					},
					borderColor: "rgb(117, 34, 206)",
					tension: 0.1,
				},
			],
		},
		options: {
			plugins: {
				legend: {
					display: false, // Remove the legend
				},
			},

			scales: {
				x: {
					grid: {
						color: "rgb(110, 110, 110)", // Set gridline color to white
					},

					ticks: {
						color: "white", // Set tick color to white
					},

					title: {
						display: true,
						text: "Time", // Add title to x-axis
						color: "white",
					},
					type: "time",
					time: {
						unit: "minute",
						displayFormats: {
							day: "HH:mm:ss",
						},
					},
				},
				y: {
					grid: {
						color: "rgb(110, 110, 110)", // Set gridline color to white
					},
					ticks: {
						color: "white", // Set tick color to white
					},
					// title: {
					//     display: true,
					//     text: 'Voltage [V]', // Add title to x-axis
					//     color: 'white'
					// },
					beginAtZero: true,
				},
			},
		},
	});
})();

const ws = new WebSocket("ws://192.168.4.1/ws");

const settingsButton = document.getElementById("settingsBtn");
const saveButton = document.getElementById("saveBtn");

// const startButton = document.getElementById("startBtn");
// const resetButton = document.getElementById("resetBtn");

const voltageDisplay = document.getElementById("voltage");
const currentDisplay = document.getElementById("current");
const powerDisplay = document.getElementById("power");
const capacityDisplay = document.getElementById("capacity");
const energyDisplay = document.getElementById("energy");

let display = false;

const modal = document.getElementById("exampleModal");

modal.addEventListener("shown.bs.modal", () => {
	saveButton.focus();
	saveButton.addEventListener("click", saveSettings);
});

// startButton.addEventListener("click", () => {
// 	startButton.classList.toggle("btn-success");
// 	startButton.classList.toggle("btn-warning");

// 	startButton.innerText = startButton.classList.contains("btn-warning")
// 		? "Pause"
// 		: "Start";
// });

const toggleSettings = () => {
	const settingsForm = document.getElementById("settingsForm");

	display = !display;
	if (display) {
		if (settingsForm.classList.contains("d-none")) {
			settingsForm.classList.remove("d-none");
		}
	} else {
		settingsForm.classList.add("d-none");
	}
};

ws.onopen = () => {
	console.log("Connection Established");
};

ws.onclose = () => {
	queryInProgress = false;
	console.log("Connection Terminated");
};

let primaryReadings = {
	voltage: {
		labels: [],
		data: [],
		chart: voltageChart,
	},
	current: {
		labels: [],
		data: [],
		chart: currentChart,
	},
	power: {
		labels: [],
		data: [],
		chart: powerChart,
	},
	capacity_ah: {
		labels: [],
		data: [],
		chart: capacityAhChart,
	},
	capacity_wh: {
		labels: [],
		data: [],
		chart: capacityWhChart,
	},
};

let queryInProgress = false;
const querySpinner = document.getElementById("querySpinner");
const queryAlert = document.getElementById("queryAlert");

ws.onmessage = (evt) => {
	if (evt.data === "QUERY_STARTED") {
		for (const series in primaryReadings) {
			if (Object.prototype.hasOwnProperty.call(primaryReadings, series)) {
				primaryReadings[series].labels = [];
				primaryReadings[series].data = [];
			}
		}

		queryInProgress = true;

		querySpinner.classList.remove("d-none");
		queryAlert.classList.add("d-none");
		return;
	}

	if (evt.data === "QUERY_FINISHED" || evt.data === "QUERY_ERROR") {
		queryInProgress = false;
		querySpinner.classList.add("d-none");

		if (evt.data === "QUERY_ERROR") queryAlert.classList.remove("d-none");

		for (const series in primaryReadings) {
			if (Object.prototype.hasOwnProperty.call(primaryReadings, series)) {
				if (!primaryReadings[series].chart) continue;

				primaryReadings[series]["chart"].data.labels =
					primaryReadings[series].labels;
				primaryReadings[series]["chart"].data.datasets[0].data =
					primaryReadings[series].data;

				primaryReadings[series].chart.update();
			}
		}

		// console.log(primaryReadings);

		return;
	}

	if (queryInProgress) {
		const csvLines = evt.data.split("\n");

		csvLines.forEach((csvLine) => {
			const parsedCsv = csvLine.split(",");

			if (parsedCsv.length !== 3) return;

			const field = parsedCsv[0];
			const timestamp = parsedCsv[1];
			const value = parseFloat(parsedCsv[2]);

			primaryReadings[field].labels.push(timestamp);
			primaryReadings[field].data.push(value);
		});

		return;
	}

	const readings = JSON.parse(evt.data);

	voltageDisplay.innerHTML = readings["voltage"];
	currentDisplay.innerHTML = readings["current"];
	powerDisplay.innerHTML = readings["power"];
	capacityDisplay.innerHTML = readings["capacityAh"];
	energyDisplay.innerHTML = readings["capacityWh"];
};

const saveSettings = () => {
	const limitStates = document.getElementsByClassName("limitEnabled");
	const limits = document.getElementsByClassName("limit");

	let settings = {
		uvlimit: [false, 0],
		ovlimit: [false, 0],
		ovclimit: [false, 0],
		ovplimit: [false, 0],
	};

	let n = 0;
	for (const setting in settings) {
		settings[setting][0] = limitStates[n].checked || false;
		settings[setting][1] = parseFloat(limits[n].value || 0);
		n = n + 1;
	}
	console.log(settings);

	const settingSuccess = document.getElementById("settingsSuccess");

	if (queryInProgress) {
		console.log("waiting for query to finish");
		return;
	}

	try {
		ws.send(JSON.stringify(settings));

		settingSuccess.classList.add("alert-success");
		settingSuccess.classList.remove("alert-danger");
		settingSuccess.innerText = "Settings saved successfully.";
	} catch (error) {
		console.log(error);

		settingSuccess.classList.add("alert-danger");
		settingSuccess.classList.remove("alert-success");
		settingSuccess.innerText = "Settings could not be saved.";
	} finally {
		settingSuccess.classList.remove("visually-hidden");

		setTimeout(() => {
			settingSuccess.classList.add("visually-hidden");
		}, 5000);
	}
};

const handleInput = () => {
	const numberInputs = document.querySelectorAll('input[type="number"]');

	for (const input of numberInputs) {
		input.addEventListener("input", (event) => {
			if (event.target.value !== "") {
				if (isNaN(event.target.value)) {
					event.target.value = 0;
				} else {
					if (parseFloat(event.target.value) < 0) {
						event.target.value = 0;
					}

					if (event.target.classList.contains("voltageSetting")) {
						if (parseFloat(event.target.value) > 50.0) {
							event.target.value = 50.0;
						}
					} else if (event.target.classList.contains("currentSetting")) {
						if (parseFloat(event.target.value) > 100.0) {
							event.target.value = 100.0;
						}
					} else if (event.target.classList.contains("powerSetting")) {
						if (parseInt(event.target.value) > 5000) {
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

document.addEventListener("DOMContentLoaded", (event) => {
	const now = new Date();
	const oneHourAgo = new Date(now.getTime() - 60 * 60 * 1000);

	const formatDateTime = (date) => {
		const year = date.getFullYear();
		const month = String(date.getMonth() + 1).padStart(2, "0");
		const day = String(date.getDate()).padStart(2, "0");
		const hours = String(date.getHours()).padStart(2, "0");
		const minutes = String(date.getMinutes()).padStart(2, "0");
		const seconds = String(date.getSeconds()).padStart(2, "0");
		return `${year}-${month}-${day}T${hours}:${minutes}:${seconds}`;
	};

	document.getElementById("fromDateTime").value = formatDateTime(oneHourAgo);
	document.getElementById("toDateTime").value = formatDateTime(now);
});

const timeRangeApplyButton = document.getElementById("timeRangeApply");

timeRangeApplyButton.addEventListener("click", () => {
	let fromTime = document.getElementById("fromDateTime").value;
	let toTime = document.getElementById("toDateTime").value;

	if (fromTime.length === 16) fromTime += ":00";
	if (toTime.length === 16) toTime += ":00";

	// Convert to Date object
	const utcFromTime = new Date(fromTime);
	const utcToTime = new Date(toTime);

	// Convert to UTC string
	const utcFromTimeString = utcFromTime.toISOString().slice(0, -5);
	const utcToTimeString = utcToTime.toISOString().slice(0, -5);

	const queryTimeInfo = `dtinfo.S${utcFromTimeString}E${utcToTimeString}`;

	if (queryTimeInfo.length !== 47) return;

	if (queryInProgress) {
		console.log("waiting for query to finish");
		return;
	}

	try {
		ws.send(queryTimeInfo);
	} catch (error) {
		console.log(error);
	}
});
