// 上古十大神器之 神农鼎
// Create by Rcwiz for Hero.cn 2003/09

#include <ansi.h>

inherit ITEM;

int is_magic_item() { return 1; }

// 炼制的丹药
string *gifts = ({
        "/clone/fam/pill/neili1",
        "/clone/fam/pill/neili2",
        "/clone/fam/pill/linghui1",
        "/clone/fam/pill/linghui2",
        "/clone/fam/pill/lingzhi4",
        "/clone/fam/pill/lingzhi3",
        "/clone/fam/pill/puti1",
        "/clone/fam/pill/puti2",
        "/clone/fam/pill/puti3",
        "/clone/fam/pill/puti4",
        "/clone/fam/pill/renshen3",
        "/clone/fam/pill/renshen4",
        "/clone/fam/pill/sheli1",
        "/clone/fam/pill/sheli2",
        "/clone/fam/pill/sheli3",
        "/clone/fam/pill/sheli4",
        "/clone/fam/pill/xuelian3",
        "/clone/fam/pill/xuelian4",        
        "/clone/fam/gift/int3",
        "/clone/fam/gift/con3",
        "/clone/fam/gift/str3",                        
        "/clone/fam/gift/dex3",
        "/clone/fam/pill/neili1",
        "/clone/fam/pill/neili2",
        "/clone/fam/pill/linghui1",
        "/clone/fam/pill/linghui2",
        "/clone/fam/pill/lingzhi4",
        "/clone/fam/pill/lingzhi3",
        "/clone/fam/pill/puti1",
        "/clone/fam/pill/puti2",
        "/clone/fam/pill/puti3",
        "/clone/fam/pill/puti4",
        "/clone/fam/pill/renshen3",
        "/clone/fam/pill/renshen4",
        "/clone/fam/pill/sheli1",
        "/clone/fam/pill/sheli2",
        "/clone/fam/pill/sheli3",
        "/clone/fam/pill/sheli4",
        "/clone/fam/pill/xuelian3",
        "/clone/fam/pill/xuelian4",        
        "/clone/fam/gift/int4",
        "/clone/fam/gift/con4",
        "/clone/fam/gift/str4",
        "/clone/fam/gift/dex4",                                                
        "/clone/fam/max/naobaijin",
        "/clone/fam/pill/neili1",
        "/clone/fam/pill/neili2",
        "/clone/fam/pill/linghui1",
        "/clone/fam/pill/linghui2",
        "/clone/fam/pill/lingzhi4",
        "/clone/fam/pill/lingzhi3",
        "/clone/fam/pill/puti1",
        "/clone/fam/pill/puti2",
        "/clone/fam/pill/puti3",
        "/clone/fam/pill/puti4",
        "/clone/fam/pill/renshen3",
        "/clone/fam/pill/renshen4",
        "/clone/fam/pill/sheli1",
        "/clone/fam/pill/sheli2",
        "/clone/fam/pill/sheli3",
        "/clone/fam/pill/sheli4",
        "/clone/fam/pill/xuelian3",
        "/clone/fam/pill/xuelian4",
        "/clone/fam/pill/yulu",
        "/clone/fam/pill/neili1",
        "/clone/fam/pill/neili2",
        "/clone/fam/pill/linghui1",
        "/clone/fam/pill/linghui2",
        "/clone/fam/pill/lingzhi4",
        "/clone/fam/pill/lingzhi3",
        "/clone/fam/pill/puti1",
        "/clone/fam/pill/puti2",
        "/clone/fam/pill/puti3",
        "/clone/fam/pill/puti4",
        "/clone/fam/pill/renshen3",
        "/clone/fam/pill/renshen4",
        "/clone/fam/pill/sheli1",
        "/clone/fam/pill/sheli2",
        "/clone/fam/pill/sheli3",
        "/clone/fam/pill/sheli4",
        "/clone/fam/pill/xuelian3",
        "/clone/fam/pill/xuelian4",        
});

void create()
{
        set_name(HIG "神农鼎" NOR, ({ "shennong ding", "shennong", "ding" }) );
        set_weight(400);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "个");
                set("long", HIG "这是一个具有神奇作用的鼎，据说上古神农尝百草炼奇药，所用"
                                "之炼制器具就是这个神农鼎。\n"
                                "你可以用它来炼制(lianzhi)出神奇的丹药，使用liandan ? "
                                "查看可使用次数。\n炼制丹药需要炼丹术一百级。\n" NOR);
        }

        setup();
}

void init()
{
        add_action("do_lianzhi", "lianzhi");
}

int do_lianzhi(string arg)
{
        object me, ob;
        int i;
        string gift;

        me = this_player();
        
        if(! objectp(present("shennong ding", me)))return 0;

        if (arg == "?")
        {
                 write(HIG "使用次数 " + this_object()->query("count") + "/5\n" NOR);
                 return 1;
        }
        if (me->is_fighting() || me->is_busy())
                 return notify_fail("你正忙呢！\n");          

        message_sort(HIG "\n$N" HIG "将神农鼎放在地上，随手仍进去一些药材，渐渐地，鼎中阵"
                         "阵青烟冒出，光华万道 ……\n" NOR, me);

        gift = gifts[random(sizeof(gifts))];
        ob = new(gift);
        if (! objectp(ob))
        {
                write(HIR "物件 " + gift + " 复制出错！\n" NOR);
        }
        else
        {
                write(HIG "你炼制出了 " + ob->name() + HIG + " 。\n" NOR);
                ob->move(me, 1);
        }
             
        me->start_busy(2);
        this_object()->add("count", 1);
        if (this_object()->query("count") >= 5)
        {
                write(HIW "只听得一阵破碎的声音，神农鼎已损坏了。\n" NOR);
                destruct(this_object());                        
        }
        
        return 1;
}
