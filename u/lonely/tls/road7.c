//road7.c

inherit ROOM;

void create()
{
        set("short", "石板路");
        set("long", @LONG
    你走在一条长长的石板路上，道旁古树参天，鸟鸣不绝，前面是
一片大松林，这条路一直通向松林深处，林子里黑黑漆漆的，你不由的默
念“阿弥陀佛”。
LONG    );
        set("exits", ([ /* sizeof() == 2 */
   "north" : __DIR__"songlin-1",
  "south" : __DIR__"yuhua1",

   
]));
        set("no_clean_up", 0);
        set("outdoors", "天龙寺");

        setup();
}
