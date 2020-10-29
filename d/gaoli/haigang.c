// Room in 高丽
inherit ROOM;
void create()        
{
        set("short", "海港");
        set("long", @LONG
这里是从高丽出海的必经之地，从这里上船可以直接到达扬州。这
里非常热闹，停泊着各种船只，有货船，商船等等。很多旅客从这里进
出港口，有从中原来的，也有从其他地方来的。许多小贩在这里叫卖。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "west" : __DIR__"yucun",
        ]));
       setup();
        replace_program(ROOM);
}        
