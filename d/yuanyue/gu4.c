// This program is a part of NITAN MudLIB

inherit ROOM;
#include <room.h>

void create()
{
        set("short", "小径");
        set("long", @LONG
一条五色彩石小径直通精舍，两旁种满鲜花，五彩缤纷。路边更
有各种果树，果(yiguo)已熟透,甚为诱人。一扇玉门在阳光下份外可
爱。
LONG );
        set("exits", ([ /* sizeof() == 4 */
                "eastup" : __DIR__"gu3",
                "westdown" : __DIR__"gu5",
 
        ]));
        set("outdoors","tieflag");      
        create_door("westdown","玉门","eastup",DOOR_CLOSED);         
        set("coor/x",90);
        set("coor/y",10);
        set("coor/z",-10);
        setup(); 
}
void init()
{
        add_action("do_get","pick");
}          
int do_get(string arg)
{
        object swo;
        if( query("mark/been_get")>10) return notify_fail("果子已被摘光了。\n");
        if(random(1000)>10) 
        { 
                swo=new(__DIR__"obj/yiguo");
                swo->move(this_player());
                addn("mark/been_get",1);
                write("你从树上摘了一个果子。\n" );
        }
        else
        { 
                swo=new(__DIR__"obj/yiguo1");
                swo->move(this_player());
                addn("mark/been_get",1);
                write("你从树上摘了一个果子. \n" );
        }
        
        return 1; 
}
void reset()
{
        ::reset();
        delete("mark/been_get");
}  
