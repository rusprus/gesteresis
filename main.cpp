#include <thread>
#include <iostream>
#include <string>
#include <stdio.h>
#include <chrono>

using namespace std;

int ba(0);
int y(0);
int oldY(0);
int maxY(0);
int rdv(0);
int rmv(0);
bool state(false);
bool timerOn(false);
long startTime(0);

void timerProc() {
    while (y!=255) {

      if(timerOn){

          if( ( time(0) - startTime ) > rdv  ){
              state = !state;
              timerOn = false;

              cout<<endl;
              cout<<"Значение выше ВА: "<< state << endl;
//              cout<<"Время срабатывания: "<< time(0) -  startTime   << endl;
          }
      }
      std::this_thread::sleep_for(std::chrono::nanoseconds(1000000000));
   }
}

void mainProc(){
    while(true){

        if( y==255 )return ;

        cout << "Входное значение Y: ";
        oldY = y;
        maxY = y > maxY ? y : maxY;
        cin >> y ;

        // 1 случай: предыдущий Y ниже уставки
        if(!state){
            // Текущий сигнал выше уставки

             if( (y > ba) && !timerOn ){
                 timerOn = true;
                 startTime = time(0);
                 cout<<"-->Первый случай: "<< endl;
             }
        }

        // 2 случай: предыдущий Y выше уставки + RMV
        if(state  && ( maxY > ba+rmv )){
            // Текущий сигнал выше уставки.
             if( y > ba  ){
                // Ничего не делаем
             }
             // Текущий сигнал ниже уставки.
             if( (y < ba) && !timerOn){
                timerOn = true;
                startTime = time(0);
                maxY = 0;
                cout<<"-->Второй случай: "<< endl;
             }
        }

        // 3 случай: предыдущий Y выше уставки,но ниже (уставка + RMV)
        if(state  && ( maxY < ba+rmv ) && ( maxY > ba )){
            // Текущий сигнал выше уставки.
             if( y > ba  ){
                // Ничего не делаем
             }
             // Текущий сигнал ниже уставки.

             if( (y < ba - rmv) && !timerOn){
                timerOn = true;
                startTime = time(0);
                maxY = 0;
                cout<<"-->Третий случай: "<< endl;
             }
        }
    }
}

int main()
{

cout<<"255 для выхода "<< endl;
cout << "Введите уставку ВА: ";
cin >> ba;
cout << "Введите задержку RDV: ";
cin >> rdv;
cout << "Введите отклонение от уставки RMV: ";
cin >> rmv;
startTime = time(0);

std::thread mainThread(mainProc);
std::thread timerThread(timerProc);
timerThread.join();
mainThread.join();

return 0;
}
