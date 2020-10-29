inherit ROOM;

void create()
{
  set("short","长廊");
  set("long",@LONG
这里松树林里一条非常幽静的长廊，往西直通无无境等地。长廊
尽头处有一简屋，材料天然，与这茂密的松树林混为一体。
LONG);

   set("exits",([
      "west" : __DIR__"songlin",
      "north" : __DIR__"songlin1",
      "enter" : __DIR__"monitang",
      "south" : __DIR__"songlin2",
     ]));
 set("coor/x",-270);
  set("coor/y",-300);
   set("coor/z",40);
   setup();
}




