
export const UtilitarRLE = {
  
  comprima: (textOriginal) => {
    if (!textOriginal) return "";
    
    const caractere = Array.from(textOriginal);
    let rezultat = "";
    let contor = 1;
    let lungime = caractere.length; 

    for (let i = 0; i < lungime; i++) {
      /// numaram caracterele identice
      if (i + 1 < lungime && caractere[i] === caractere[i + 1]) {
        contor++;
      } else {
       
        if (contor > 2) {
            
            rezultat += caractere[i] + "|" + contor.toString(36);
        } else {
          
            rezultat += caractere[i].repeat(contor);
        }
        contor = 1; 
      }
    }
    
    return rezultat;
  },

  decomprima: (textComprimat) => {
    if (!textComprimat) return "";
    
   
    const sablon = /(.)\|([0-9a-z]+)|([\s\S])/g;
    
    let rezultatDecodat = "";
    let potrivire;
    
    sablon.lastIndex = 0;

    while ((potrivire = sablon.exec(textComprimat)) !== null) {
     
      if (potrivire[1] && potrivire[2]) {
          const caracter = potrivire[1];
         
          const numar = parseInt(potrivire[2], 36);
          
          if (numar > 50000) return "Eroare: Numar prea mare!";
          
          rezultatDecodat += caracter.repeat(numar);
      } 
      
      else if (potrivire[3]) {
          rezultatDecodat += potrivire[3];
      }
    }

    return rezultatDecodat;
  }
};