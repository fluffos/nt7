// letter.c
// 师傅手谕

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name("师门信件", ({ "letter", "quest letter" }));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "张");
                set("long", "这是一封师傅送来的亲笔信。\n");
                set("value", 0);
        }
        setup();
}

void init()
{
        // 接受
        add_action("do_accept", "accept");

        // 拒绝
        add_action("do_refuse", "refuse");
}

// 查看时显示任务提示
string long()
{
        string msg;
        mapping quest;
        object me;

        msg = query("long");
        if (! mapp(quest = query("quest")))
                return msg;

        me = this_player();
        if( query("id", me) != query("quester") )
                return msg;

        // call_out 不一定很准时，所以这里要防止出现
        // “负一秒”这样的情况
        if (time() > query("dest_time"))
                return msg;

        msg += "上面写着：\n";

        // 为其他类型的任务提供扩展余地
        switch (quest["type"])
        {
        case "kill" :
                // 寻找 master 太过麻烦，所以这里就根据本人的善恶
                // 判断消息
                msg += "\n“字谕弟子" + me->name() + "：";
                if (me->is_good())
                {
                        msg += ("得闻恶贼" HIR + quest["name"] + "(" + quest["id"] + ")" + NOR
                                "打家劫舍，无恶不作。近日他在" HIR +
                                quest["place"] + NOR "出没，正是大好"
                                "机会将他除去，你若愿意，便代我出手"
                                "无妨，但务必须在" HIR +
                                CHINESE_D->chinese_monthday(quest["limit"]) +
                                NOR "之前完成。否则回山复命即可。" +
                                quest["master_name"] + "于" +
                                CHINESE_D->chinese_monthday(quest["time"]) +
                                "。”\n");
                } else
                if (me->is_bad())
                {
                        msg += ("得闻所谓大侠" HIR + quest["name"] + "(" + quest["id"] + ")" + NOR
                                "屡次和我派作对，近日他在" HIR +
                                quest["place"] + NOR "出没，正是大好"
                                "机会将他除去，你若愿意，便代我出手"
                                "无妨，但务必须在" HIR +
                                CHINESE_D->chinese_monthday(quest["limit"]) +
                                NOR "之前完成。否则回山复命即可。" +
                                quest["master_name"] + "于" +
                                CHINESE_D->chinese_monthday(quest["time"]) +
                                "。”\n");
                } else {
                        msg += ("武林人士" HIR + quest["name"] + "(" + quest["id"] + ")" + NOR
                                "所为甚是讨厌，得闻近日他在" HIR +
                                quest["place"] + NOR "出没，正是大好"
                                "机会将他除去，你若愿意，便代我出手"
                                "无妨，但务必须在" HIR +
                                CHINESE_D->chinese_monthday(quest["limit"]) +
                                NOR "之前完成。否则回山复命即可。" +
                                quest["master_name"] + "于" +
                                CHINESE_D->chinese_monthday(quest["time"]) +
                                "。”\n");
                }
                break;
        }
        // 想立即拒绝的话就输入 refuse，否则等 30 秒也没关系
        msg += HIC "\n如果你愿意接受此任务，请在" HIW +
               chinese_number(query("dest_time") - time()) +
               HIC "秒之内输入" HIW "(accept quest)"
               HIC "以确认，否则即为拒绝"
               HIW "(refuse quest)" HIC "。\n" NOR;
        msg = sort_msg(msg);
        return msg;
}

private void eval_function(function fun) { evaluate(fun); }

// 自动取消
void start_auto_cancel(object who, int timeout)
{
        call_out("refuse_quest", timeout, who);
}

// 接受任务
// 发放上一个任务的奖励，生成这一个任务的 npc
int do_accept(string arg)
{
        object head;
        object me;

        if (arg != "quest")
                return notify_fail("你要接受什么？\n");

        if (query_temp("obsolete"))
                return 0;

        me = this_player();
        if( query("id", me) != query("quester") )
                return notify_fail("这信可不是寄给你的。\n");

        if( query("quest/id", me) != query("killed_id") )
                write("你看了看信，上面的东西看来是过时了。\n");
        else
        {
            if (QUEST_D->remote_bonus(me))
            {
                    QUEST_D->start_quest(me, query("quest"));
                    message_sort(query("msg/accept"), me);

                    // Drop head
                    if (objectp(head = present("head", me)) &&
                        query("owner_id", head) == query("killed_id") )
                    {
                        message_vision("$N看看手中的" + head->name() +
                                       "，心道此物已然无用，顺手就往地上一扔。\n",
                                      me);
                        destruct(head);
                    } else
                    if (objectp(head = present("head", environment(me))) &&
                        query("owner_id", head) == query("killed_id") )
                    {
                        message_vision("$N看看地上的" + head->name() +
                                       "，心道此物已然无用，顺手就往边上一踢。\n",
                                      me);
                        destruct(head);
                    }
            } else
                    write("你看了看信，似乎没啥重要的。\n");
        }

        set_temp("obsolete", 1);
        //call_out("dest_ob", 0, this_object());
        destruct(this_object());
        return 1;
}

// 析构函数
void dest_ob(object ob)
{
        destruct(ob);
}

// 拒绝
int do_refuse(string arg)
{
        object me;

        if (arg != "quest")
                return notify_fail("你要拒绝什么？\n");

        if (query_temp("obsolete"))
                return 0;

        me = this_player();
        if( query("id", me) != query("quester") )
                return notify_fail("这信可不是寄给你的。\n");

        message_sort(query("msg/refuse"), me);

        set_temp("obsolete", 1);
        call_out("dest_ob", 0, this_object());
        return 1;
}

// CLASS_D("generate") + "/killed" 延时调用的析构函数
void refuse_quest(object me)
{
        message_sort(query("msg/refuse"), me);

        remove_call_out("eval_function");
        call_out("dest_ob", 0, this_object());
}