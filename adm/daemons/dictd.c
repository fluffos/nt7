// Copyright (C) 2005, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// dictd.c 字典精灵

#include <ansi.h>
#include <net/socket.h>  

inherit F_DBASE; 

nosave mapping socket_info = allocate_mapping(0);
void get_translated(int);

int clean_up() { return 1; } 

void create() 
{ 
        seteuid(ROOT_UID); 
        set("channel_id", "字典精灵"); 
        CHANNEL_D->do_channel(this_object(), "sys", "字典精灵已经启动。"); 
} 

void translate(object user, string sentence, string language)
{
        int err, fd;

        if( !objectp(user) || !stringp(sentence) || !stringp(language) ) 
                return ;

        fd = socket_create(STREAM, "read_callback", "close_socket");

        if( fd < 0 )
        {
                tell_object(user, HIR "翻译失败, 请稍后在试。\n" NOR); 
                return;
        }

        // err = socket_connect(fd, "64.233.189.104 80", "read_callback", "write_callback" );
   err = socket_connect(fd, "203.208.36.17 80", "read_callback", "write_callback" );

        if( err != EESUCCESS )
        {
                tell_object(user, HIR "翻译失败, 请稍后在试。\n" NOR);
                return;
        }     

        sentence = replace_string(sentence, "\n", "_LINE_");
        sentence = replace_string(sentence, " ", "%20");

        socket_info[fd] = allocate_mapping(4);
        socket_info[fd]["user"] = user;
        socket_info[fd]["sentence"] = sentence;
        socket_info[fd]["language"] = language;
        socket_info[fd]["translate"] = "";
        
        return ;
}

int close_socket(int fd)
{
        socket_close(fd);
        get_translated(fd);
        map_delete(socket_info, fd);
}

void read_callback(int fd, mixed message)
{
        socket_info[fd]["translate"] += message;
        socket_write(fd, "\n");
        return ;
}

void write_callback(int fd)
{
        if( socket_info[fd]["language"] == "en" )
                socket_write(fd, sprintf("GET /translate_t?ie=gb&oe=gb&langpair=zh-CN|en&text=%s HTTP/1.1\n\n", 
                                         socket_info[fd]["sentence"]));
        else
                socket_write(fd, sprintf("GET /translate_t?ie=gb&oe=gb&langpair=en|zh-CN&text=%s HTTP/1.1\n\n", 
                                         socket_info[fd]["sentence"]));
        return ;
}

void get_translated(int fd)
{
        string translate;

        if( sscanf(socket_info[fd]["translate"], "%*s<textarea name=utrans %*s>%s</textarea></td>%*s", translate) != 4 )
        {
                tell_object(socket_info[fd]["user"], HIR "翻译失败：\n" NOR + socket_info[fd]["sentence"] + "\n");
                tell_object(socket_info[fd]["user"], HIR "翻译失败：\n" NOR + socket_info[fd]["translate"] + "\n");
                return ;
        }

        translate = replace_string(translate, "_LINE_", "\n");

        translate = sprintf(HIC "您查询的为 : %s "NOR"\n%s\n" HIR "%s\n\n" NOR, 
                            socket_info[fd]["sentence"], repeat_string("=", 50), translate);


        tell_object(socket_info[fd]["user"], translate);

        return ;
}

mapping query_sockets()
{
        return socket_info;
}
