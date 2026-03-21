import { useState } from "react";
import axios from "axios";

function App() {

  const [phone, setPhone] = useState("");
  const [message, setMessage] = useState("");

  const makeCall = async () => {

    await axios.post("http://localhost:5000/call", {
      phone,
      message
    });

    alert("Call initiated!");
  };

  return (
    <div style={{padding:"50px"}}>

      <h2>Smart Caller</h2>

      <input
        placeholder="Phone Number"
        value={phone}
        onChange={(e)=>setPhone(e.target.value)}
      />

      <br/><br/>

      <textarea
        placeholder="Enter message"
        value={message}
        onChange={(e)=>setMessage(e.target.value)}
      />

      <br/><br/>

      <button onClick={makeCall}>Call</button>

    </div>
  );
}

export default App;