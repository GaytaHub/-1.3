#include "headfile.h"

void Hardware_Init(void);
void Software_Init(void);
void EndLine_Scan(void);

int main(void)
{  
  Hardware_Init();
  Software_Init();
  for(;;)
  {
    EndLine_Scan();
  }
}

    
