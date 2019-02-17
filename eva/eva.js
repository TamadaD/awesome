new Chart(document.getElementById("myChart"), {
    type: "doughnut",
    data: {
        labels: ["赤", "青", "黄色"],
        datasets: [
            {
                data: [300, 50, 100],
                backgroundColor: [
                    "rgb(255, 99, 132)",
                    "rgb(54, 162, 235)",
                    "rgb(255, 205, 86)"
                ]
            }
        ]
    }
});