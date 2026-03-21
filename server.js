const express = require("express");
const bodyParser = require("body-parser");
const cors = require("cors");
const twilio = require("twilio");

const app = express();
app.use(cors());
app.use(bodyParser.json());

// Twilio credentials - Replace with your actual credentials
const accountSid = "AC231038ad3856c1063b33650d07bd2251";
const authToken = "746944e336ed612faf9a584524f912b7";
const twilioPhoneNumber = "+12762593598";

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
