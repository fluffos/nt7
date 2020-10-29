inherit ROOM; 

void create() 
{ 
        set("short", "弑神大殿"); 
        set("long", @LONG 
这里是30级BOSS挑战区。

LONG
); 
                        
        set("outdoors", "boss"); 
        set("no_magic",1);
        set("exits", ([ /* sizeof() == 3 */ 
                "out": "/d/city/wumiao",
        ])); 
        
        set("objects", ([
                __DIR__"npc/daozhang" : 1,
        ]));
        
        setup(); 
} 

