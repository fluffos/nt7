// ken 1999.12.9

#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
	set("short", "山庄前院");
	set("long", @LONG
走到这里，你的视野豁然开朗，刚才的压抑一扫而光。此处建筑黄金
为顶，白玉为阶，远见层层叠叠的琉璃瓦在夕阳的余辉下熠熠生光，
近处几只仙鹤在松柏掩映的草地上悠闲地漫步，望之有如神仙境界。
LONG	);
	set("exits", ([ 
  "north" : __DIR__"gaden",
  "westdown" : __DIR__"cookroom",
  "eastdown" : __DIR__"lianroom",
  "southeast" : __DIR__ "bi", 
]));
        set("objects",([
			__DIR__"npc/guards" : 2,
       	]) );
	set("coor/x",-30);
	set("coor/y",1090);
	set("coor/z",40);
	setup();
}
void init()
{	
	add_action("do_around","around");
}

int do_around(string arg)
{       
        object room;
        object me;
        if(!arg || arg=="")
        {
                write("你要转过什么？\n");
                return 1;
        }
        if( arg == "jiashan" || arg == "假山" )
        {
        me = this_player();
        room = find_object("/n/moon/bi");
        if(!objectp(room)) room=load_object("/u/moon/bi");
        message_vision("\n$N信步浏览，转眼走过了假山。\n\n",me); 
        me->move(room); 
        return 1;
        }
        else
         write("你要转过什么？\n");
                return 1;
}
