// story:baihu 白虎

#include <ansi.h>

int give_gift(string name);

nosave mixed *story = ({
        "天庭。",
        "太白金星：今日太乙真人广邀群仙赴宴，不知他又要搞什么名堂。",
        "童子：师父，太上老君来了。",
        "太白金星：哦？来得正好！",
        "太上老君：金星啊，时候也差不多了，这就走吧，不然迟到了太乙真人又要发标了。",
        "太白金星面露怯色，好像害怕什么。",
        "太白金星：走啦，童儿，快去牵我的坐骑来。",
        "童子：是！说罢飞奔而出 ……",
        "太上老君：太白金星啊，你那个坐骑跑得太慢，不如坐我这只仙鹤，免得迟到。",
        "太白金星恍然大悟道：正是，正是！还是坐你的仙鹤快！免得那老不死的又要发标。",
        "太上老君和太白金星乘仙鹤飞去 ……",
        "童子：师父，我来了。你的坐骑在这里~~",
        "童子：？？？师父不见了？正好这个时候出去玩玩。",
        "童子：小虎，小虎，我出去玩你就呆在这别到处乱跑哦！",
        "小虎：盎~！哄~！",
        "童子：好吧，我走了！说罢童子飞奔而出 ……",
        "小虎跟着跑了出去 ……",       
        (: give_gift, "baihu" :),
        "听说白虎(white tiger)一阵乱蹿，到了凡间。",
});

string prompt() { return HIM "【神话】" NOR; }

void create()
{
        seteuid(getuid());
}

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}

int give_gift(string name)
{
        object ob;

        ob = new(CLASS_D("misc/") + name);
        if (! objectp(ob))
                return 0;

        NPC_D->place_npc(ob);
        if (! objectp(environment(ob)))
        {
                destruct(ob);
                return 0;
        }

        CHANNEL_D->do_channel(find_object(STORY_D), "sys",
                              ob->name() + "出现在" + environment(ob)->short() +
                              "(" + base_name(environment(ob)) + ")。");
        return 1;
}
