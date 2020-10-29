inherit ROOM;

void create()
{
        set("short","长廊");
        set("long",@LONG
这是一条非常幽静的长廊。西边小路通往无无境，东边过去是寺
院深处的松林。
LONG);
     set("exits",([
        "west" : __DIR__"road3",
        "east" : __DIR__"songlin",
    ]));
    set("coor/x",-290);
  set("coor/y",-300);
   set("coor/z",40);
   setup();
}




