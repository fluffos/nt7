inherit ROOM; 
void create() 
{ 
        set("short", "战场入口"); 
        set("long", @LONG 
四周越来越暗了，你胆颤心惊的象前摸索着，到处是一些
迷路人的尸体和骷髅。不时传来一阵阵鬼哭浪嚎,好象有什么
东西在暗中窥视着，你不由的加快了脚步。
LONG
); 
                        
        set("outdoors", "battle"); 
        set("virtual_room", 1); 
        set("no_magic",1);
        set("exits", ([ /* sizeof() == 3 */ 
                "east" : __DIR__"maze/exit",
        ])); 

        setup();
        replace_program(ROOM); 
} 
