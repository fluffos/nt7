// story:jiuyang 九阳神功

#include <ansi.h>

nosave string char_id;
nosave string char_name;

int give_gift();
object select_character();

nosave mixed *story = ({
        "一堆佛经。",
        "$N拿起一本细细的看了半天，却不得要领，这分明就是一本佛经，没有半点武功诀窍。",
        "$N沉思片刻，将书反了过来，逆句读、跳字读，还是没有什么奥妙。",
        "盛怒之下，$N用力将佛经扔了开去，又拣起一本，却是《金刚经》。",
        "研读片刻，还是一堆废话。",
        "“岂有此理，少林寺的藏经阁就放了这些东西？”$N心中暗道：“莫非少林僧人其实都不会武功？”",
        "随拣随丢，须臾已经翻了几十本经书，没有找到半点头绪。",
        "$N不由得暗暗叫苦，看了看地上躺着的慧真和道一二人，心想：这次闯进藏经阁，实在是干冒奇险，居然...",
        "一时间$N不由得心头大怒，将手中的经书撕了个粉碎，霎时纸片飞扬。",
        "忽然几张碎纸片飘过$N的眼前，似乎写着：力从人借，气由脊发。胡能气由脊发...",
        "$N见识不凡，看了这几句心中登时一动，这分明是极上乘的武学诀窍！",
        "$N看了看手中剩下的半卷经书，赫然是一本：《楞伽经》，只见夹缝中密密麻麻的写着一些文字。",
        "只是经书已经缺了一半，如何是好？$N连忙在地上慢慢寻找，把碎纸一片片寻回。",
        "待到碎片悉数裱好，已然过了两个时辰，$N细细读过，原来这《楞伽经》夹缝中居然录有一份九阳真经。",
        "$N心下暗自琢磨：当年华山论剑，也不过是争夺一本九阴真经而已，今天我得了此书，当真是奇遇。",
        "$N随即将烛台拿近，慢慢揣摩真经要旨，只是真经博大精深，一时未能全然领悟。",
        "眼见天色渐晚，$N不敢久留，揣起经书，想了想，又把经文开头一段扯下撕碎，这才收好。",
        "$N暗道，待我回去细细研读这九阳真经，他日天下无敌，岂不美哉？",
        "想罢，$N跃出窗去，悄然飘失在夜幕中。",
        (: give_gift :),
});

void create()
{
        seteuid(getuid());

        if (! objectp(select_character()))
        {
                STORY_D->remove_story("jiuyang");
                destruct(this_object());
                return;
        }
}

string prompt() { return HIG "【奇遇】" NOR; }

object select_character()
{
        object *obs;
        object ob;

        obs = filter_array(all_interactive(),
                           (: living($1) &&
                              $1->query_skill("jiuyang-shengong", 1) < 1 &&
/*
                              query("combat_exp", $1) >= 100000 && 
                              query("combat_exp", $1)<1500000 && 
*/
                              SKILL_D("jiuyang-shengong")->valid_learn($1) &&
                              ! wizardp($1) &&
                              !query("story/jiuyang", $1):));
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
        object book;

        ob = find_player(char_id);
        if (! ob) return 1;

        if (ob->query_skill("jiuyang-shengong", 1) < 50)
                ob->set_skill("jiuyang-shengong", 50);

        set("story/jiuyang", 1, ob);
        tell_object(ob, HIC "你学习到了九阳神功。\n" NOR);
        CHANNEL_D->do_channel(this_object(), "rumor", "听说少林寺"
                              "藏经阁失窃，遗失楞伽经一本。");
        book = new("/clone/book/jiuyang-book");
        book->move(ob, 1);
        STORY_D->remove_story("jiuyang");
        return 1;
}
