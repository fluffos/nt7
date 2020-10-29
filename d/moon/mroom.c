// ken 1999.12.9

#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
	set("short", "密室");
	set("long", @LONG
一间小小的密室，一尘不染，看来经常有人来打扫，
可是现在这里除了一个书柜以外，别的什么都没有。
LONG	);
        set("objects",([
			__DIR__"obj/bookcase" : 1,
                        __DIR__"npc/xiao" : 1,
       	]) );
        set("exits/south", __DIR__"nroom");
	set("coor/x",-50);
	set("coor/y",1120);
	set("coor/z",40);
        setup();
}

void reset()
{
   object *inv;
   object item1,bookcase;
   ::reset();

   bookcase = present("bookcase", this_object());
   inv = all_inventory(bookcase);
   if( !sizeof(inv)) {
      item1 = new(__DIR__"obj/book");
      item1->move(bookcase);
   }
}
