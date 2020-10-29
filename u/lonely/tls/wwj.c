#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "无无境");
        set("long",@LONG
忽然眼前景物一变，一座半人高矮围墙里竹林似海，幽静无比，小路
从中轻轻穿过，通向院外的雨花院。这里种植的全是西南名竹--云竹。每
当轻风吹过，吹得竹干摇摆，如云如海，在你身边一浪浪抚过，使你心中
似有所动。东边一条石板路延伸向远方。
LONG);
	set("outdoors","天龙寺");
        set("exits", ([
		"north": __DIR__"yuhua",
		"south": __DIR__"road2", 
	        "east": __DIR__"road3",
		]));
        set("coor/x",-310);
  set("coor/y",-300);
   set("coor/z",40);
   setup();
}
