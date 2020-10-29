inherit ROOM;

string show_bei();
string show_aoxian();

// 72小时只能挑战一次
#define TIME_LIMIT 2

#include <ansi.h>

void create()
{
        set("short", HIR "火焰洞" NOR);
        set("long",@LONG
一进入此处幽深之气息突然被一阵无比炽热的气息掩盖，只见四
周岩壁使劲地泛着红光，似乎是经历几千几万年的炽烤。洞内深邃无
比，前方黑乎乎的一片，只有借助着岩石泛出的火光才能看清楚四周
景致。不远处，有一块碑石（bei）， 远看上上面刻着一些文字。据
说，这里隐藏着一只已经修炼成人形的远古火焰巨兽。
LONG);


        set("exits", ([
                "out"  : __DIR__"dong3.16",
        ]));

        set("item_desc", ([
                "bei"  : (: show_bei :),
                "aoxian":(: show_aoxian :),
        ]));

        set("no_rideto",1);
        set("no_flyto", 1);
        set("no_clean_up", 1);
        setup();

}

string show_bei()
{
        object ob;

        ob = find_living("huo qilin");
        if (objectp(ob) && environment(ob) == this_object())
        {
                return HIG "这是一块隐藏着机关的碑石，碑石中央凹陷的部分被斩妖勋章填满，正闪闪发光！\n" NOR;
        }
        return NOR + WHT "上面刻着一些奇特的符号，从未见过，不过在碑石中央有一块地方已经凹"
                         "陷(aoxian)下去，似乎是一个机关\n" NOR;
}

string show_aoxian()
{
        object ob;

        ob = find_living("huo qilin");
        if (objectp(ob) && environment(ob) == this_object())
        {
                return HIG "碑石中央凹陷的部分被斩妖勋章填满，正闪闪发光！\n" NOR;
        }

        if( query("no_putin", this_object()) )
                return HIG "碑石中央凹陷的部分被斩妖勋章填满，正闪闪发光！\n" NOR;

        return HIY "你仔细观察这凹陷下去的一块，似乎可以放(putin)入一块物品来打开其中的机关。\n" NOR;
}

// 检查今天是否已经参加过麒麟战
void init()
{
        object me = this_player();

        add_action("do_putin", "putin");

        // TIME_LIMIT小时只能参加一次，测试期间例外，为2小时
        if (time() - query("boss/qilin", me) <  TIME_LIMIT * 3600 && userp(me) && ! wizardp(me))
        {
                tell_object(me, HIG "\n对不起，你参加火麒麟对抗战间隔时不足" +
                                sprintf("%d", TIME_LIMIT) + "小时。\n");
                tell_object(me, HIC "你距离上次参加火麒麟对抗战间隔： " + HIY +
                  sprintf("%d",(time()-query("boss/qilin", me))/3600)+HIC"小时。\n\n"NOR);
                me->move(__DIR__"dong3.16");
                return;
        }

        // 设置参加时间
        tell_object(me, HIG "\n你进入火焰洞准备参加对抗火麒麟战斗，请不要离开，否则" +
                        sprintf("%d", TIME_LIMIT) + "小时内无法再次进入。\n" NOR);
        tell_object(me, HIR "你已经设置为免死状态，在火焰洞死亡后可自动在武庙复活，不损失任何物品和技能。\n\n" NOR);
        set("boss/qilin", time(), me);

        // 不需要设置，房间自动免死

        me->save();

        return;
}

// 放入斩妖勋章
int do_putin(string arg)
{
        object ob, env;
        object ob_qilin;

        object me = this_player();

        if (! arg)return notify_fail("你打算放入什么物品到石碑中凹陷部分？\n");

        ob_qilin = find_living("huo qilin");
        if (objectp(ob_qilin))
        {
                if (environment(ob_qilin) == this_object() )
                        return notify_fail(HIG "石碑中的斩妖勋章正闪闪发光，透射出神秘而诡异的气息！\n" NOR);
        }
        // 正在清场则不能扔
        env = environment(me);
        if( query("doing", env) )
        {
                return notify_fail("目前正在清场，请稍后再试！\n");
        }

        if( query("no_putin", env) )
                return notify_fail("你目前暂时无法完成此操作，请稍后再试。\n");

        if (objectp(ob = present(arg, me)))
        {

                // 判断是否为斩妖勋章
                if (base_name(ob) != "/clone/armor/zhanyao-xunzhang")
                        return notify_fail("你准备拿出" + ob->name() + NOR "放入石碑，却发现怎么也放不上去。\n");

                /*
                // 测试期间用麒麟钥匙打开，扬州客店有销售，1COIN一把
                if (base_name(ob) != "/d/shenlong/obj/qilin_key")
                        return notify_fail("你准备拿出" + ob->name() + NOR "放入石碑，却发现怎么也放不上去。\n");
                */
                message_vision(HIR "\n喀嚓~一声，$N将" + ob->name() + HIR "放入石碑中的凹陷部分，瞬间" + ob->name() +
                             HIR "与石碑合为一体，并散发出诡异的光芒 ……\n" NOR, me);

                destruct(ob);

                set("no_putin", 1, env);
                remove_call_out("clear_no_putin");
                call_out("clear_no_putin", 10, env);

                // 进行延迟出现
                remove_call_out("qilin_coming");
                call_out("qilin_coming", 5, me);

                return 1;
        }

        return notify_fail("你身上没有这样物品。\n");
}

void qilin_coming(object me)
{
        object ob_qilin, ob;

        ob = find_living("huo qilin");

        if (objectp(ob) && environment(ob))
        {
                if (base_name(environment(ob)) == __FILE__)
                        return ;
        }

        // 正在清场则返回
        ob = environment(me);
        if( query("doing", ob))return ;

        message_vision(HIY "\n猛然间，石碑剧烈的颤动，整个山洞也开始晃动，伴随着一阵巨响，一团火焰从山"
                       "洞深处窜出 ……\n" NOR, me);

        ob_qilin = new(__DIR__"npc/qilin");

        set("life_time", time(), ob_qilin);
        ob_qilin->move(__FILE__);

        delete("no_putin", ob);

        return;
}

void clear_no_putin(object env)
{
        delete("no_putin", env);
        return;
}

void start_move()
{
        object *ob;
        int i;
        object ob_out;

        ob = all_inventory(this_object());

        // 清出清场标志
        delete("doing");

        if (! sizeof(ob))return;

        if (! objectp(ob_out = find_object(__DIR__"dong3.16")))
                ob_out = load_object(__DIR__"dong3.16");

        for (i = 0; i < sizeof(ob); i++)
        {
                if (! ob[i]->is_character())
                {
                        destruct(ob[i]);
                        continue;
                }

                if( query("id", ob[i]) == "huoqilin" )
                        continue;

                ob[i]->move(ob_out);
        }

        return;
}

// 来自BOSS的呼叫，当麒麟死亡后延迟将所有房间内的ID
// 移动到火焰洞外，如delay_time = 0 则不延迟
void move_all_player_out(int delay_time)
{
        if (! delay_time)
        {
                start_move();
        }
        else
        {
                remove_call_out("start_move");
                call_out("start_move", delay_time);
        }

        return;

}
