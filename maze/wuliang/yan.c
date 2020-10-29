//cool 98.7.17
// Modify By River 98/12
inherit ROOM;

void create()
{
	set("short", "大岩石");
	set("long", @LONG
你跳上了一块大岩石，岩石上落脚的地方并不大，你看见岩石上坐着有人，
只是这人始终一动不动，身上又穿着青袍，与青岩同色。
LONG
	);
        set("outdoors", "大理");
        set("objects", ([
	    __DIR__"npc/dyq": 1,
	]));
	setup();
}

void init()
{
      add_action("do_jump","tiao");
      add_action("do_jump","jump");
}

int do_jump(string arg)
{
      object me;
      me = this_player();
      if (arg !="down") 
        return notify_fail("你要到那去？\n");
      if( arg=="down"){
        write("你纵身跳下了岩石。\n");
        message("vision",me->name() + "一纵身跳下了岩石。\n",environment(me), ({me}) );
        me->move(__DIR__"anbian");
        message("vision",me->name() + "走了过来。\n",environment(me), ({me}) );
        }
       return 1;
}