// This program is a part of NITAN MudLIB

inherit ROOM;
#include <room.h>

void create()
{
        set("short", "洞口");
        set("long", @LONG
走出山洞，你的眼前豁然开朗。泉水叮咚，百鸟欢唱。时不时有
少女的笑声传了过来。两边奇峰怪石，前面一大片翠绿的草地，开放
着许多不知名的花草。香气传来，令人心情舒畅，你感到走入了世外
桃源一般。
LONG );
        set("exits", ([ /* sizeof() == 4 */
                "west" : __DIR__"gu0",
                "east" : __DIR__"dong1",
 
        ]));  
        set("outdoors","wansong");              
         
        set("coor/x",130);
        set("coor/y",0);
        set("coor/z",10);
        setup();
        replace_program(ROOM);
}        
