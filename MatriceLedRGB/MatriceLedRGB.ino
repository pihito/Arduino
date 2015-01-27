// 2-dimensional array of row pin numbers:
const int rows[8] = {
  0,1,2,3,4,5,6,7 };

// 2-dimensional array of column pin numbers:
const int cols[8] = {
  6,11,10,3,17,4,8,9  };

// 2-dimensional array of pixels:
int pixels[8][8];

void setup() {
  for(int row = 0;row<8;row++)
  {
     pinMode(rows[row], OUTPUT); 
  } 
}

void loop() {
  
  for(int row = 0;row<8;row++)
  {
     digitalWrite(rows[row], HIGH); 
     delay(1000);
     digitalWrite(rows[row], LOW); 
  }
}
