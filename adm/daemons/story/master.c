// story:master 宗师聚会

#include <ansi.h>

nosave string *char_id;
nosave string *char_name;
nosave string winner_name;
nosave string winner_id;
nosave string ann_name;
nosave string ann_id;

int   get_winner();
mixed give_gift();
int   rob_gift();
int   select_characters();

nosave mixed *story = ({
        "$1[$I1]：好，今日我们五人齐聚华山，不必寒暄，可快入正题。",
        "$2[$I2]：嗯，来龙去脉也不必多说了，此次乃是为了江湖上近日出现的"
        HIM "玄黄紫清丹" NOR WHT "一事。",
        "$3[$I3]：听说此丹千年一遇，服用以后妙用无穷，平增十年功力。",
        "$4[$I4]：嘿嘿，只是每次出现弄得江湖腥风血雨，不得安宁。",
        "$5[$I5]：所以在下召集诸位，以武会友，定下这神丹名分。",
        "$2[$I2]：也是，这等神物，若是给江湖宵小拿去，真可谓明珠暗投！",
        "$5[$I5]：近来江湖你争我夺，在下实在是看不过去，这才亲自出手取了来。",
        "$1[$I1]：甚好甚好，理当如此。",
        "$5[$I5]：只是此神物我也不敢贸然自居，故请得诸位来华山论剑，以决此物归属。",
        "$3[$I3]：废话不必多说，如何比法？",
        "$4[$I4]：我们各显绝艺，谁能压倒对方，便是得主，如何？",
        "$2[$I2]：好吧，$4所言极是。",
        "...",
        "天黑了...",
        "天又亮了...",
        "天又黑了...",
        "天又亮了...",
        "...",
        (: get_winner :),
        "$a叹服道：三天以来，看来还是$w武功高强，更胜一筹啊！",
        "$w谦道：哪里哪里，各位身手不凡，在下亦是眼界大开，方知天外有天。",
        "$a[$Ia]：不必谦让，此物理应归$w所有，此乃天意啊。",
        (: give_gift :),
        "$w[$Iw]：休走！接招！",
        "那黑影蓦然回身，和$w对了一掌，只震得$w眼花缭乱，气血翻涌。",
        "黑影哈哈长笑，飘然下山而去。",
        "$w调息良久，缓缓的吐出一口气，道：此人内力当真深厚，我看好像是$6。",
        (: rob_gift :),
});

void create()
{
        seteuid(getuid());

        if (uptime() < 86400)
        {
                destruct(this_object());
                return;
        }

        ann_id = 0;
        ann_name = 0;
        winner_id = 0;
        winner_name = 0;
        if (! select_characters())
        {
                STORY_D->remove_story("master");
                destruct(this_object());
                return;
        }
}

string prompt() { return HIG "【论剑】" NOR; }

int select_characters()
{
        object *obs;
        object ob;
        int i;

        obs = filter_array(all_interactive(),
                           (: ! wizardp($1) && ultrap($1) && living($1):));
        if (sizeof(obs) < 6)
                return 0;

        char_id = allocate(6);
        char_name = allocate(6);
        for (i = 0; i < 6; i++)
        {
                ob = obs[random(sizeof(obs))];
                char_id[i]=query("id", ob);
                char_name[i] = ob->name(1);
                obs -= ({ ob });
        }

        return 1;
}

mixed query_story_message(int step)
{
        mixed msg;

        if (step >= sizeof(story))
                return 0;

        msg = story[step];
        if (functionp(msg)) msg = evaluate(msg);
        if (stringp(msg))
        {
                msg = replace_string(msg, "$1", char_name[0]);
                msg = replace_string(msg, "$I1", char_id[0]);
                msg = replace_string(msg, "$2", char_name[1]);
                msg = replace_string(msg, "$I2", char_id[1]);
                msg = replace_string(msg, "$3", char_name[2]);
                msg = replace_string(msg, "$I3", char_id[2]);
                msg = replace_string(msg, "$4", char_name[3]);
                msg = replace_string(msg, "$I4", char_id[3]);
                msg = replace_string(msg, "$5", char_name[4]);
                msg = replace_string(msg, "$I5", char_id[4]);
                msg = replace_string(msg, "$6", char_name[5]);
                msg = replace_string(msg, "$I6", char_id[5]);
                if (ann_name && ann_id)
                {
                        msg = replace_string(msg, "$a", ann_name);
                        msg = replace_string(msg, "$Ia", ann_id);
                }
                if (winner_name && winner_id)
                {
                        msg = replace_string(msg, "$w", winner_name);
                        msg = replace_string(msg, "$Iw", winner_id);
                }
        }
        return msg;
}

int get_winner()
{
        int i;

        i = random(5);
        winner_name = char_name[i];
        winner_id = char_id[i];
        do
        {
                i = random(5);
                ann_id = char_id[i];
                ann_name = char_name[i];
        } while (ann_id == winner_id);

        return 1;
}

mixed give_gift()
{
        object gob;
        object gift;

        gob = find_player(winner_id);
        if (random(2))
        {
                CHANNEL_D->do_channel(this_object(), "rumor",
                                      "听说五大宗师在华山聚会，将" +
                                      "玄黄紫清丹交给" + winner_name + "。");
                STORY_D->remove_story("master");
                if (gob)
                {
                        gift = new("/clone/ultra/xuanhuang");
                        if (gift) gift->move(gob, 1);
                }
                return 0;
        }

        return "一道黑影掠过，一掌重重的击在$a的背心，$a大叫一声，吐出一口鲜血。";
}

int rob_gift()
{
        object rob;
        object gift;

        rob = find_player(char_id[5]);
        CHANNEL_D->do_channel(this_object(), "rumor",
                              "听说" + char_name[5] + "从五大宗师手中夺走了"
                              "玄黄紫清丹。");
        STORY_D->remove_story("master");
        if (rob)
        {
                gift = new("/clone/ultra/xuanhuang");
                if (gift) gift->move(rob, 1);
        }
        return 0;
}
