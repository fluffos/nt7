#include <ansi.h>
inherit ITEM; 

void create()
{
	      set_name(HIC"旗子"NOR, ({"fwar flag","flag"}) );
        set_weight(300);
        set("unit", "面");
        set("long", "一面大旗上描绘着不知名的图腾，看来你似乎可以将它检起。\n");
        set("value", 1);
        set("no_store",1);
        set("no_sell", 1);
        set("flag_war_item", 1);
        set("no_get", 1);
        setup();
}
void init()
{
	add_action("do_get","get");
	add_action("do_drop","drop");
}
int do_get(string arg) {
	object ob, me = this_player();
	if(!me) return 0;
	if(arg == "all" || !arg || !ob = present(arg, environment(me))) return 0;
	if(ob != this_object()) return 0;
	if(present("fwar flag", me)) return notify_fail("你身上已经有一只旗子了，先去插好再来吧。\n");
	if(ob->move(me)) {
		me->start_busy(2);
		FWAR_D->get_flag(me, ob);
	}
  return 1;
}
int do_drop(string arg) {
	object ob, me = this_player();
	if(!me) return 0;
	if(arg == "all" || !arg || !ob = present(arg, me)) return 0;
	if(ob != this_object()) return 0;
	if(ob->move(environment(me))) {
		FWAR_D->drop_flag(me, ob);
	}
  return 1;
}

int do_stab(object me)
{
	object room;
	if(!room = environment(me)) return 0;
	if(!room->query("stab_flag")) return notify_fail(name()+"只能插在起点。\n");
	if(room->query("party") != me->query_temp("flag_war/party")) return notify_fail(name()+"只能插在你自己的队伍起点。\n");
	FWAR_D->stab_flag(me, this_object());
	return 1;
}