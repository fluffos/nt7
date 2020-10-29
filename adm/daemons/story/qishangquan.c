// story:qishangquan 七伤拳

#include <ansi.h>

nosave string char_id;
nosave string char_name;
nosave string family_name;

int give_gift();
object select_character();

nosave mixed *story = ({
        "话说当日成昆让一武林高手救之后：",
        "杨逍：教主，本教刚刚经过了一场大战，我们应先回光明顶重整明教。",
        "张无忌：杨左使说得也没错，那么我就和杨左使先回光明顶，义父你和韦一笑去追击成昆吧。",
        "韦一笑：是，教主。",
        "谢逊：无忌，不必啦，光明顶重整需要人手，成昆我一个人去杀他就够，韦一笑还是和你一起回明教吧。",
        "张无忌：也好！义父，那我们先走了。",
        "说罢，张无忌、杨逍、韦一笑等三人就转身回明教去了。",
        "谢逊心想：虽然说我的武功足以杀成昆，但是......应该也会有一场恶战！！不想了，追上去再说。",
        "不出半个时辰，谢逊已经追到了成昆.........",
        "谢逊喝道：成昆，你别想再跑！",
        "成昆吓得出了一身冷汗，过了一会才慢慢的转过身来，一见到只有谢逊一人才松了一口气。",
        "成昆：我说我的徒儿，凭你也想杀你的师父么？虽说你的功夫有很大的进步，但是我这几年也不是白活啊！",
        "谢逊：废话少说，来吧！！！",
        "谢逊说罢就向成昆挥出一拳，成昆嘿嘿一笑，身体轻轻一转就避开了。",
        "谢逊心想：以现在的情况要杀死成昆确实不易，如果那天在光明顶答应帮我杀成昆的$N在这里的话，那就一定没问题",
        "话说曹操，曹操就到，$N路过这里一见谢逊和成昆正打得火热，就马上施展轻功赶到谢逊身边。",
        "$N对着谢逊说道：谢老前辈，今天可以实现我的诺言了！",
        "成昆望着$N在那里恶心的表演心中有说不出的烦，鄙视的望着$N“呸”的一声！",
        "$N马上气得火冒三丈，聚全身功力于一掌向成昆拍去！！！",
        "成昆见状马出掌相对！！！",
        "但是$N内功深厚，成昆被震得经脉尽断，整个人向后倒飞了出去",
        "谢逊马上提起屠龙赶到成昆的后面，然后对准他的臭冬瓜脑袋下面的脖子一刀砍下去！！！",
        "成昆连叫都来不及叫一声就死了！！！！",
        "谢逊对天狂笑：哈哈哈！哈哈哈哈！！！哈哈！！！！！！",
        "过了良久......",
        "谢逊对着$N说到：我现在就按照当天的约定，把我的七伤拳传授给你！",
        (: give_gift :),
});

void create()
{
        seteuid(getuid());

        if (! objectp(select_character()))
        {
                destruct(this_object());
                return;
        }
}

string prompt() { return HIY "【奇遇】" NOR; }

object select_character()
{
        object *obs;
        object ob;

        obs = filter_array(all_interactive(),
                           (: ultrap($1) &&
                              living($1) &&
                              $1->query_skill("qishang-quan", 1) < 1 &&
/*
                              query("combat_exp", $1) <= 30000000 && 
                              query("combat_exp", $1)>2500000 && 
*/
                              query("max_neili", $1)>5500 && 
                              SKILL_D("qishang-quan")->valid_learn($1) &&
                              ! wizardp($1) &&
                              !query("story/qishangquan", $1):));
        if (! sizeof(obs))
                return 0;

        ob = obs[random(sizeof(obs))];
        char_id=query("id", ob);
        char_name = ob->name(1);
        return ob;
}

mixed query_story_message(int step)
{
        mixed msg;

        if (step >= sizeof(story))
                return 0;

        msg = story[step];
        if (stringp(msg))
        {
                msg = replace_string(msg, "$N", char_name);
                msg = replace_string(msg, "$ID", char_id);
        }
        return msg;
}

int give_gift()
{
        object ob;

        ob = find_player(char_id);
        if (! ob) return 1;

        if (ob->query_skill("qishang-quan", 1) < 10)
                ob->set_skill("qishang-quan", 10);

        set("story/qishangquan", 1, ob);
        tell_object(ob, HIC "你从谢逊那里学习到了七伤拳。\n" NOR);
        CHANNEL_D->do_channel(this_object(), "rumor", "听说" + ob->name(1) +
                              "从谢逊那里学习到了七伤拳。");
        STORY_D->remove_story("qishangquan");
        return 1;
}
