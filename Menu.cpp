#include "Menu.h"
#include <string.h>
int Menu::interaction_menu(int* option, int max) 
{
    while(1)
    {
        int key = _getch();
        if (key == KEY_ENTER)
            return 0;
        if (key == KEY_ESCAPE)
            return -1;
        if (key == 0 || (key > 223 && key < 256)) 
        {
            key = _getch();
            switch (key) 
            {
            case KEY_PG_UP:
                *option = (*option - 1 < 0) ? max : *option - 1;
                return 1;
            case KEY_PG_DOWN:
                *option = (*option + 1 > max) ? 0 : *option + 1;
                return 1;
            case KEY_PG_LEFT:
                return REMOVE;
            case KEY_PG_RIGHT:
                return RETURN;
            }

        }
    }
}

void Menu::menu() 
{ 
    about();
    while (1) 
    {
        switch (print_menu(0, "MENU.txt"))
        {
        case -1:
            return;
        case 0:
        {
            system("cls");
            std::cout << "Please enter the path to your file and press Enter\n\
You can drag and drop your file from Explorer into this window\n";
            BitmapMonochrome BMP;
            system("cls");
            QR Q(BMP.getMonochromeImage());
            set_text("HISTORY.txt");
            add(BMP.getFilename());
            _getch();
            break;
        }

        case 1:
        {
            system("cls");
            int number = print_menu(1, "HISTORY.txt");
            if (number != -1)
            {
                for (int i = 0; i < number; i++)
                {
                    text.push(text.front()), text.pop();
                }
                BitmapMonochrome BMP(text.front());
                system("cls");
                QR Q(BMP.getMonochromeImage());
                _getch();
            }
            break;
        }
        case 2:
        {
            system("cls");
            about();
            break;
        }
        }
    }
}
void Menu::frame(int pos, int max, int length_txt) 
{
    printf("%c", (pos == 0) ? UP_RIGHT_2 : (pos == max) ? DOWN_RIGHT_2 : VERT_2_RIGHT_1);
    for (int i = 0; i < length_txt+5; i++) 
    {
        if (i == length_txt+2) 
        {
            printf("%c", (pos == 0) ? HORIZ_2_DOWN_1 : (pos == max) ? HORIZ_2_UP_1 : CROSS_1);
            continue;
        }
        printf("%c", (pos == 0 || pos == max) ? HORIZ_2 : HORIZ_1);
    }
    printf("%c%c", (pos == 0) ? UP_LEFT_2 : (pos == max) ? DOWN_LEFT_2 : VERT_2_LEFT_1, (pos == 0) ? '\n' : (pos == max) ? '\0' : '\n');
}
/**************************************************************************************/
int Menu::print_menu(bool allow_editing, const std::string path) 
{
    set_text(path);
    int choise = 0;
    while (1) 
    {
        system("cls");
        for (int number = 0; number < text.size(); number++) 
        {
            //std::string line_ = get_line();
            frame(number, text.size() + 2, max_length());
            printf("%c", VERT_2);
            std::cout << (choise == number ? "\033[42;1m " : " " ) << text[number].c_str() << " ";
            //printf((choise == number) ? "\033[42;1m %s " : " %s ", get_line());
            for(int i = strlen(text[number].c_str()); i < max_length(); i++)
                printf(" ");
            printf("\033[0m%c", VERT_1);
            printf((choise == number) ? "\033[32;1m<-\033[0m" : "  ");
            printf("%c\n", VERT_2);
        }
            if (text.size())
                frame(text.size(), text.size(), max_length());
            switch (interaction_menu(&choise, text.size() - 1))
            {
            case -1:
                return -1;
            case 0:
                if (text.begin() != text.end())
                    return choise;
            case REMOVE:
            {
                if (allow_editing)
                {
                    txt_file.open(path, std::ios::out | std::ios::trunc);
                    for (int i = 0; i < text.size(); i++)
                    {
                        if (i == choise)
                        {
                            removing.push(text.front());
                            text.pop();
                            if (choise == text.size())
                                choise--;
                        }
                        if (text.size())
                        {
                            txt_file << text.front() << std::endl;
                            text.push(text.front()), text.pop();
                        }

                        else
                            return -1;
                    }

                    //txt_file.clear(); // 
                    //txt_file.seekp(0, std::ios::beg);
                    //txt_file.write("123456789", 9);

                    txt_file.close();
                }
                break;
            }
            case RETURN:
            {
                if (allow_editing)
                {
                    rreturn_to(path);
                }
                break;
            }
            }
    }
}
/**************************************************************************************/
void Menu::set_text(std::string path) 
{
    std::string line;
    if(txt_file.is_open())
        txt_file.close();
    while (!text.empty())
        text.pop();
    txt_file.open(path);
    while(std::getline(txt_file, line))
        text.push(line);
    txt_file.close();
}

int Menu::max_length()
{
    int max_length = strlen(text.front().c_str());
    for(int i=0; i<text.size(); i++)
    {
        if(max_length < strlen(text[i].c_str()))
            max_length = strlen(text[i].c_str());
    }
    return max_length;
}

void Menu::about()
{
    std::cout << "                " << IUB << "This is a QR code scanner." << DEFAULT << std::endl;
    std::cout << "The scanner can " << IUB << "only" << DEFAULT << " read " <<  IUB << "QR codes" << DEFAULT << 
" from a "  << IUB << "Bitmap monochrome file." << DEFAULT << std::endl;

    std::cout <<  IUB << "Control" << DEFAULT << " is carried out using the " << IUB << "arrow keys" << DEFAULT << 
", " << IUB << "Enter" << DEFAULT << " and " << IUB << "Esc." << DEFAULT << std::endl;

    std::cout << "To " << IUB << "remove" << DEFAULT << " an item from history, " << IUB << "select" << DEFAULT <<
" the desired item and press the " << IUB << "left arrow key." << DEFAULT << std::endl;
    
    std::cout << "To " << IUB << "cancel" << DEFAULT << ", press the " <<  IUB << "right arrow key." << DEFAULT << std::endl;
    
    std::cout << "After closing the program you will not be able to undo the deletion in history" << std::endl;

std::cout << "\n\nPress any key to continue";
    _getch();
}

void Menu::rreturn_to(const std::string path)
{
    if (removing.size())
    {
        add(removing.top());
        removing.pop();
        txt_file.close();
        set_text("HISTORY.txt");
    }
}

void Menu::add(std::string filename)
{
    int i = 0;
    for (; i < text.size(); i++)
    {
        if (text.front() == filename.c_str())
            break;
        text.push(text.front()), text.pop();
    }
    int buf = i;
    for (; buf < text.size(); buf++)
        text.push(text.front()), text.pop();
    if (i == text.size())
    {
        txt_file.open("HISTORY.txt", std::ios::out | std::ios::app);
        txt_file << filename.c_str() << std::endl;
        txt_file.close();
    }
}
