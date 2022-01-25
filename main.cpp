#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
int ba(0);
int y(0);
int oldY(0);
int rdv(0);
int rmv(0);
bool state(false);
bool timerOn(false);
long startTime(0);


cout<<"255 для выхода "<< endl;
cout << "Введите уставку ВА: ";
cin >> ba;
cout << "Введите задержку RDV: ";
cin >> rdv;
cout << "Введите отклонение от уставки RMV: ";
cin >> rmv;
startTime = time(0);

while(true){

    if( y==255 )return 0;

    cout << "Входное значение Y: ";

    oldY = y;
    cin >> y ;

    if(timerOn){

        cout<<"delta time: "<< time(0) -  startTime   << endl;
        if( ( time(0) - startTime ) > rdv  ){
            state = !state;
        }
    }

    // 1 случай: предыдущий Y ниже уставки
    if(!state){
        // Текущий сигнал выше уставки
         if( (y > ba) && !timerOn ){
             timerOn = true;
             startTime = time(0);
         }
         // Текущий сигнал ниже уставки.
         if(y < ba){
            timerOn = false;
         }
    }

    // 2 случай: предыдущий Y выше уставки + RMV
    if(state  && ( oldY > ba+rmv )){
        // Текущий сигнал выше уставки.
         if( y > ba  ){
             timerOn = false;
         }
         // Текущий сигнал ниже уставки.
         if( (y < ba) && !timerOn){
            timerOn = true;
            startTime = time(0);
         }
    }

    // 3 случай: предыдущий Y выше уставки,но ниже (уставка + RMV)
    if(state  && ( oldY < ba+rmv ) && ( oldY > ba )){
        // Текущий сигнал выше уставки.
         if( y > ba  ){
             timerOn = false;
         }
         // Текущий сигнал ниже уставки.
         if( (y < ba) && !timerOn){
            timerOn = true;
            startTime = time(0);
         }
    }

    cout<<"Значение выше ВА: "<< state << endl;

}
return 0;
}
