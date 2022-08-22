function requestInfo() {
    const request = new XMLHttpRequest();
    const usr = window.localStorage.getItem('username');
    // console.log(usr)
    const url = "/plot/?username=" + usr;
    request.responseType = 'json';

    request.open('GET', url, true);

    request.addEventListener('loadstart', function () {
        document.getElementById('chartWrapper').style.display = "none";
        document.getElementById('recommendationWrapper').style.display = "none";
        document.getElementById('loading').style.display = "block";
    });

    request.onload = function() {
        processInfo(request.response);
    }

    request.send();
}

function processInfo(response) {
  const hitKeys = [];
  const hitVals = [];
  const clickKeys = [];
  const clickVals = [];
  const services = response['services'];
  const statistics = response['statistics'];
  for (let key in statistics) {
    if (key.includes("Hits")) {
      if (statistics[key] != 0) {
        hitVals.push(statistics[key]);
        key = key.substring(0, key.length - 4)
        hitKeys.push(key);
      }
    }
    if (key.includes("Clicks")) {
      if (statistics[key] != 0) {
        clickVals.push(statistics[key]);
        key = key.substring(0, key.length - 6)
        clickKeys.push(key);
      }
    }
  }

  const weighted = {'netflix':0, 'prime':0, 'hulu':0, 'disney':0, 'hbo':0, 'peacock':0, 'paramount':0, 'starz':0, 'showtime':0, 'apple':0, 'mubi':0};

  for (let key in statistics) {
    // console.log(weighted);
    if (key.includes("Hits")) {
      weighted[key.substring(0, key.length - 4)] += statistics[key];
    }
    else {
      weighted[key.substring(0, key.length - 6)] += statistics[key] * 10;

    }
  }

  weightedwo0 = weighted
  for (let key in weightedwo0) {
    if(!weightedwo0[key]) {
      delete weightedwo0[key];
    }
  }

  const items = Object.keys(weighted).map(
    (key) => { return [key, weighted[key]] });

  items.sort(
    (first, second) => { return second[1] - first[1] }
  );

  var keys = items.map(
    (e) => { return e[0] });

  createPlot(hitKeys, hitVals, "bar", 'chart1')
  createPlot(clickKeys, clickVals, "pie", 'chart2')
  createPlot(Object.keys(weightedwo0), Object.values(weightedwo0), "doughnut", 'chart3')
  // createPlot(clickKeys, clickVals, "bar", 'Most Popular Platforms Based On Title Clicks', 'chart4')

  giveRecommendations(keys, services);

  document.getElementById('chartWrapper').style.display = "block";
  document.getElementById('recommendationWrapper').style.display = "block";
  document.getElementById('loading').style.display = "none";
}

function createPlot(keys, vals, type, chartNum) {
  Chart.defaults.global.defaultFontFamily = "'Raleway'";
  bar_display = true;
  if (type == "doughnut" || type == "pie")
    bar_display = false;

  const labels = keys;
  const data1 = vals;

  const data = {
      labels: labels,
      datasets: [{
        label: 'Streaming Platforms',
        backgroundColor: [
          '#ED5565',
          '#FC6E51',
          '#FFCE54',
          '#EBCE4D',
          '#A0D468',
          '#4BCFAD',
          '#A0CECB',
          '#4FC1E9',
          '#5D9CEC',
          '#06334A',
          ],
          borderColor: [
            '#ED5565',
            '#FC6E51',
            '#FFCE54',
            '#EBCE4D',
            '#A0D468',
            '#4BCFAD',
            '#A0CECB',
            '#4FC1E9',
            '#5D9CEC',
            '#06334A',
          ],
        data: data1,
      }]
    };
  
    const config = {
    type: type,
    data: data,
    options: {
      aspectRatio: 3,
      responsive: false,
      maintainAspectRatio: true,
      scales: {
        y: {
          display: bar_display,
          grid: {
            display: bar_display,
            drawBorder: bar_display
                },
          title: {
            display: bar_display,
            text: 'Number of titles returned',
            font: {
              size: 18,
              defaultFontFamily: "Raleway"
            }
          },
          ticks: {
              color: "white"
          }
        },
        x: {
          display: bar_display,
          grid: {
            display: false,
            drawBorder: bar_display
                },
          title: {
            display: bar_display,
            text: 'Streaming Platforms',
            font: {
              size: 18,
              defaultFontFamily: "Raleway"
            }          
          },
          ticks: {
              color: "white"
          }
        }
      },
      layout: {
        padding: {
          right: 300,
          top: 100,
          left: 300}},
          plugins: {
            legend: {
              display: !bar_display,
              position: 'right'
            },
            title: {
              display: false,
            }
          }
          },

      };
      
      const myChart = new Chart(
        document.getElementById(chartNum),
        config
      );
}

function openTab(evt, tabName) {
  var i, x, tablinks;
  x = document.getElementsByClassName("tab");
  for (i = 0; i < x.length; i++) {
    x[i].style.display = "none";
  }
  tablinks = document.getElementsByClassName("tablink");
  for (i = 0; i < x.length; i++) {
    tablinks[i].className = tablinks[i].className.replace(" w3-border-indigo", "");
  }
  document.getElementById(tabName).style.display = "block";
  evt.currentTarget.firstElementChild.className += " w3-border-indigo";
}

function giveRecommendations(weighted, services) {
  services = Object.values(services)[0];
  console.log(services);
  console.log(weighted);

  let rGood = [];
  let rBad = [];
  let rNew = [];

  for (let key in weighted.slice(0,3)) {
    for (let i in services) {
      if (services[i] == weighted[key])
        rGood.push(services[i].toUpperCase());
    }
  }

  let temp = weighted.slice(7, weighted.length - 1);

  for (let key in temp) {
    for (let i in services) {
      if (services[i] == temp[key])
        rBad.push(services[i].toUpperCase());
    }
  }

  for (let key in weighted.slice(0,3)) {
    let included = false;
    for (let i in services) {
      if (services[i] == weighted[key])
        included = true;
    }
    if (!included)
      rNew.push(weighted[key].toUpperCase());
  }

  let spanSize = 0;
  if (rGood.length != 0) {
    document.getElementById("recommendationsGood").innerHTML = rGood.join(", ");
    document.getElementById("rgWrapper").style.display = "block";
    spanSize++;
  }
  if (rBad.length != 0) {
    document.getElementById("recommendationsBad").innerHTML = rBad.join(", ");
    document.getElementById("rbWrapper").style.display = "block";
    spanSize++;
  }
  if (rNew.length != 0) {
    document.getElementById("recommendationsNew").innerHTML = rNew.join(", ");
    document.getElementById("rnWrapper").style.display = "block";
    spanSize++;
  }

  if (spanSize > 0) {
    let largeScrn = 12/spanSize;
    let smallScrn = largeScrn*2;
    document.getElementById("rgWrapper").classList.add("l"+parseInt(largeScrn));
    document.getElementById("rgWrapper").classList.add("s"+parseInt(smallScrn));
    document.getElementById("rbWrapper").classList.add("l"+parseInt(largeScrn));
    document.getElementById("rbWrapper").classList.add("s"+parseInt(smallScrn));
    document.getElementById("rnWrapper").classList.add("l"+parseInt(largeScrn));
    document.getElementById("rnWrapper").classList.add("s"+parseInt(smallScrn));
  }

  // document.getElementById(idGood).innerHTML = weighted.slice(0, 3);
  // document.getElementById(idBad).innerHTML = weighted.slice(-3);
  
}