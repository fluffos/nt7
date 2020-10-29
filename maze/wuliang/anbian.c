#include <room.h>
#include <ansi.h>
inherit ROOM;
#define QUESTDIR1 "quest/天龙八部/凌波微步篇/"
void create()
{
         set("short", HIC"澜沧江边"NOR);
         set("long",@LONG
你沿着山坡走到澜沧江边，朝阳初升，照得碧玉般的江面上犹如镶了一层
黄金一般，壮丽无比，你站在这里，心中什么也不愿意想，只希望就这样天长
地久，时间永恒。
LONG
 );

        set("exits",([
             "eastup" : __DIR__"gaoshan",
]));
        
	set("outdoors", "大理");
	setup();
}

void init()
{
	object me = this_player();
      
	if( query_temp(QUESTDIR1+"yingjiu", me) && query(QUESTDIR1+"pass_shanlu", me)){
set_temp("wait", 1, 		me);
		tell_object(me,HIC"\n你悄立江边，思涌如潮，心中思绪万千。\n"NOR);
		call_out("do_wait", 20 + random(10), me);
	}
	add_action("do_jump", "jump");
	add_action("do_look", "look");
}

void do_wait(object me)
{

if(!me) return;
	if( environment(me) && query_temp("wait", me)){
		tell_object(me,HIY"\n你悄立江边，思涌如潮，心中思绪万千。突然眼角瞥处，见数十丈外一块大岩石（yan)上似乎有些古怪。\n"NOR);
		me->delele_temp("wait");
set_temp("yan1", 1, 		me);
	}
}

int do_look(string arg)
{
	object me = this_player();

	if( !query_temp("yan1", me)){
		set("long", @LONG
你沿着山坡走到澜沧江边，朝阳初升，照得碧玉般的江面上犹如镶了一层
黄金一般，壮丽无比，你站在这里，心中什么也不愿意想，只希望就这样天长
地久，时间永恒。
LONG
);
		me->look(arg);
	}
	else {
		if (!arg) {
			set("long", @LONG
你沿着山坡走到澜沧江边，朝阳初升，照得碧玉般的江面上犹如镶了一层
黄金一般，壮丽无比，你站在这里，心中什么也不愿意想，只希望就这样天长
地久，时间永恒。你悄立江边，思涌如潮，心中思绪万千。突然眼角瞥处，见
数十丈外一块大岩石（yan)上似乎有些古怪。
LONG
);
			me->look(arg);
		}
		else if (arg == "rock" || arg == "yanshi" || arg == "yan") {
			tell_object(me,HIR"一块巨岩，不知道可不可以跳上去？\n"NOR);
set_temp("yan2", 1, 			me);
			return 1;
		}
       }		
}

int do_jump(string arg)
{
	object me;
	me = this_player();

	if( arg != "yan" || !query_temp("yan2", me) )
		return notify_fail("你要跳到那去？\n");

	if (me->query_skill("dodge",1) < 80)
		tell_object(me,WHT"你打量了下岩石和你之间的距离，似乎太远了，只好做罢。\n"NOR);
	else {
		tell_object(me,HIR"你一提气，纵身跳到了岩石上。\n"NOR);
		message("vision", me->name() + "一纵身跳到了几十丈远的大岩石上。\n", environment(me), ({me}) );
delete_temp("wait", 		me);
delete_temp("yan1", 		me);
delete_temp("yan2", 		me);
		me->move(__DIR__"yan");
		message("vision", me->name() + "从下面跃了上来。\n", environment(me), ({me}) );
	}
	return 1;
}

int valid_leave(object me,string dir)
{
	if( query_temp("wait", me) )
delete_temp("wait", 		me);
delete_temp("yan1", 	me);
delete_temp("yan2", 	me);
        return ::valid_leave(me,dir);
}