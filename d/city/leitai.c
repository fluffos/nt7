// Room: /city/leitai.c
// Date: Feb.27 1998 by Java
// Update by Doing
// Modified by Haiyan

#include <ansi.h>

inherit ROOM;
string look_tiaofu();

void create()
{
        set("short", "擂台");
        set("long", @LONG
这是一个四丈见方的擂台。粗壮结实的木柱撑起一片平台，四角
的支柱上高挂着四副对联，四面的观众都能清楚地看到台上的手起脚
落。梁上贴着一长条幅(tiaofu)，上面写了一些东西。
LONG );
        set("outdoors", "city");
        set("item_desc", ([
                "tiaofu" : (: look_tiaofu :),
        ]));

        set("exits", ([
                "down" : "/d/city/wudao1",
        ]));
        set("objects", ([
                "/adm/npc/referee": 1,
        ]));
	set("coor/x", 1);
	set("coor/y", -9);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_lclose", "lclose");
        add_action("do_lopen", "lopen");
        add_action("do_invite", "invite");
        add_action("do_jiangli", "jiangli");
}

string look_tiaofu()
{
        object ob;

        ob = query("close_by");
        if (! objectp(ob))
                return "本擂台现在自由开放，如有兴趣自行比"
                       "武，失手伤人致命，概不负责。\n\n"
                       "注：巫师请用" HIY "lopen" NOR "/"
                       HIY "lclose" NOR "命令开放关闭擂台。\n";

        return "本擂台现在被" + ob->name(1) + "暂时关闭，"
               "组织比武，闲杂人等勿要喧哗。\n"
               "巫师请用" HIY "invite" NOR "命令邀请他人上台，"
               "或在台下使用" HIY "pass" NOR "命令\n"
               "指定某人上台比武，用" HIY "kickout" NOR
               "踢某人下台。\n";
}

int refuse(object ob)
{
        return 1;
        if (! wizardp(ob) && query("close_by"))
                return 1;

        return 0;
}

int do_lclose(string arg)
{
        object me,ob;

        me = this_player();
        if (wiz_level(me) < 3)
                return notify_fail("你没有资格关闭擂台。\n");

        if (arg != "here")
                return notify_fail("如果你要关闭擂台，请输入(lclose here)。\n");

        if (objectp(query("close_by")))
                return notify_fail("这个擂台已经被" +
                                   query("close_by")->name(1) +
                                   "关闭用于比武了。\n");

        set("close_by", me);
        message("vision", HIW "【武林盛会】" + me->name(1) +
                "关闭了擂台，开始举行比武盛会。\n" NOR,
                all_interactive());

        foreach (ob in all_inventory(this_object())) 
        {
                if (userp(ob) && !wizardp(ob))
                {
                        ob->move("/d/city/wudao1");
                        if (living(ob))
                                tell_object(ob,"公平子对你说：擂台给关闭了，您先请下台等待吧！\n");
                }
        }

        set("biwu_room",1);
        return 1;
}

int do_lopen(string arg)
{
        object me;

        me = this_player();
        if (wiz_level(me) < 3)
                return notify_fail("你没有资格打开擂台。\n");

        if (! objectp(query("close_by")))
                return notify_fail("这个擂台目前并没有被关闭。\n");

        if (query("close_by")->name(1) != me->name())
                return notify_fail("只能由主持比武大会的巫师才能打开擂台。\n");

        if (arg != "here")
                return notify_fail("如果你要打开擂台，请输入(lopen here)。\n");

        delete("close_by");
        message("vision", HIW "【武林盛会】" + me->name(1) +
                "结束了比武，重新开放了擂台。\n" NOR, all_interactive());

        delete("biwu_room");
        return 1;
}

object *broadcast_to()
{
        if (! objectp(query("close_by")))
                return 0;

        return ({ find_object("/d/city/wudao1"),
                  find_object("/d/city/wudao2"),
                  find_object("/d/city/wudao3"),
                  find_object("/d/city/wudao4"), });
}

int do_invite(string arg)
{
        int i;
        object *inv;
        object me;
        object ob;

        me = this_player();
        if (! wizardp(me))
                return notify_fail("你不是巫师，没有资格邀请人家上来。\n");

        if (! query("close_by"))
                return notify_fail("现在擂台并没有关闭，无需特地邀请别人。\n");

        if (query("close_by")->name(1) != me->name())
                return notify_fail("只能由主持比武大会的巫师才能邀请选手上台。\n");

        if (! arg ||
            ! objectp(ob = find_player(arg)))
                return notify_fail("你想让谁上来？\n");

        if (environment(ob) == this_object())
                return notify_fail("嗯？现在不是已经在这里了么？\n");

        if (wizardp(ob))
                return notify_fail("人家自己想上来自己会上来，不劳你费心。\n");

        if (! living(ob))
                return notify_fail("好歹你得弄醒人家吧？\n");

        if (mapp(ob->query_condition()))
                return notify_fail("对不起，对方的身体状况不好，不能上台！\n");

        if( query("eff_qi", ob)<query("max_qi", ob) )
               return notify_fail("对不起，对方的气血受伤了，不能上台！\n");

        if( query("eff_jing", ob)<query("max_jing", ob) )
               return notify_fail("对不起，对方的精气受伤了，不能上台！\n");

        inv = deep_inventory(ob);
        for (i = 0; i < sizeof(inv); i++)
        {
                if (! userp(inv[i])) continue;
                return notify_fail("对方身上背着个大活人呢，不能上台！\n");
        }

        message("vision", HIW + me->name() + "一声长啸：" + ob->name() +
                          "，你还不快快上来？\n" NOR, all_interactive());
        message_vision("只见$N急急忙忙的走了开去。\n", ob);
        message("vision", "只见一声呼哨，" + ob->name() + "应声跃上台来，矫健之极。\n",
                this_object());

        ob->move(this_object());
        tell_object(ob, HIY "你一阵目眩，定神一看，这才发现自己已经到了" +
                    environment(ob)->short() + HIY "。\n");
        return 1;
}

int do_jiangli(string arg)
{
        object me = this_player();
        object ob, obv;
        string player, msg;
        string *par;
        int *mc;
        mapping winner;
        int place, gift;

        if (wiz_level(me) < 3)
                return notify_fail("你没有资格给别人奖励。\n");

        if (! objectp(query("close_by")))
                return notify_fail("现在擂台并没有用于召开比武大会，你" +
                                   "不能给别人奖励。\n");

        if (query("close_by")->name(1) != me->name())
                return notify_fail("你并不是主持比武大会的巫师，" +
                                   "不能给别人奖励。\n");

        if (! arg || sscanf(arg, "%s %d %d", player, place, gift) != 3)
        {
                msg = "指令格式：jiangli <ID> <名次> <奖品>。\n\n";
                msg += "Example: jiangli haiyan 2 5\n\n";
                msg += "奖品代号如下：\n";
                msg += "0 - 玄黄紫清丹\n";
                msg += "1 - 九转金丹\n";
                msg += "2 - 天香玉露\n";
                msg += "3 - 菩提子\n";
                msg += "4 - 仙丹\n";
                msg += "5 - 洗髓丹\n";
                msg += "6 - 神力丸\n";
                msg += "7 - 火红仙丹\n";
                msg += "8 - 补天石\n";
                msg += "9 - 冰蚕丝\n\n";
                me->start_more(msg);
                return 1;
        }

        if ( place < 1 || place > 5)
                return notify_fail("你只能奖励前五名。\n");

        if (! objectp(ob = present(player, this_object())))
                return notify_fail("你要奖励谁？\n");

        if( !query("winner", me))winner=([]);
        else
        {
                winner=query("winner", me);
                mc = keys(winner);
                par = values(winner);

                if (member_array(place, mc) != -1)
                       return notify_fail("第" + chinese_number(place) +
                                          "名已经产生了。\n");

                if (member_array(player, par) != -1)
                       return notify_fail(player + "已经取得名次了。\n");
        }

        switch(gift)
        {
             case 0:
                obv = new("/clone/gift/xuanhuang");
                break;
             case 1:
                obv = new("/clone/gift/jiuzhuan");
                break;
             case 2:
                obv = new("/clone/misc/tianxiang");
                break;
             case 3:
                obv = new("/d/shaolin/obj/puti-zi");
                break;
             case 4:
                obv = new("/clone/gift/xiandan");
                break;
             case 5:
                obv = new("/clone/gift/xisuidan");
                break;
             case 6:
                obv = new("/clone/gift/shenliwan");
                break;
             case 7:
                obv = new("/clone/gift/unknowdan");
                break;
             case 8:
                obv = new("/d/item/obj/butian");
                break;
             case 9:
                obv = new("/d/item/obj/tiancs");
                break;
        }

        message("vision",HIW"【武林盛会】恭喜"+query("name", ob)+"("+
                query("id", ob)+")获得本届比武大会第"+
                chinese_number(place) + "名。\n" NOR,
                all_interactive());
        message_vision("$N在怀里掏了半天，摸出一"+query("unit", obv)+
                       obv->name() + "交给了$n！\n", me, ob);

        winner+=([place:query("id", ob)]);
        set("winner", winner, me);
        obv->move(ob);
        return 1;
}