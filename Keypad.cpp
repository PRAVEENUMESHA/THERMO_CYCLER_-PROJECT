int threshold[10] = {204, 146, 78, 371, 334, 293, 481, 456, 429, 541};
// char keypad[16]={'1','2','3','4','5','6','B','7','8','9','C','*','0','#','D'};
int keypad[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
// char Keycar[6] ={'A','B','C','D','*','#'};
// int idckey[10] = {0, 146, 78, 371, 334, 293, 481, 456, 429, 541}
void setup()
{
    Serial.begin(9600);
}
void loop()
{
    long int A = ABC();
    if (A > 0)
    {
        long int B = A;
      Serial.println("output:");
      while(B!=0)
      {
        Serial.println(B);
        B--;
      }
    }
   
}

// taking keypad input
long int ABC()
{
    int value = analogRead(A0);
    static long val_cur = 0;
    bool check_ = 0;
    for (int i = 0; i < 10; i++)
    {
        if (abs(value - threshold[i]) < 5)
        {
            int val = keypad[i];
            val_cur = (val_cur * 10) + val;
            Serial.println(val_cur);
            while (analogRead(A0) < 1000)
            {
                delay(1);
            }
        }
        if (abs(value - 500) < 5)
        {
            long int last = val_cur;
            val_cur = 0;
            Serial.println(last);
            while (analogRead(A0) < 1000)
            {
                delay(1);
            }
            return last;
        }
    }
}
