require("dotenv").config();
const express = require("express");
const bodyParser = require("body-parser");
const cors = require("cors");
const twilio = require("twilio");

const app = express();
app.use(cors());
app.use(bodyParser.json());

// Twilio credentials - Replace with your actual credentials
const accountSid = process.env.TWILIO_SID;
const authToken = process.env.TWILIO_AUTH_TOKEN;
const twilioPhoneNumber = process.env.TWILIO_PHONE;

const client = twilio(accountSid, authToken);

// Health check endpoint
app.get("/", (req, res) => {
  res.send("Server is running");
});

// Endpoint to make calls with Twilio
app.post("/call", async (req, res) => {
  const { phone, message } = req.body;

  // Validation
  if (!phone || !message) {
    return res.status(400).send({ error: "Phone number and message are required" });
  }

  try {
    const call = await client.calls.create({
      twiml: `<Response>
                <Say voice="alice">${message}</Say>
              </Response>`,
      to: phone,
      from: twilioPhoneNumber
    });

    res.send({ callSid: call.sid, status: "Call initiated" });
  } catch (error) {
    console.error("Error making call:", error);
    res.status(500).send({ error: error.message });
  }
});

// Start server
const PORT = 5000;
app.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
});
