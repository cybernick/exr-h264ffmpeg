#include <QCoreApplication>
#include <iostream>
#include <stdint.h>
#include <QDir>
using namespace std;

int digits_pos(char *string)
{
    int pos=0;
    for(int i=0;i<strlen(string);i++)
    {
        if (isdigit(string[i])==false)
        pos++;
        else return pos;
    }
    return -1;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    if(argc!=2)
    {
        cout<<"Welcome to application that convert the sequence of images"<<endl;
        cout<<"into h264 video files in the same resolution as a picture!"<<endl;
        cout<<"To convert the sequence just write in console ./exr-h264ffmpeg <folder_name>"<<endl;
    }

    QDir dir(argv[2]);
    QFileInfoList dirContent = dir.entryInfoList(QStringList() << "*.exr", QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    QString file_name = dirContent.at(0).fileName();
    char* ch_file_name = file_name.toAscii().data();
    int pos=digits_pos(ch_file_name);
    QString prefix=file_name.mid(0,pos);
    QString number=file_name.mid(pos,file_name.size());

    QString subStr(".exr"); // String to replace.
    QString newStr(""); // Replacement string.
    number.replace(number.indexOf(subStr), subStr.size(), newStr);

    int num=number.size();
    QString command="ffmpeg -framerate 30  -y  -i ";
    command.append(prefix);
    command.append("%0");
    command.append(QString::number(num));
    command.append("d.exr ");
    command.append("-c:v libx264  out.mov");
    system(command.toAscii());
    //system("ffmpeg -f image2 -pattern_type glob -framerate 12 -i singlepart.%02d.exr -c:v libx264 -pix_fmt yuv420p -preset slow -crf 17 out.mov");-pix_fmt yuv420p
    return a.exec();
}

