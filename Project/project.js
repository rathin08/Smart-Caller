const express = require("express");
const bodyParser = require("body-parser");
const cors = require("cors");
const twilio = require("twilio");

const app = express();
app.use(cors());
app.use(bodyParser.json());

const accountSid = "YOUR_ACCOUNT_SID";
const authToken = "YOUR_AUTH_TOKEN";

const client = twilio(accountSid, authToken);

app.post("/call", async (req, res) => {

  const { phone, message } = req.body;

  try {

    const call = await client.calls.create({
      twiml: `<Response>
                <Say voice="alice">${message}</Say>
              </Response>`,
      to: phone,
      from: "YOUR_TWILIO_PHONE_NUMBER"
    });

    res.send(call.sid);

  } catch (error) {
    res.status(500).send(error);
  }

});

app.listen(5000, () => {
  console.log("Server running on port 5000");
});