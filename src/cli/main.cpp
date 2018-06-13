#include <QCoreApplication>

int main(int argc, char *argv[])
{
    printf("argc: %d\n", argc);
    if(argc != 2){
        printf("Usage: dedicatedslave arg1 [arg2... argN]\n\n"
               "TEST 123\n");
    }else{
        printf("argv[1]: %s\n", argv[1]);
    }
    QCoreApplication a(argc, argv);
    return a.exec();
}
