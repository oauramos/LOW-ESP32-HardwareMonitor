require('dotenv').config()

const express = require('express')
const axios = require('axios')
const app = express()

const { findById } = require('./findById')

// LibreOpenHardware - Webserver Url
const url = process.env.LOW_URL || 'http://localhost:8085/data.json'

app.get('/monitor', (req, res) => {
  res.setHeader('Content-Type', 'text/event-stream')
  res.setHeader('Cache-Control', 'no-cache')
  res.setHeader('Connection', 'keep-alive')

  const getDataById = (data, id) => findById(data, id)

  const intervalId = setInterval(async () => {
    try {
      const response = await axios.get(url)
      const data = response.data

      const hardwareInfo = (nameId, loadId, tempOrMaxId) => ({
        id: getDataById(data, nameId).Text,
        load: getDataById(data, loadId).Value,
        tempOrMax: getDataById(data, tempOrMaxId).Value
      })

      const result = {
        cpu: {
          ...hardwareInfo(43, 81, 79),
          temp: getDataById(data, 79).Value
        },
        gpu: {
          ...hardwareInfo(104, 116, 113),
          temp: getDataById(data, 113).Value
        },
        ram: {
          ...hardwareInfo(95, 97, 102),
          max: getDataById(data, 102).Value
        },
        disk: {
          ...hardwareInfo(137, 144, 139),
          temp: getDataById(data, 139).Value
        }
      }

      return res.json(result)
    } catch (error) {
      return res.status(500).send('Error fetching hardware data')
    }
  }, 100)

  req.on('close', () => {
    clearInterval(intervalId)
    res.end()
  })
})

app.listen(5000, () => {
  console.log('Server running on http://localhost:5000')
})
