#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "血之禁忌" NOR, ({ "blood taboo", "blood", "taboo" }));
        set_weight(30);

        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("long", HIW "一瓶莹剔透血之禁忌，散射出绚目的光彩。\n"
                            "他可以用来直接解除(jiechu)你与魔幻兽之间签订的血之盟约。\n" NOR);
                set("value", 1);
                set("no_sell", 1);
                set("unit", "瓶");
        }
        set("auto_load", 1);
        setup();
}

void init()
{
        add_action("do_remove", ({ "jiechu", "remove" }));
}

int do_remove(string arg)
{
        object me;
        object warcraft;
        string filename;

        me = this_player();

        if( !query("warcraft", me) )
                return notify_fail("你没有和任何一只魔幻兽签订契约，无需解除血之盟约。\n");
        
        filename = "/data/warcraft/" + query("id", me);
        if (file_size(filename + ".c") > 0) 
        {
                if (warcraft = find_object(filename)) 
                {
                        tell_object(me, HIR "你与" + warcraft->name() + HIR "之间的血之盟约已经解除。\n" NOR);
                        destruct(warcraft); 
                }
                
                DBASE_D->clear_object(filename); 
                rm(filename + ".c"); 
        }
        
        delete("can_whistle", me); 
        delete("warcraft", me);
        me->save();
        
        destruct(this_object());
        return 1;
}
