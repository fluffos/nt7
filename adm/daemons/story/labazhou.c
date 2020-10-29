 // story:labazhou 腊八粥
 // Plzw 2004-08-29

#include <ansi.h>

nosave string char_id;
nosave string char_name;
nosave string fam_name;
nosave string ann_name;
nosave string ann_id;

mixed give_pai();
int   rob_pai();
object   select_characters();

nosave mixed *story = ({
        "又是一年的冬天。",
        "夜晚，$N躺在床上正要休息。",
        "忽听门外一人朗声说道：“侠客岛赏善罚恶使者，前来拜见$F的$N！”",
        "$N冲出门去，只见院子里并肩站着一胖一瘦两个人。",
        "$N一见此一胖一瘦两人，颤声道：“尊驾二位便是侠客岛的赏善罚恶使者么？”",
        "张三道：“正是。阁下可是$F的$N？我们奉侠客岛岛主之命，手持铜牌前来，邀请阁下赴敝岛相叙，喝一碗腊八粥。”",
        "$N沉默不语。",
        "...",
        "张三道：“阁下不说话，那就是了。”",
        "张三从怀中取出一块铜牌，笑道：“既是如此，还望阁下准时赴约！",
        "$N知道这赏善罚恶使者的厉害，无奈之下，接过铜牌低声道：“多谢贵岛奉邀，定当于期前赶到。”",
        "张三和李四相视一笑，转眼消失在夜幕中。",
        "...",
        (: give_pai :),
        "$AN大笑道：“你这胆小怕事之人，有胆去么，不如将令牌让我，我倒想去侠客岛见识见识！”",
        "$N心想：居然天底下还有这种想死的人，自己反正也不会去，不如让给他。”",
        "$N将铜牌递上道：“既然兄台想去，拿去便是！”",
        "$AN接过铜牌哈哈大笑，身形一闪，已然消失在夜幕中。",
        (: rob_pai :),
});

void create()
{
        seteuid(getuid());

        if (! objectp(select_characters()))
        {
                STORY_D->remove_story("labazhou");
                destruct(this_object());
                return;
        }
}

string prompt() { return HIG "【奇遇】" NOR; }

object select_characters()
{
        object *obs;
        object ob;

        obs = filter_array(all_interactive(),
                           (: living($1) &&
                                  query("family", $1) && 
                              /*
                              query("weiwang", $1) >= 50000 && 
                              query("score", $1) >= 50000 && 
                              $1->query_skill("force", 1) >= 100 &&
                              $1->query_skill("dodge", 1) >= 100 &&
                              $1->query_skill("parry", 1) >= 100 &&
                              */
                              query("combat_exp", $1) >= 100000 && 
                              !wizardp($1) &&
                              !query("story/labazhou", $1):));
        if (! sizeof(obs))
                return 0;

        ob = obs[random(sizeof(obs))];
        char_id=query("id", ob);
        char_name = ob->name(1);
        fam_name=query("family/family_name", ob);

                obs = filter_array(all_interactive(),
                                                        (: living($1) &&
                                                        query("weiwang", $1) >= 50000 && 
                                                        query("score", $1) >= 50000 && 
                                                        /*
                                                        $1->query_skill("force", 1) >= 150 &&
                                                        $1->query_skill("dodge", 1) >= 150 &&
                                                        $1->query_skill("parry", 1) >= 150 &&
                                                        */
                                                        query("combat_exp", $1) >= 100000 && 
                                                        !wizardp($1) &&
                                                        !query("story/labazhou", $1):));
        if (! sizeof (obs))
                return ob;
        ob = obs[random(sizeof(obs))];
        ann_id=query("id", ob);
        ann_name = ob->name(1);
        return ob;
}

mixed query_story_message(int step)
{
        mixed msg;

        if (step >= sizeof(story))
                return 0;

        if( !char_id || !ann_id ) return 0;
        msg = story[step];
        if (stringp(msg))
        {
                msg = replace_string(msg, "$N", char_name);
                msg = replace_string(msg, "$ID", char_id);
//                     msg = replace_string(msg, "$F", fam_name); 
                     msg = replace_string(msg, "$F", ""); 
                msg = replace_string(msg, "$AN", ann_name);
                msg = replace_string(msg, "$AID", ann_id);
        }
        return msg;
}

mixed give_pai()
{
        object ob;
        object pai;

        ob = find_player(char_id);
        if (! ob) return 1;

                if (random(4) > 0)
                {

                set("story/labazhou", 1, ob);
                CHANNEL_D->do_channel(this_object(), "rumor", "听说" + ob->name(1) +
                                      "收到龙、木二岛主的邀请去侠客岛喝腊八粥。");
                // 正神是赏善，负神是惩恶
                if( query("shen", ob) >= 0 )
                        pai = new("/d/xiakedao/obj/tongpai1");
                else
                        pai = new("/d/xiakedao/obj/tongpai2");

                set("own", query("id", ob), pai);
                pai->move(ob, 1);
                set("xkd/ling", 1, ob);
                set("xkd/time", time()+86400, ob);
                STORY_D->remove_story("labazhou");
                return 0;
            }
            // 25%的几率被抢
            if (ann_id != char_id)
                return "一道黑影掠过，一掌重重的击在" + char_name + "的背心，" + char_name + "大叫一声，吐出一口鲜血。";

}

int rob_pai()
{
        object ob, rob;
        object pai;

        ob = find_player(char_id);
        rob = find_player(ann_id);
        if ((! ob) || (! rob)) return 1;

        set("story/labazhou", 1, rob);
        CHANNEL_D->do_channel(this_object(), "rumor",
                              "听说" + rob->name(1) + "从" + ob->name(1) + "手中夺走了"
                              "赏善罚恶令牌。");
        STORY_D->remove_story("labazhou");
        if (rob)
        {
                // 正神是赏善，负神是惩恶
                if( query("shen", rob) >= 0 )
                        pai = new("/d/xiakedao/obj/tongpai1");
                else
                        pai = new("/d/xiakedao/obj/tongpai2");
                if (pai) pai->move(rob, 1);
        }
        return 0;
}

