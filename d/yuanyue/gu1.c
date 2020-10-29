// This program is a part of NITAN MudLIB

inherit ROOM;
#include <room.h>

void create()
{
        int i;
        object girl;
        set("short", "谷中");
        set("long", @LONG
溪流蜿蜒如带，朱栏横跨水上，几只乳燕在花林中飞旋来去。草
坪上土墩间，斜坐着几个披发少女，或披轻纱，或着柔袍，都在盈盈
浅笑，流眸低语。
LONG );
        set("exits", ([ /* sizeof() == 4 */
                "south" : __DIR__"gu0",
                "west" : __DIR__"gu2",
      
        ]));  
        set("objects", ([
                CLASS_D("mojiao/chunhua") : 1,
                CLASS_D("mojiao/qiuyue") : 1,
        ]) );
        set("outdoors","wansong");      
        set("coor/x",120);
        set("coor/y",10);
        set("coor/z",10);
        setup(); 
} 
