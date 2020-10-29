inherit ROOM;
 
void create()
{
        set("short", "小路");
        set("long", @LONG
这是一条通往后山的小径。小路两旁长满了杂草。由于人们很少走这
条路，甚至连路中央也稀稀疏疏冒出了草芽。东边有一个小山洞。
LONG );
        set("exits", ([
                "east"   : __DIR__"road4",
                "south"  : __DIR__"road2",
        ]));
        set("objects", ([
                "/clone/beast/dushe": 4,
        ]) );
        
        set("outdoors", "taohua");
       
        set("coor/x", 8980);
        set("coor/y", -2930);
        set("coor/z", 0);
        setup();
}