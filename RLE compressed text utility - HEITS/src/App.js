import React, { useState } from 'react';
import './App.css';

import { UtilitarRLE } from './rleLogic'; 
import FileUploader from './FileUploader';

function App() {
  /// aici tinem textul
  const [textIntrare, setTextIntrare] = useState("");
  const [textIesire, setTextIesire] = useState("");
  
  /// statistici
  const [statistici, setStatistici] = useState({ timp: "0", rata: "0.00" });
  const [status, setStatus] = useState(null);

  const executaOperatia = (tipOperatie) => {
    if (!textIntrare) {
      setStatus({ msg: "⚠ Nu ai scris nimic!", tip: "error" });
      return;
    }

    try {
      setStatus(null); 
      
      const start = performance.now(); 

      let rezultat = "";
      
      if (tipOperatie === 'comprima') {
       
        rezultat = UtilitarRLE.comprima(textIntrare);
      } else {
        
        rezultat = UtilitarRLE.decomprima(textIntrare);
      }

      const stop = performance.now(); 
      
      let tempTimp = (stop - start).toFixed(3);
      let tempRata = "0.00";
      
      if (textIntrare.length > 0) {
         tempRata = (rezultat.length / textIntrare.length).toFixed(2);
      }

      setTextIesire(rezultat);
      setStatistici({ timp: tempTimp, rata: tempRata });
      
      let mesaj = "";
      if (tipOperatie === 'comprima') mesaj = "Gata! Am comprimat.";
      else mesaj = "Gata! Am decomprimat.";
      
      setStatus({ msg: mesaj, tip: "success" });

    } catch (err) {
      console.error(err);
      setStatus({ msg: "Eroare: " + err.message, tip: "error" });
    }
  };

  return (
    <div className="App">
      <header>
        <h1>4.bin - Utilitar text cu compresie - Heist</h1>
      </header>
      
      <div className="main-container">
        <FileUploader laIncarcareFisier={(text) => setTextIntrare(text)} />

        <div className="editor-grid">
          <div className="editor-box">
            <label>INPUT</label>
            <textarea 
              value={textIntrare} 
              onChange={(e) => setTextIntrare(e.target.value)} 
              placeholder="..."
            />
            <div className="info-tag">Caractere: {textIntrare.length}</div>
          </div>

          <div className="editor-box">
            <label>OUTPUT</label>
            <textarea 
              readOnly 
              value={textIesire} 
              placeholder="..." 
              className="output-area"
            />
            <div className="info-tag">Caractere: {textIesire.length}</div>
          </div>
        </div>

        <div className="controls">
          <button className="btn compress" onClick={() => executaOperatia('comprima')}>Comprimă</button>
          <button className="btn decompress" onClick={() => executaOperatia('decomprima')}>Decomprimă</button>
        </div>

        <div className="metrics-bar">
          <div className="metric">
            <span className="label">Timp Execuție</span>
            <span className="value">{statistici.timp} ms</span>
          </div>
          <div className="metric">
            <span className="label">Rata</span>
            <span className="value">{statistici.rata}</span>
          </div>
        </div>

        {status && (
          <div className={`status-message ${status.tip}`}>
            {status.msg}
          </div>
        )}
      </div>
    </div>
  );
}

export default App;