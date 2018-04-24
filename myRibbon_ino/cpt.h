class cpt {
  
  public:
   float val;
   float maxVal;
   float step;
   int8_t sign;
   uint8_t type;

   cpt() {

   
   }
   
   void update(float delta) {
     val += delta * step * sign;

     if(val > maxVal)
       switch(type) {
       case 0: val -= maxVal; break;
       case 1: sign = -1; break;
       }

     if(val < 0)
       switch(type) {
       case 0: val += maxVal; break;
       case 1: sign = 1; break;
       }

   }

   unsigned int getInt() {
     return uint32_t(val); 
   }

};
