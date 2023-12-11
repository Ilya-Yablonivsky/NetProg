#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>

//Определение размера буфера с помощью макроса 
#define BUFSZ 128

int main(int argc, char *argv[])
{
    int sock;//Сокет 
    char buffer[BUFSZ];//Буфер для приема ответа сервера 
    struct sockaddr_in server; //Содержит информацию о сервере 
   
    // Создание сокета 
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0){
        std::cout<< "Невозможно создать сокет" <<std::endl;
        exit(1);
    }
    
    //Настройка адреса сервера 
    server.sin_family = AF_INET;
    server.sin_port = htons(13);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    //Отправка запроса серверу
    if(sendto(sock, NULL, 0, 0, (struct sockaddr*)&server, sizeof(server)) < 0) {
        std::cout<< "Ошибка при отправке запроса" <<std::endl;
        exit(1);
    }
    
    // Получение ответа от сервера
    int num_bytes = recvfrom(sock, buffer, BUFSZ, 0, NULL, NULL);
    if(num_bytes < 0){
        std::cout << "Ошибка при получении ответа от сервер" <<std::endl;
        exit(1);
    }
    
    //Вывод результата 
    std::cout << "Текущее время на сервере: "<<std::endl; 
    buffer[num_bytes] = '\0';
    std::cout << buffer << std::endl;
    
    // Закрытие сокета
    close(sock);

    return 0;
}
