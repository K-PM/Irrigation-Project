/** @type {Socket} */
const socket = io()

const hA = document.getElementById("humA")
const hD = document.getElementById("humD")
const Tim = document.getElementById("tim")

const hAt = document.getElementById("humA-tit")
const hDt = document.getElementById("humD-tit")
const timt = document.getElementById("tim-tit")

socket.on('updateData',(info)=>{
    if(!hD.classList.contains("info")){

        hD.classList.add("info")
        hA.classList.add("info")
        Tim.classList.add("info")

        hAt.classList.add('title-box')
        hDt.classList.add('title-box')
        timt.classList.add('title-box')

    }
    Tim.textContent = `${info.riego}`
    hA.textContent = `${info.humA} %`
    hD.textContent = `${info.humD} %`
})