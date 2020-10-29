// Room in 高丽
inherit ROOM;
void create()        
{
        set("short", "青石大道");
        set("long", @LONG
你走在一条青石大道上，人来人往地非常繁忙，不时地有人骑着马
匆匆而过。南边通向高丽城。西北面是一条通向较军场的大道。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "southwest" : __DIR__"jiaojunchang",
                "northeast" : __DIR__"dadao1",
        ]));
       setup();
        replace_program(ROOM);
}        
