String oldPath = "";
//String path = "LBLLLBSBLLBSLL";
String path = "SLBLSLBLSR";
String toFind[] = {"LBR","LBS", "LBL", "RBL", "SBL"};
String toReplace[] = {"B","R","S","B","R"};
int possibilities = sizeof(toFind)/sizeof(String);
int counter = 0,i;

void optimizePath()
{
  while(true)
  {
    oldPath = path;
    for(i=0; i<possibilities; i++)
      path.replace(toFind[i], toReplace[i]);
    //Serial.println(path);
    if(oldPath == path)
      break;
    counter++;
  }  
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  optimizePath();
  Serial.print("Answer: ");
  Serial.println(path);
}
