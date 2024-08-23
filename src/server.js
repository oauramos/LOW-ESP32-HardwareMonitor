require('dotenv').config()

const express = require('express')
const axios = require('axios')
const app = express()

const { findById } = require('./findById')

// LibreOpenHardware - Webserver Url
const url = process.env.LOW_URL || 'http://localhost:8085/data.json'

app.get('/cpu', (req, res) => {
  res.setHeader('Content-Type', 'text/event-stream')
  res.setHeader('Cache-Control', 'no-cache')
  res.setHeader('Connection', 'keep-alive')

  const intervalId = setInterval(async () => {
    try {
      const response = await axios.get(url)
      const findCpuName = findById(response.data, 43)
      const findCpuLoad = findById(response.data, 81)
      const findCpuTemp = findById(response.data, 79)

      const result = {
        id: findCpuName.Text,
        load: findCpuLoad.Value,
        temp: findCpuTemp.Value
      }
      return res.json(result)
    } catch (error) {
      return res.status(500).send('Error fetching hardware data')
    }
  }, 1000)

  req.on('close', () => {
    clearInterval(intervalId)
    res.end()
  })
})

app.get('/gpu', (req, res) => {
  res.setHeader('Content-Type', 'text/event-stream')
  res.setHeader('Cache-Control', 'no-cache')
  res.setHeader('Connection', 'keep-alive')

  const intervalId = setInterval(async () => {
    try {
      const response = await axios.get(url)
      const findGpuName = findById(response.data, 104)
      const findGpuLoad = findById(response.data, 116)
      const findGpuTemp = findById(response.data, 113)

      const result = {
        id: findGpuName.Text,
        load: findGpuLoad.Value,
        temp: findGpuTemp.Value
      }
      return res.json(result)
    } catch (error) {
      return res.status(500).send('Error fetching hardware data')
    }
  }, 1000)

  req.on('close', () => {
    clearInterval(intervalId)
    res.end()
  })
})

app.get('/ram', (req, res) => {
  res.setHeader('Content-Type', 'text/event-stream')
  res.setHeader('Cache-Control', 'no-cache')
  res.setHeader('Connection', 'keep-alive')

  const intervalId = setInterval(async () => {
    try {
      const response = await axios.get(url)
      const findRamName = findById(response.data, 95)
      const findRamLoad = findById(response.data, 97)
      const findRamMax = findById(response.data, 102)

      const result = {
        id: findRamName.Text,
        load: findRamLoad.Value,
        max: findRamMax.Value
      }
      return res.json(result)
    } catch (error) {
      return res.status(500).send('Error fetching hardware data')
    }
  }, 1000)

  req.on('close', () => {
    clearInterval(intervalId)
    res.end()
  })
})

app.get('/disk', (req, res) => {
  res.setHeader('Content-Type', 'text/event-stream')
  res.setHeader('Cache-Control', 'no-cache')
  res.setHeader('Connection', 'keep-alive')

  const intervalId = setInterval(async () => {
    try {
      const response = await axios.get(url)
      const findDiskName = findById(response.data, 137)
      const findDiskLoad = findById(response.data, 144)
      const findDiskTemp = findById(response.data, 139)

      const result = {
        id: findDiskName.Text,
        load: findDiskLoad.Value,
        temp: findDiskTemp.Value
      }
      return res.json(result)
    } catch (error) {
      return res.status(500).send('Error fetching hardware data')
    }
  }, 1000)

  req.on('close', () => {
    clearInterval(intervalId)
    res.end()
  })
})

app.listen(5000, () => {
  console.log('Server running on http://localhost:5000')
})
