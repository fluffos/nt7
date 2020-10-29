
inherit ROOM; 

void create() 
{ 
        set("short", "大殿"); 
        set("long", @LONG 
这里是BOSS挑战区。

LONG
); 
                        
        set("outdoors", "boss"); 
        set("maze",1);
        set("exits", ([ /* sizeof() == 3 */ 
                "out": "/d/city/wumiao",
        ])); 
        
        setup(); 
} 


