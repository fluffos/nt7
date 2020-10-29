#include <ansi.h>
inherit ITEM;
void create()
{
    set_name(YEL "夜辰日记" NOR, ({ "night's diary","diary" }) );
    set_weight(1);
    /*if( clonep() )
            set_default_object(__FILE__);
    else*/ {
            set("unit", "本");
            set("material", "paper");
            set("long", "一本巫师夜辰以前的日记，你可以读一读（ｒｅａｄ），说不定会有什么发现。\n");
          }

    setup();
}
void init()
{
        if(environment(this_object())==this_player())
        add_action("do_read","read");
        add_action("do_go","go");
}

int do_read(string arg)
{
object me;
mapping exits;
string *dirs;
string thisdir;
if(arg != "night's diary" && arg != "diary") return 0;
me=this_player();
if(find_call_out("markit")== -1)
call_out("markit",random(60)+20,me);
if( !mapp(exits=query("exits", environment(me))) )
{
tell_object(me,"有一批宝藏就在附近！\n");
return 1;
}
        dirs = keys(exits);
        thisdir = dirs[random(sizeof(dirs))];
        if(!sizeof(thisdir)) return 1;
        set("thisdir",thisdir);
        tell_object(me,"有一批宝藏就在"+thisdir+"的方向！\n");
        return 1;
}

int do_go(string arg)
{
        if(arg==query("thisdir"))
        addn_temp("going", 1, this_player());
        return 0;
}
int markit(object me)
{
object gold;
if( query_temp("going", me) <= 20 || environment() != me)return 1;
if(!query("already"))
{
gold = new("/clone/money/gold");
tell_object(me,"\n\n你弯腰仔细查找，从『夜辰日记』所指示的地方挖出些金子！\n");
gold->set_amount(50);
gold->move(me);
delete_temp("going", me);
set("already",1);
        message_vision("\n$N化为轻烟，渐渐散去了。\n", this_object());
        destruct(this_object());
}
return 1;
}