inherit ITEM;
#include <ansi.h>

#define CMD_JD   HIY + "jianding " + query("id") + HIC

void create()
{
        set_name(HIC "无名古玉" NOR, ({"wuming guyu", "wuming", "guyu"}));
        set_weight(2000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "块");
                set("long", HIC "这是一块不知名的古玉，看上去非常古老，不知产于哪一年代。\n" HIG
                                "需要通过鉴定，此玉的真面目才能显现，鉴定后可随机出现以下玉石之一：\n" HIB
                                "古玄玉（1级）、古玄玉（2级）、古玄玉（3级）\n" HIW
                                "玄冰石（1级）、玄冰石（2级）、玄冰石（3级）\n" HIR 
                                "鉴定前请确认你的背包中的负重至少剩余5% 。\n" HIC
                                "在扬州鲁班处，输入指令 " + CMD_JD + " 来请求鲁班鉴定无名古玉。\n" NOR);
                        
                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}

void init()
{
        add_action("do_jianding", "jianding");
}

int do_jianding(string arg)
{
        object me, env;
        object yu;        
        int ran_point;
        
        me = this_player();
        
        
        if (! arg || arg != query("id"))
                return notify_fail("你想鉴定什么？\n");
                
                        
        env = environment(me);
        
        if (base_name(env) != "/d/room/xiaoyuan")
                return notify_fail("这个物品好象只有鲁班才能鉴定，你还是上他那去吧。\n");
                
        message_vision(HIY "$N拿出" + name() + HIY "让鲁班鉴定。\n", me);
        
        
        // 开始鉴定
        /*40%几率鉴定出1级白玉或黑玉1块
          35%几率鉴定出2级白玉或黑玉1块
          25%几率鉴定出3级白玉或黑玉1块
        */
        ran_point = 1 + random(100);
        if (ran_point > 60)
        {
                if (random(2))
                {
                        yu = new("/clone/fam/enchase/guxuan-yu1");
                }
                else
                {
                        yu = new("/clone/fam/enchase/xuanbing-shi1");
                }
        }
        else if (ran_point > 0 && ran_point <= 35)
        {
                if (random(2))
                {
                        yu = new("/clone/fam/enchase/guxuan-yu2");
                }
                else
                {
                        yu = new("/clone/fam/enchase/xuanbing-shi2");
                }                
        }
        else
        {
                if (random(2))
                {
                        yu = new("/clone/fam/enchase/guxuan-yu3");
                }
                else
                {
                        yu = new("/clone/fam/enchase/xuanbing-shi3");
                }                
        }

        tell_object(me, HIG "鲁班将鉴定后的玉石交给你。\n" NOR);

        yu->move(me, 1);
        
        destruct(this_object());
        
        return 1;
}
