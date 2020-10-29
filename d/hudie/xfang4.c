// 厢房 xfang4.c
 
#include <ansi.h>
#include <room.h>

inherit ROOM;

void create() 
{ 
        set("short", "厢房");
        set("long", @LONG
这是一间别致的厢房，推开房门，揭开门帘，但见房内黑沉沉的
宛似夜晚，房间内所有的窗户都用毡子遮住了，床上的帐帘也关得严
严实实。看来这里就是「见死不救」胡青牛休息的地方了。
LONG );

        set("exits", ([
              "out" : __DIR__"caotang",
        ]));

        set("objects",([
            __DIR__"npc/hu" : 1,
        ]));
        set("no_fight",1);

        create_door("out", "竹门", "enter", DOOR_CLOSED);
        setup();
}