import React, { useState } from 'react';


const FileUploader = ({ laIncarcareFisier }) => {
  const [trageFisier, setTrageFisier] = useState(false);
  const [numeFisier, setNumeFisier] = useState(null);

  const proceseazaFisier = (fisier) => {
    console.log("fisier prins:", fisier);

    if (!fisier) return;

    if (!fisier.name.endsWith('.txt')) {
       alert("Eroare: Doar fisiere .txt!");
       return;
    }

    const cititor = new FileReader();
    
    cititor.onload = (e) => {
      
      laIncarcareFisier(e.target.result);
      setNumeFisier(fisier.name);
    };

    cititor.onerror = () => alert("Nu am putut citi fisierul.");
    
    cititor.readAsText(fisier);
  };

  const onDragOver = (e) => {
    e.preventDefault(); 
    setTrageFisier(true);
  };

  const onDragLeave = (e) => {
    e.preventDefault();
    setTrageFisier(false);
  };

  const onDrop = (e) => {
    e.preventDefault();
    setTrageFisier(false);
    
    if (e.dataTransfer.files && e.dataTransfer.files.length > 0) {
      proceseazaFisier(e.dataTransfer.files[0]);
    }
  };

  const onInputChange = (e) => {
    if (e.target.files.length > 0) {
      proceseazaFisier(e.target.files[0]);
    }
    e.target.value = null; 
  };

  return (
    <div 
      className={`uploader ${trageFisier ? 'drag-active' : ''}`}
      onDragOver={onDragOver}
      onDragLeave={onDragLeave}
      onDrop={onDrop}
    >
      <div className="uploader-content">
        {numeFisier ? (
          <div>
            <span style={{fontSize: '20px', fontWeight:'bold', color: '#27ae60'}}>✅</span>
            <p style={{margin: '5px 0'}}>Fisier selectat:</p>
            <strong style={{textDecoration:'underline'}}>{numeFisier}</strong>
          </div>
        ) : (
          <div>
            <span style={{fontSize: '30px', color: '#3498db'}}>📂</span>
            <p style={{fontWeight: 'bold'}}>TRAGE FISIER AICI</p>
            <p style={{fontSize: '12px', color: '#7f8c8d'}}>(sau click pentru selectare)</p>
          </div>
        )}
      </div>
      
      <input 
        type="file" 
        accept=".txt" 
        onChange={onInputChange} 
        title=" " 
      />
    </div>
  );
};

export default FileUploader;