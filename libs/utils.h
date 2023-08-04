#ifndef UTILS_H
#define UTILS_H



void printString(String message){
    if (DEBUG){
        Serial.println(message);
    }
}


void printStringNoBreak(String message){
    if (DEBUG){
        Serial.print(message);
    }
}


void printJson(DynamicJsonDocument doc){
    if (DEBUG){
        serializeJsonPretty(doc, Serial);
        Serial.println();
    }
}



#endif // UTILS_H