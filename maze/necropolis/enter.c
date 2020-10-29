inherit ROOM; 

void create() 
{ 
        set("short", "墓园入口"); 
        set("long", @LONG 
墓园里没有一点生气，地上到处是枯枝败叶，偶尔看到一些
干枯的动物尸骸，让人不寒而栗，到处散发着一股尸首腐烂的
味道，看不到一丝活物存在。
LONG
); 
                        
        set("outdoors", "necropolis"); 
        set("virtual_room", 1);
        set("no_death_penalty", 1);
        set("no_magic", 1);
        set("exits", ([ /* sizeof() == 3 */ 
                "south" : __DIR__"maze/entry", 
        ])); 
        set("objects",([
                "/maze/necropolis/obj/coffin1": 1,  
        ])); 
        setup();
 
} 